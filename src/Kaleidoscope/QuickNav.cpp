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

// Member variables.
bool QuickNav::disabled_              = false;
uint16_t QuickNav::timeout_           = 200; // In ms.
uint32_t QuickNav::start_time_        = 0; // In ms.
uint8_t QuickNav::num_taps_           = 2;
uint8_t QuickNav::left_control_taps_  = 0;
uint8_t QuickNav::right_control_taps_ = 0;

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

// Event handlers.

// Run for every non-idle key, in each cycle the key isn't idle in. If a key
// gets pressed, released, or is held, it is not considered idle, and this
// event handler will run for it too.
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
    return EventHandlerResult::OK;
  }
  else if(keyWasPressed(key_state)) {
    return EventHandlerResult::OK;
  }

  if(keyToggledOn(key_state) && keyIsControl(mapped_key)) {
    if(mapped_key.raw == Key_LeftControl.raw) {
      if(++left_control_taps_ == num_taps_) {
        hid::pressKey(LGUI(Key_LeftBracket));
        reset();
        return EventHandlerResult::EVENT_CONSUMED;
      }
    }
    else if(mapped_key.raw == Key_RightControl.raw) {
      if(++right_control_taps_ == num_taps_) {
        hid::pressKey(LGUI(Key_RightBracket));
        reset();
        return EventHandlerResult::EVENT_CONSUMED;
      }
    }
  }
  else { // Not a control key, so reset everything.
    reset();
  }
  return EventHandlerResult::OK;
}

void QuickNav::reset(void) {
  left_control_taps_ = 0;
  right_control_taps_ = 0;
  start_time_ = 0;
}

}  // namespace plugin
}  // namespace kaleidoscope

kaleidoscope::plugin::QuickNav QuickNav;
