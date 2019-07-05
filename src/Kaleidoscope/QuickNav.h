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

#pragma once

#include <Kaleidoscope.h>

namespace kaleidoscope {
namespace plugin {

class QuickNav : public kaleidoscope::Plugin {
  public:
    // Basic plugin status functions.
    static void enable();
    static void disable();
    static bool active();

    enum OSMode : int8_t;

    // OS behavior
    static void use_windows();
    static void use_mac();
    static void use_linux();

    // Getters and setters
    static uint16_t timeout();
    static void set_timeout(uint16_t new_timeout);
    static uint8_t tap_threshold();
    static void set_tap_threshold(uint8_t new_threshold);

    EventHandlerResult onKeyswitchEvent(Key &mapped_key, byte row, byte col,
                                        uint8_t key_state);

  private:
    static bool disabled_;
    static OSMode os_mode_;
    static uint8_t tap_threshold_;
    static uint16_t timeout_;
    static uint32_t start_time_;
    static uint8_t tap_count_[];

    enum Control_ : int8_t;

    static inline Control_ mapped_control(Key &key);
    static inline void reset(void);
};


}  // namespace plugin
}  // namespace kaleidoscope

extern kaleidoscope::plugin::QuickNav QuickNav;
