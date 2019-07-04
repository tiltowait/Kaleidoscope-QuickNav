# Kaleidoscope-QuickNav

A barebones alternative to [TapDance](https://github.com/keyboardio/Kaleidoscope-TapDance) that sends Cmd+[ or Cmd+] when the Control keys are double-tapped. On a Mac, this is equivalent to browser back and browser forward. It would be trivial to make this work on Windows by changing the call to `LGUI` to `LCTRL`.

The reason for this plugin's existence is due to a [bug](https://github.com/keyboardio/Kaleidoscope/issues/571) in the TapDance plugin. Since I only need very basic functionality from the plugin, I opted to make my own, much lighter, replacement.

## Using the Plugin

Installation of `QuickNav` into your Kaleidoscope sketch is simple.

```c++
#include <Kaleidoscope.h>
#include <Kaleidoscope-AutoShift.h>

KALEIDOSCOPE_INIT_PLUGINS(QuickNav);

void setup() {
  Kaleidoscope.setup();
}
```

## Configuring the Plugin

`QuickNav` has several member functions for controlling its behavior.

### `enable()`

Enables the plugin.

### `disable()`

Disables the plugin.

### `set_timeout(uint16_t new_timeout)`

`QuickNav` only sends the browser navigation shortcut if the control taps occur within a certain time period. By default, this timeout is 200ms, but it can be changed to whatever the user wants.

### `set_tap_threshold(uint8_t new_threshold)`

Alters the number of taps necessary before `QuickNav` sends the browser navigation shortcut. Default is 2. Setting this to 0 effectively disables the Control keys, and is not recommended.

## Querying the Plugin

### `active()`

Returns `true` if the plugin is enabled.


### `timeout()`

Returns the timeout, in milliseconds.

### `tap_threshold()`

Returns the number of taps necessary before sending the browser navigation shortcut.
