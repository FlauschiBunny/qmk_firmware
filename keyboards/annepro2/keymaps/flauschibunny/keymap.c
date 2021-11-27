#include <stdint.h>
#include "annepro2.h"
#include "qmk_ap2_led.h"
#include "config.h"

enum anne_pro_layers {
  _BASE_LAYER,
  _FN1_LAYER, // Navigation and editing
  _FN2_LAYER, // Mouse, Bluetooth, RGB
  _FN3_LAYER, // Makros
  _FN4_LAYER, // Dark Table or mouse in planning...
};

enum custom_keycodes { //Use USER 00 instead of SAFE_RANGE for Via. VIA json must include the custom keycode.
	  ATABF = SAFE_RANGE, //Alt tab forwards
	  ATABR
	};
// Key symbols are based on QMK. Use them to remap your keyboard
/*
* Layer _BASE_LAYER
* ,-----------------------------------------------------------------------------------------.
* | esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |    Bksp   |
* |-----------------------------------------------------------------------------------------+
* | Tab    |  q  |  w  |  e  |  r  |  t  |  y  |  u  |  i  |  o  |  p  |  [  |  ]  |   \    |
* |-----------------------------------------------------------------------------------------+
* | FN1     |  a  |  s  |  d  |  f  |  g  |  h  |  j  |  k  |  l  |  ;  |  '  |    Enter    |
* |-----------------------------------------------------------------------------------------+
* | Shift      |  z  |  x  |  c  |  v  |  b  |  n  |  m  |  ,  |  .  |  /  |    Shift       |
* |-----------------------------------------------------------------------------------------+
* | Ctrl  |  L1   |  Alt  |               space             | AltGr |  FN2  |  FN3  | FN4   |
* \-----------------------------------------------------------------------------------------/
*
* Layer TAP in _BASE_LAYER
* ,-----------------------------------------------------------------------------------------.
* |     |     |     |     |     |     |     |     |     |     |     |     |     |           |
* |-----------------------------------------------------------------------------------------+
* |        |     |     |     |     |     |     |     |     |     |     |     |     |        |
* |-----------------------------------------------------------------------------------------+
* | TG(FN1)|     |     |     |     |     |     |     |     |     |     |     |             |
* |-----------------------------------------------------------------------------------------+
* |            |     |     |     |     |     |     |     |     |     |     |                |
* |-----------------------------------------------------------------------------------------+
* |       |       |       |                                 |       |TG(FN2)|TG(FN3)|TG(FN4)|
* \-----------------------------------------------------------------------------------------/
*/
 const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 [_BASE_LAYER] = KEYMAP( /* Base */
    KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC,
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
    TT(_FN1_LAYER), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
    KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
    KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, TT(_FN2_LAYER), TT(_FN3_LAYER), TT(_FN4_LAYER)
),
  /*
  * Layer _FN1_LAYER
  * ,-----------------------------------------------------------------------------------------.
  * |  `  |  F1 |  F2 |  F3 |  F4 |  F5 |  F6 |  F7 |  F8 |  F9 | F10 | F11 | F12 |  LAYER_0  |
  * |-----------------------------------------------------------------------------------------+
  * | Tab    |PRVAPP|NXTAPP|lst_DSK|NXT_DSK|WWW_SRCH|PGUP|HOME|UP|END | INSRT|V-UP|V-DWN|MUTE |
  * |-----------------------------------------------------------------------------------------+
  * |        | ALT | WIN |CTRL | SHFT |WWW_BAKC|PGDWN|LEFT|DOWN|RIGHT| BCKSPC| CALC | Enter   |
  * |-----------------------------------------------------------------------------------------+
  * | MARK_ALL|UNDO | CUT| COPY | PASTE | REDO|  DEL  |  MPRV  | MNXT |PRINT| MAIL  | ShiFT   |
  * |-----------------------------------------------------------------------------------------+
  * | Ctrl  |  L1   |  Alt  |            SPACE                |  AltGr|TG(FN2)|TG(FN3)|TG(FN4)|
  * \-----------------------------------------------------------------------------------------/
  *
  */
 [_FN1_LAYER] = KEYMAP( /* Base */
    KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, TO(_BASE_LAYER),
    KC_TRNS, ATABR, ATABF, C(G(KC_LEFT)), C(G(KC_RGHT)), KC_WWW_SEARCH, KC_PGUP, KC_HOME, KC_UP, KC_END, KC_INS, KC_VOLU, KC_VOLD, KC_MUTE,
    KC_TRNS, KC_LALT, KC_LGUI, KC_LCTL, KC_LSFT, KC_WWW_BACK, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_BSPC, KC_CALC, KC_TRNS,
    C(KC_A), C(KC_Z), C(KC_X), C(KC_C), C(KC_V), C(KC_Y), KC_DEL, KC_MPRV, KC_MEDIA_PLAY_PAUSE, KC_MNXT, KC_MAIL, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_SPC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
),
  /*
  * Layer _FN2_LAYER
  * ,-----------------------------------------------------------------------------------------.
  * |     |     |     |     |     |    |      |      |     |     |    |      |      |         |
  * |-----------------------------------------------------------------------------------------+
  * | Tab    |     |     |     |     |     |     | wh_u | wh_l | ms_u | wh_r |   |     |      |
  * |-----------------------------------------------------------------------------------------+
  * |    |     |r clck |m clck| l clck |  | WH_U |  ms_left  |  ms_d  |  ms_r  |  |  Enter    |
  * |-----------------------------------------------------------------------------------------+
  * | Shift      |     |     |     |     |     |     |     |  ,  |INSRT| DEL |    Shift       |
  * |-----------------------------------------------------------------------------------------+
  * | Ctrl  |  L1   |  Alt  |               l clck            |  Alt  |TG(FN2)|TG(FN3)|TG(FN4)|
  * \-----------------------------------------------------------------------------------------/
  *
  */
 [_FN2_LAYER] = KEYMAP( /* Base */
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, TO(_BASE_LAYER),
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_WH_UP, KC_MS_WH_LEFT, KC_MS_UP, KC_MS_WH_RIGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_LEFT, KC_MS_BTN2, KC_MS_BTN3, KC_MS_BTN1, KC_TRNS, KC_MS_WH_DOWN, KC_MS_WH_LEFT, KC_MS_DOWN, KC_MS_RIGHT, KC_TRNS, KC_PGDN, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_INS, KC_DEL, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_BTN1, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
 ),
 /*
* Layer _FN3_LAYER
* ,-----------------------------------------------------------------------------------------.
* |     |     |     |     |     |     |     |     |     |     |     |     |     |  LAYER_0  |
* |-----------------------------------------------------------------------------------------+
* |        |     |     |     |     |     |     |     |     |     |     |     |     |        |
* |-----------------------------------------------------------------------------------------+
* | TG(FN1)|     |     |     |     |     |     |     |     |     |     |     |             |
* |-----------------------------------------------------------------------------------------+
* |   shift  |UNDO | CUT| COPY | PASTE | REDO|     |     |     |     |     |                |
* |-----------------------------------------------------------------------------------------+
* |       |       |       |                                 |       |TG(FN2)|TG(FN3)|TG(FN4)|
* \-----------------------------------------------------------------------------------------/
*/
[_FN3_LAYER] = KEYMAP( /* Base */
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NUMLOCK, KC_KP_SLASH, KC_KP_ASTERISK, KC_KP_MINUS, KC_TRNS, KC_TRNS, TO(_BASE_LAYER),
    KC_TAB, KC_TRNS, KC_TRNS, KC_UP, KC_TRNS, KC_TRNS, KC_TRNS, KC_KP_7 KC_KP_8, KC_KP_9, KC_KP_PLUS, KC_HOME, KC_END, KC_TRNS,
    KC_TRNS, KC_LCTL, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, KC_KP_4, KC_KP_5, KC_KP_6, KC_KP_PLUS, KC_BSPC, KC_KP_ENTER,
    KC_LSFT, C(KC_Z), C(KC_X), C(KC_C), C(KC_V), C(KC_Y), KC_DEL, KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_ENTER, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_KP_0, KC_KP_DOT, KC_TRNS, KC_TRNS, KC_TRNS
 ),
