# Kaleidoscope-QuickNav

A barebones alternative to [TapDance](https://github.com/keyboardio/Kaleidoscope-TapDance) that sends Ctrl/Cmd+[ or Ctrl/Cmd+] when the Control keys are double-tapped. This is the shortcut to browser back and browser forward.

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

### Basics

#### `enable()`

Enables the plugin.

#### `disable()`

Disables the plugin.

#### `set_timeout(uint16_t new_timeout)`

`QuickNav` only sends the browser navigation shortcut if the control taps occur within a certain time period. By default, this timeout is 200ms, but it can be changed to whatever the user wants.

#### `set_tap_threshold(uint8_t new_threshold)`

Alters the number of taps necessary before `QuickNav` sends the browser navigation shortcut. Default is 2. Setting this to 0 effectively disables the Control keys, and is not recommended.

### Operating System Control

Different operating systems use different keys for shortcut chords. Windows/Linux use `Control`, while macOS uses `Command`. The following methods allow the user to tell the plugin which OS is in use. By default, `QuickNav` is set to Windows mode.

#### `use_windows()`

#### `use_mac()`

#### `use_linux()`

`use_windows()` and `use_linux()` are functionally identical and are provided simply for ease of use. `use_linux()` should be used for the BSDs and many other operating systems, as well.

## Querying the Plugin

### `active()`

Returns `true` if the plugin is enabled.


### `timeout()`

Returns the timeout, in milliseconds.

### `tap_threshold()`

Returns the number of taps necessary before sending the browser navigation shortcut.
