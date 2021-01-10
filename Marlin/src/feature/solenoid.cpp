/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include "../inc/MarlinConfig.h"

#if EITHER(EXT_SOLENOID, MANUAL_SOLENOID_CONTROL)

#include "solenoid.h"

#include "../module/motion.h" // for active_extruder

// PARKING_EXTRUDER options alter the default behavior of solenoids, this ensures compliance of M380-381

#if ENABLED(PARKING_EXTRUDER)
  #include "../module/tool_change.h"
  #define SOLENOID_MAGNETIZED_STATE (TERN_(PARKING_EXTRUDER_SOLENOIDS_INVERT,!)PARKING_EXTRUDER_SOLENOIDS_PINS_ACTIVE)
#else
  #define SOLENOID_MAGNETIZED_STATE HIGH
#endif

#define HAS_SOLENOID(N) (HAS_SOLENOID_##N && TERN(MANUAL_SOLENOID_CONTROL, true, EXTRUDERS > N))

// Used primarily with MANUAL_SOLENOID_CONTROL
static void set_solenoid(const uint8_t num, const bool active) {
  const uint8_t value = active ? SOLENOID_MAGNETIZED_STATE : !SOLENOID_MAGNETIZED_STATE;
  switch (num) {
    case 0:
      OUT_WRITE(SOL0_PIN, value);
      TERN_(PARKING_EXTRUDER, if (!active && active_extruder == 0) parking_extruder_set_parked()); // If active extruder's solenoid is disabled, carriage is considered parked
      break;
    #if HAS_SOLENOID(1)
      case 1:
        OUT_WRITE(SOL1_PIN, value);
        TERN_(PARKING_EXTRUDER, if (!active && active_extruder == 1) parking_extruder_set_parked()); // If active extruder's solenoid is disabled, carriage is considered parked
        break;
    #endif
    #if HAS_SOLENOID(2)
      case 2:
        OUT_WRITE(SOL2_PIN, value);
        break;
    #endif
    #if HAS_SOLENOID(3)
      case 3:
        OUT_WRITE(SOL3_PIN, value);
        break;
    #endif
    #if HAS_SOLENOID(4)
      case 4:
        OUT_WRITE(SOL4_PIN, value);
        break;
    #endif
    #if HAS_SOLENOID(5)
      case 5:
        OUT_WRITE(SOL5_PIN, value);
        break;
    #endif
    default:
      SERIAL_ECHO_MSG(STR_INVALID_SOLENOID);
      break;
  }
}

void enable_solenoid(const uint8_t num) { set_solenoid(num, true); }
void disable_solenoid(const uint8_t num) { set_solenoid(num, false); }
void enable_solenoid_on_active_extruder() { enable_solenoid(active_extruder); }

void disable_all_solenoids() {
  disable_solenoid(0);
  #if HAS_SOLENOID(1)
    disable_solenoid(1);
  #endif
  #if HAS_SOLENOID(2)
    disable_solenoid(2);
  #endif
  #if HAS_SOLENOID(3)
    disable_solenoid(3);
  #endif
  #if HAS_SOLENOID(4)
    disable_solenoid(4);
  #endif
  #if HAS_SOLENOID(5)
    disable_solenoid(5);
  #endif
}

#endif // EXT_SOLENOID || MANUAL_SOLENOID_CONTROL
