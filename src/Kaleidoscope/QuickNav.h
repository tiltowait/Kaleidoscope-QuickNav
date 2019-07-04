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

    // Event handlers. Delete what you don't need.
    EventHandlerResult onKeyswitchEvent(Key &mapped_key, byte row, byte col,
                                        uint8_t key_state);

  private:
    static bool disabled_;
    static uint8_t num_taps_;
    static uint16_t timeout_;
    static uint32_t start_time_;
    static uint8_t control_taps_[];

    enum Control_ : int8_t;

    static inline bool keyIsControl(Key &key) {
        return key.raw == Key_LeftControl.raw
               || key.raw == Key_RightControl.raw;
    }
    static inline Control_ mappedControl(Key &key);
    static inline void reset(void);
};


}  // namespace plugin
}  // namespace kaleidoscope

extern kaleidoscope::plugin::QuickNav QuickNav;
