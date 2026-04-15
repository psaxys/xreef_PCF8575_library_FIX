# PCF8575 INPUT fix fork

Base project: xreef/PCF8575_library

## Problem fixed

For pins configured as `INPUT` and used with an external pull-up resistor (button to GND / active-low), `digitalRead()` could incorrectly keep returning `LOW`.

## Root causes

1. `readBuffer()` updated the input buffer only when **both** conditions were true at the same time:
   - a pull-down style input was HIGH, and
   - a pull-up style input was LOW.

   This should be logical OR, not AND.

2. `digitalRead()` consumed the buffered level after a read by flipping the bit in `byteBuffered`. That made the API behave like an event latch instead of returning the current stable pin state.

## Changes

- `PCF8575.cpp`
  - Changed the condition in `readBuffer()` from `and` to `||`.
  - Removed buffer-bit clearing in `digitalRead()` so repeated reads reflect the actual current level.

## Expected behavior after fix

- `INPUT` pin + external pull-up + button to GND:
  - released button -> `HIGH`
  - pressed button -> `LOW`

- repeated `digitalRead()` calls now return the actual level instead of dropping back to `LOW` because of internal buffer mutation.
