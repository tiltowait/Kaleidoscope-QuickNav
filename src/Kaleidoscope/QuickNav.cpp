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

// BACK/FORWARD are duplicates of LEFT/RIGHT for the sake of readability
enum QuickNav::Control_ : int8_t { LEFT = 0, RIGHT = 1,
                                   BACK = 0, FORWARD = 1,
                                   NEITHER = -1 };

// Member variables.
bool QuickNav::disabled_         = false;
uint16_t QuickNav::timeout_      = 200; // In ms.
uint8_t QuickNav::tap_threshold_ = 2;
uint8_t QuickNav::tap_count_[]   = {0, 0};
uint32_t QuickNav::start_time_   = 0;

Key QuickNav::shortcut_[] = { Key_NoKey, Key_NoKey };

QuickNav::QuickNav() {
  use_windows();
}

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
  shortcut_[BACK]    = LALT(Key_LeftArrow);
  shortcut_[FORWARD] = LALT(Key_RightArrow);
}

// The Mac can also use Cmd+Left/Right, but there's a focus issue in
// Safari where this functionality breaks on Topsites, so we use the
// brackets instead.
void QuickNav::use_mac() {
  shortcut_[BACK]    = LGUI(Key_LeftBracket);
  shortcut_[FORWARD] = LGUI(Key_RightBracket);
}

// Linux uses the same shortcut scheme as Windows.
void QuickNav::use_linux() {
  use_windows();
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

    switch(control) {
      case LEFT:
        tap_count_[RIGHT] = 0;
        break;
      case RIGHT:
        tap_count_[LEFT] = 0;
        break;
      case NEITHER:
        reset();
        break;
    }

    if(control != NEITHER) {
      tap_count_[control]++;
      if(tap_count_[control] == tap_threshold_) {
        hid::pressKey(shortcut_[control]);
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
  start_time_       = 0;
}

}  // namespace plugin
}  // namespace kaleidoscope

kaleidoscope::plugin::QuickNav QuickNav;
