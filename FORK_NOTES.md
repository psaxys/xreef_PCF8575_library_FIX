# PCF8575 input fix fork

This fork fixes three input-related issues in the upstream library:

1. `readBuffer()` updated the input buffer only when pull-down and pull-up conditions were both true. It now updates when either condition is true.
2. `digitalRead()` no longer clears the buffered bit after a read. That old behavior made reads edge-like instead of returning the current level.
3. `pinMode(INPUT)` and `pinMode(INPUT_PULLUP)` now actively release the PCF8575 pin by writing `1` to the expander bit and synchronizing the port state immediately after mode changes. This is required by the PCF8575 quasi-bidirectional architecture, otherwise a pin can stay driven low and a button-to-GND with pull-up never reads HIGH correctly.

## Practical effect

A button wired from the PCF8575 pin to GND with a pull-up to VCC now behaves as expected:
- idle = HIGH
- pressed = LOW

## Recommended usage

```cpp
pcf8575.pinMode(P0, INPUT);
// external pull-up resistor to VCC, button to GND

// or
pcf8575.pinMode(P0, INPUT_PULLUP);
```
