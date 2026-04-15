# PCF8575 input fix fork

This fork fixes active-low button handling for pins configured as `INPUT` and externally pulled up to VCC.

## What was fixed

1. `pinMode(INPUT)` and `pinMode(INPUT_PULLUP)` now release the PCF8575 pin by writing HIGH to the expander state.
2. `readBuffer()` now updates all configured input bits unconditionally from the live I2C sample.
3. `digitalRead()` now returns the current pin level instead of consuming edge-like cached states.
4. `digitalReadAll()` also preserves sampled states and reports actual input levels.
5. The broken `and` condition in the original buffered read path was removed from the effective logic.

## Why the original code failed

For plain `INPUT`, the upstream code only treated one polarity as a valid buffered change. With an external pull-up and a button to GND, the LOW transition was ignored, so the press was never reflected in `digitalRead()`.

## Recommended use

If your wiring is:
- resistor from pin to VCC
- button from pin to GND

then both of these should now work:
- `pinMode(pin, INPUT)` with external pull-up
- `pinMode(pin, INPUT_PULLUP)`

Pressed button should read `LOW`.