/*
  * Layer _FN4_LAYER
  * ,-----------------------------------------------------------------------------------------.
  * | USB | BT1 | BT2 | BT3 | BT4 |BTDEL|  F6 |  F7 | F8 | LEDOF|LEDON| LEDI | LEDV | LAYER_0|
  * |-----------------------------------------------------------------------------------------+
  * | Tab    |     |     |  UP |  r  |  t  |  y  |  u  |  i  |  o  | PS | HOME | END |   \    |
  * |-----------------------------------------------------------------------------------------+
  * |       |  Ctrl |LEFT |DOWN |RIGHT|  g  |  h  |  j  |  k  |  l  | PGUP|PGDN |    Enter    |
  * |-----------------------------------------------------------------------------------------+
  * | Shift      |  z  |  x  |  c  |  v  |  b  |  n  |  m  |  ,  |INSRT| DEL |    Shift       |
  * |-----------------------------------------------------------------------------------------+
  * | Ctrl  |  L1   |  Alt  |               space             |  Alt  |TG(FN2)|TG(FN3)|TG(FN4)|
  * \-----------------------------------------------------------------------------------------/
  *
  */
 [_FN4_LAYER] = KEYMAP( /* Base */
    KC_AP2_USB, KC_AP2_BT1, KC_AP2_BT2, KC_AP2_BT3, KC_AP2_BT4, KC_AP2_BT_UNPAIR, KC_TRNS, KC_TRNS, KC_TRNS, KC_AP_LED_OFF, KC_AP_LED_ON, KC_AP_LED_NEXT_INTENSITY, KC_AP_LED_SPEED, TO(_BASE_LAYER),
    KC_TRNS, KC_TRNS, KC_UP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PSCR, KC_HOME, KC_END, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGUP, KC_PGDN, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_INS, KC_DEL, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
 ),
};
const uint16_t keymaps_size = sizeof(keymaps);


