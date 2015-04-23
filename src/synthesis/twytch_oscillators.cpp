/* Copyright 2013-2015 Matt Tytel
 *
 * twytch is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * twytch is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with twytch.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "twytch_oscillators.h"

namespace mopo {

  TwytchOscillators::TwytchOscillators() : Processor(kNumInputs, 1) {
    oscillator1_phase_ = 0;
    oscillator2_phase_ = 0;
    oscillator1_value_ = 0.0;
    oscillator1_value_ = 0.0;
  }

  void TwytchOscillators::process() {
    int wave1 = static_cast<int>(input(kOscillator1Waveform)->source->buffer[0] + 0.5);
    int wave2 = static_cast<int>(input(kOscillator2Waveform)->source->buffer[0] + 0.5);

    int i = 0;
    if (input(kReset)->source->triggered) {
      int trigger_offset = input(kReset)->source->trigger_offset;
      for (; i < trigger_offset; ++i)
        tick(i, wave1, wave2, 8, 10000, 8, 10000);

      oscillator1_phase_ = 0;
      oscillator2_phase_ = 0;
      oscillator1_value_ = 0.0;
      oscillator1_value_ = 0.0;

      for (int i = 0; i < 16; ++i) {
        oscillator1_detune_offsets_[i] = i * (INT_MAX >> 4);
        oscillator2_detune_offsets_[i] = i * (INT_MAX >> 4);
      }
    }
    for (; i < buffer_size_; ++i)
      tick(i, wave1, wave2, 8, 10000, 8, 10000);
  }
} // namespace mopo
