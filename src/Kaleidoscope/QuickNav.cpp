// -*- mode: c++ -*-
// Kaleidoscope-QuickNav -- Double-tap the control keys to trigger browser back and forward.
// Copyright (C) 2019 Jared Lindsay
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <Kaleidoscope-QuickNav.h>

namespace kaleidoscope {
namespace plugin {

// QuickNav

enum QuickNav::Control_ : int8_t { NEITHER = -1, LEFT = 0, RIGHT = 1 };
enum QuickNav::OSMode : int8_t { WINDOWS, MAC, LINUX };

// Member variables.
bool QuickNav::disabled_            = false;
QuickNav::OSMode QuickNav::os_mode_ = WINDOWS;
uint16_t QuickNav::timeout_         = 200; // In ms.
uint8_t QuickNav::tap_threshold_    = 2;
uint8_t QuickNav::tap_count_[]      = {0, 0};
uint32_t QuickNav::start_time_      = 0;

// Basic plugin status functions.

// Enable the plugin.
void QuickNav::enable() {
  disabled_ = false;
}

// Disable the plugin.
void QuickNav::disable() {
  disabled_ = true;
}

// Returns true if the plugin is enabled.
bool QuickNav::active() {
  return !disabled_;
}

// OS behavior
void QuickNav::use_windows() {
  os_mode_ = WINDOWS;
}

void QuickNav::use_mac() {
  os_mode_ = MAC;
}

void QuickNav::use_linux() {
  os_mode_ = LINUX;
}

// Getters and setters

// The timeout, in ms, for triggering the navigation action
uint16_t QuickNav::timeout() {
  return timeout_;
}

void QuickNav::set_timeout(uint16_t new_timeout) {
  timeout_ = new_timeout;
}

// The number of taps needed to trigger the navigation action
uint8_t QuickNav::tap_threshold() {
  return tap_threshold_;
}

void QuickNav::set_tap_threshold(uint8_t new_threshold) {
  tap_threshold_ = new_threshold;
}


// Event handlers.

// Watch for taps of either control key. If the same control key is tapped
// tap_threshold_ times within timeout_, then send either Cmd+[ or Cmd+], depending
// on which control was tapped.
EventHandlerResult QuickNav::onKeyswitchEvent(Key &mapped_key, byte row,
                                              byte col, uint8_t key_state) {
  if(disabled_) {
    return EventHandlerResult::OK;
  }

  if(start_time_ != 0 && Kaleidoscope.hasTimeExpired(start_time_, timeout_)) {
    reset();
  }

  if(keyToggledOff(key_state)) {
    start_time_ = Kaleidoscope.millisAtCycleStart();
  }
  else if(keyToggledOn(key_state)) {
    Control_ control = mapped_control(mapped_key);
    Key bracket = Key_NoKey;

    switch(control) {
      case LEFT:
        bracket = Key_LeftBracket;
        break;
      case RIGHT:
        bracket = Key_RightBracket;
        break;
      case NEITHER:
        reset();
        break;
    }

    if(bracket != Key_NoKey) {
      tap_count_[control]++;
      if(tap_count_[control] == tap_threshold_) {
        os_mode_ == MAC ? hid::pressKey(LGUI(bracket))
                        : hid::pressKey(LCTRL(bracket)); // Windows & Linux
        reset();
        return EventHandlerResult::EVENT_CONSUMED;
      }
    }

  }
  return EventHandlerResult::OK;
}

QuickNav::Control_ QuickNav::mapped_control(Key &key) {
  if(key == Key_LeftControl) {
    return LEFT;
  }

  if(key == Key_RightControl) {
    return RIGHT;
  }

  return NEITHER;
}

void QuickNav::reset(void) {
  tap_count_[LEFT]  = 0;
  tap_count_[RIGHT] = 0;
  start_time_          = 0;
}

}  // namespace plugin
}  // namespace kaleidoscope

kaleidoscope::plugin::QuickNav QuickNav;