void matrix_init_user(void) {

}

void matrix_scan_user(void) {
}

// Code to run after initializing the keyboard
void keyboard_post_init_user(void) {
    // Here are two common functions that you can use. For more LED functions, refer to the file "qmk_ap2_led.h"

    // annepro2-shine disables LEDs by default. Uncomment this function to enable them at startup.
    annepro2LedEnable();

    // Additionally, it also chooses the first LED profile by default. Refer to the "profiles" array in main.c in
    // annepro2-shine to see the order. Replace "i" with the index of your preferred profile. (i.e the RED profile is index 0)
    //0: Full red
    //1: Full green
    //2: Full blue
    //3: Horizontal rainbow
    //4: Vertical Rainbow
    //5: Low-FPS Animated Vertical Rainbow
    //6: Animated Vertical Rainbow
    //7: Animated Horizontal Rainbow
    //8: Animated Breathing
    //9: Animated Red Vertical Wave
    //10: Animated Spectrum
    //11: Reactive Fade
    annepro2LedSetProfile(12);
}

layer_state_t layer_state_set_user(layer_state_t layer) {
  switch(get_highest_layer(layer)) {
    case _FN1_LAYER:
      // Set the leds to yellow
      annepro2LedSetForegroundColor(0xFF, 0xFF, 0x00);
      break;
    case _FN2_LAYER:
      // Set the leds to violet
      annepro2LedSetForegroundColor(0x88, 0x00, 0xFF);
      break;
    case _FN3_LAYER:
      // Set the leds to cyan
      annepro2LedSetForegroundColor(0x1F, 0x73, 0x6A);
      break;
    case _FN4_LAYER:
      // Set the leds to yellow
      annepro2LedSetForegroundColor(0xFF, 0x00, 0xFF);
      break;
    default:
      // Reset back to the current profile
      annepro2LedResetForegroundColor();
      break;
  }
  return layer;
}

// The function to handle the caps lock logic
// It's called after the capslock changes state or after entering layers 1 and 2.
bool led_update_user(led_t leds) {
  if (leds.caps_lock) {
    // Set the caps-lock to red
    const annepro2Led_t color = {
        .p.red = 0xff,
        .p.green = 0x00,
        .p.blue = 0x00,
        .p.alpha = 0xff
    };

    annepro2LedMaskSetKey(2, 0, color);
    /* NOTE: Instead of colouring the capslock only, you can change the whole
       keyboard with annepro2LedSetForegroundColor */
  } else {
    // Reset the capslock if there is no layer active
    if(!layer_state_is(_FN1_LAYER) && !layer_state_is(_FN2_LAYER)) {
      const annepro2Led_t color = {
          .p.red = 0xff,
          .p.green = 0x00,
          .p.blue = 0x00,
          .p.alpha = 0x00
      };
      annepro2LedMaskSetKey(2, 0, color); // row#, col#, color... so kann die Farb-Einstellung nur für spezielle Tasten gelten
    }
  }

  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) { //For keycode overrides
		case ATABF:	//Alt tab forwards
		  if (record->event.pressed) {
			if (!is_alt_tab_active) {
			  is_alt_tab_active = true;
			  register_code(KC_LALT);
			}
			alt_tab_timer = timer_read();
			register_code(KC_TAB);
		  } else {
			unregister_code(KC_TAB);
		  }
		  return true;
		case ATABR:	//Alt tab reverse
		  if (record->event.pressed) {
			if (!is_alt_tab_active) {
			  is_alt_tab_active = true;
			  register_code(KC_LALT);
			}
			alt_tab_timer = timer_read();
			register_code(KC_LSHIFT);
			register_code(KC_TAB);
		  } else {
			unregister_code(KC_TAB);
            unregister_code(KC_LSHIFT);
		  }
		  return true;
	}
	return true;
}
