// Obins stock firmware has something similar to this already enabled, but disabled by default in QMK
#define PERMISSIVE_HOLD
#pragma once

#undef TAPPING_TERM
#define TAPPING_TERM 200
//#define RETRO_TAPPING

#undef TAPPING_TOGGLE
#define TAPPING_TOGGLE 2

#define MK_3_SPEED
#define MK_MOMENTARY_ACCEL

#define CAPS_LOCATION (MATRIX_COLS * 0 + 0)

#define IDLE_PROFILE_INDEX 0
