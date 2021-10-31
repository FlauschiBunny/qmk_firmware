/* Copyright
 *   2021 solartempest
 *   2021 QMK
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "PS17.h"
#ifdef RGBLIGHT_ENABLE
	extern rgblight_config_t rgblight_config; // To pull layer status for RGBLIGHT
#endif

bool is_alt_tab_active = false; // Super Alt Tab Code
uint16_t alt_tab_timer = 0;
bool spam_arrow;
uint16_t spam_timer = false;
uint16_t spam_interval = 1000; // (1000ms == 1s)
#ifdef VIA_ENABLE
	enum custom_keycodes { //Use USER 00 instead of SAFE_RANGE for Via. VIA json must include the custom keycode.
	  ATABF = USER00, //Alt tab forwards
	  ATABR, //Alt tab reverse
	  NMR, //Move window to monitor on right
	  NML, //Move window to monitor on left
	  SPAMARROW //Spam arrows
	};
#else
	enum custom_keycodes { //Use USER 00 instead of SAFE_RANGE for Via. VIA json must include the custom keycode.
	  ATABF = SAFE_RANGE, //Alt tab forwards
	  ATABR, //Alt tab reverse
	  NMR, //Move window to monitor on right
	  NML, //Move window to monitor on left
	  SPAMARROW //Spam arrows
	};
#endif

#ifdef COMBO_ENABLE //Tap combos
	enum combos {
	  kppls_7, //Hold plus and 7 to backspace
	  kppls_8, //Hold plus and 8 to delete
	  kpent_4, //Hold enter and 4 for left arrow
	  kpent_5, //Hold enter and 5 for down arrow
	  kpent_6, //Hold enter and 6 for right arrow
	  kpent_8, //Hold enter and 4'8 for up arrow
	};
	const uint16_t PROGMEM kppls7_combo[] = {KC_KP_PLUS, KC_KP_7, COMBO_END};
	const uint16_t PROGMEM kppl8_combo[] = {KC_KP_PLUS, KC_KP_8, COMBO_END};
	const uint16_t PROGMEM kpent4_combo[] = {KC_PENT, KC_KP_4, COMBO_END};
	const uint16_t PROGMEM kpent5_combo[] = {KC_PENT, KC_KP_5, COMBO_END};
	const uint16_t PROGMEM kpent6_combo[] = {KC_PENT, KC_KP_6, COMBO_END};
	const uint16_t PROGMEM kpent8_combo[] = {KC_PENT, KC_KP_8, COMBO_END};
	combo_t key_combos[COMBO_COUNT] = {
	  [kppls_7] = COMBO(kppls7_combo, KC_BSPACE),
	  [kppls_8] = COMBO(kppl8_combo, KC_DELETE),
	  [kpent_4] = COMBO(kpent4_combo, KC_LEFT),
	  [kpent_5] = COMBO(kpent5_combo, KC_DOWN),
	  [kpent_6] = COMBO(kpent6_combo, KC_RGHT),
	  [kpent_8] = COMBO(kpent8_combo, KC_UP)
	};
#endif

#ifdef TAP_DANCE_ENABLE// Tap Dance definitions. Not VIA compatible.
	enum {
		TD_MINUS_NUMLOCK,
	};
	qk_tap_dance_action_t tap_dance_actions[] = {
		// Tap once for Escape, twice for Caps Lock
		[TD_MINUS_NUMLOCK] = ACTION_TAP_DANCE_DOUBLE(KC_KP_MINUS, KC_NUMLOCK),
	};
	//TD(TD_MINUS_NUMLOCK) // Add tap dance item to your keymap in place of a keycode (non-VIA only)
#endif


enum layer_names {
    _LAYER_NUMPAD,
    _LAYER_BROWSER,
    _LAYER_VS_CODE,
    _LAYER_MEDIA,
    _LAYER_CURSOR,
    _LAYER_MOUSE,
    _LAYER_F_KEYS,
    _LAYER_OFFICE,
    _LAYER_WINDOWS,
    _LAYER_FREE1,
    _LAYER_SELECT //Layer selection, must be highest layer
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_LAYER_NUMPAD] = LAYOUT(
		KC_PGDOWN, KC__MUTE, KC_PGUP,
		KC_NUMLOCK, KC_KP_SLASH, KC_KP_ASTERISK, KC_KP_MINUS,
        KC_KP_7, KC_KP_8, KC_KP_9, KC_KP_PLUS,
        KC_KP_4, KC_KP_5, KC_KP_6,
        KC_KP_1, KC_KP_2, KC_KP_3, MO(_LAYER_SELECT),
        KC_KP_0,          KC_KP_DOT
    ),
    [_LAYER_BROWSER] = LAYOUT(
		C(KC_TAB), C(KC_T), C(S(KC_TAB)),
        ATABF, LWIN(KC_TAB), ATABR, LALT(KC_F4),
        KC_WWW_HOME, KC_F11, KC_WWW_FAVORITES, KC_WWW_REFRESH,
        KC_WWW_BACK, KC_WWW_SEARCH, KC_WWW_FORWARD,
        C(KC_F), C(KC_E), C(KC_L), MO(_LAYER_SELECT),
        C(S(KC_P)),          KC_TRNS
    ),
    [_LAYER_VS_CODE] = LAYOUT(
		ATABF, LWIN(KC_TAB), ATABR,
        KC_F5, KC_F10, KC_F11, KC_F9, //Start debug, step over, step into, toggle breakpoint
        KC_F12, LALT(KC_F12), C(KC_BSLASH), C(KC_N), // open definition, peek definition, split editor, new file
        C(S(KC_TAB)), C(S(KC_P)), C(KC_TAB), //prev editor, open command panel, next editor
        C(KC_H), KC_F3, S(KC_F3), MO(_LAYER_SELECT), //search/replace, find next, find prev
        C(KC_E),          S(KC_F12) //search file, show references
    ),
    [_LAYER_MEDIA] = LAYOUT(
		KC_VOLU, KC_MUTE, KC_VOLD,
        ATABF, LWIN(KC_TAB), ATABR, LALT(KC_F4),
        KC_MEDIA_REWIND, KC_MEDIA_STOP, KC_MEDIA_FAST_FORWARD, KC_WWW_SEARCH,
        KC_MEDIA_PREV_TRACK, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_NEXT_TRACK,
        C(S(KC_TAB)), KC_MEDIA_EJECT, C(KC_TAB), MO(_LAYER_SELECT),
        C(S(KC_M)),          KC_TRNS
    ),
    [_LAYER_MOUSE] = LAYOUT(
		KC_MS_WH_DOWN, KC_MS_BTN3, KC_MS_WH_UP,
        ATABF, LWIN(KC_TAB), ATABR, LALT(KC_F4),
        KC_MS_BTN4, KC_MS_UP, KC_MS_BTN5, KC_MS_BTN2,
        KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT,
        KC_MS_ACCEL0, KC_MS_ACCEL1, KC_MS_ACCEL2, MO(_LAYER_SELECT),
        KC_MS_BTN1,          KC_TRNS
    ),
    [_LAYER_CURSOR] = LAYOUT(
		ATABF, LWIN(KC_TAB), ATABR,
        KC_UNDO, KC_CUT, KC_COPY, KC_PASTE,
        KC_HOME, KC_UP, KC_END, KC_LCTRL,
        KC_LEFT, KC_DOWN, KC_RIGHT,
        KC_DEL, KC_SPACE, KC_BSPACE, MO(_LAYER_SELECT),
        KC_LSHIFT,          KC_LALT
    ),
    [_LAYER_F_KEYS] = LAYOUT(
		ATABF, LWIN(KC_TAB), ATABR,
        KC_F1, KC_F1, KC_F1, KC_PSCREEN,
        KC_F1, KC_F1, KC_F1, KC_SCROLLLOCK,
        KC_F1, KC_F1, KC_F1,
        KC_F1, KC_F1, KC_F1, MO(_LAYER_SELECT),
        KC_ESCAPE,          KC_PAUSE
    ),
    [_LAYER_OFFICE] = LAYOUT(
		ATABF, LWIN(KC_TAB), ATABR,
        C(KC_1),  C(KC_2),  C(KC_3),  C(KC_4), //Switch messages, calendar, contacts, tasks
        C(KC_E), LALT(S(KC_UP)), C(KC_K), C(S(KC_U)), //search, move element up, new link, start Teams video call
        LALT(S(KC_LEFT)), LALT(S(KC_DOWN)), LALT(S(KC_RIGHT)), //indent left, move element down, indent right
        LWIN(KC_DOT), C(KC_EQUAL), C(KC_MINUS), MO(_LAYER_SELECT), //Emoji menu, zoom out, zoom in
        C(S(KC_M)),          C(S(KC_K)) // mute/new message, raise hand in Teams
    ),
    [_LAYER_WINDOWS] = LAYOUT(
		ATABF, LWIN(KC_TAB), ATABR,
        C(LWIN(KC_LEFT)), LWIN(KC_D), C(LWIN(KC_RIGHT)), LALT(KC_F4),
        LALT(S(KC_TAB)), LWIN(KC_UP), LALT(KC_TAB), KC_TRNS,
        LWIN(KC_LEFT), LWIN(KC_DOWN), LWIN(KC_RIGHT),
        LWIN(KC_E), KC_CALC, LWIN(KC_L), MO(_LAYER_SELECT),
        KC_LWIN,          KC_MY_COMPUTER
    ),
    [_LAYER_FREE1] = LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, MO(_LAYER_SELECT),
        KC_TRNS,          KC_TRNS
    ),
    [_LAYER_SELECT] = LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        TO(_LAYER_OFFICE), TO(_LAYER_WINDOWS), TO(_LAYER_FREE1), KC_TRNS,
        TO(_LAYER_MOUSE), TO(_LAYER_CURSOR), TO(_LAYER_F_KEYS),
        TO(_LAYER_BROWSER), TO(_LAYER_VS_CODE), TO(_LAYER_MEDIA), MO(_LAYER_SELECT),
        TO(_LAYER_NUMPAD),          RESET
    )
};


void matrix_init_user(void) { //run when matrix is initiated, before all features init
};

void matrix_scan_user(void) { //run whenever user matrix is scanned
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1000) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
  if (spam_arrow && timer_elapsed(spam_timer) >= spam_interval) {
    spam_timer = timer_read();
    tap_code(KC_UP);
    tap_code(KC_DOWN);
  }
};

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

		case NMR:	//Move window to next monitor on right
		  if (record->event.pressed) {
			register_code(KC_LSFT);
			register_code(KC_LWIN);
			register_code(KC_RIGHT);
			unregister_code(KC_RIGHT);
			unregister_code(KC_LWIN);
			unregister_code(KC_LSFT);
		  }
		  return true;
		case NML:	//Move window to next monitor on left
		  if (record->event.pressed) {
			register_code(KC_LSFT);
			register_code(KC_LWIN);
			register_code(KC_LEFT);
			unregister_code(KC_LEFT);
			unregister_code(KC_LWIN);
			unregister_code(KC_LSFT);
		  }
		  return true;

		case SPAMARROW: // Moves arrow up and down
		  if (record->event.pressed) {
			spam_arrow ^= 1;
			spam_timer = timer_read();
			if(spam_arrow==1) { //Change LED colour on bottom row to orange to indicate on
				rgblight_sethsv_at(15,255,120,24);
				rgblight_sethsv_at(15,255,120,26);
				}
			else {
				rgblight_sethsv_at(180,255,120,24); //Set LEDs back to purple, assuming on that coloured layer
				rgblight_sethsv_at(180,255,120,26);
				}
		  }
		  return false;
	}
	return true;
}


// RGB Layer Light Settings - Note that this will fix the key switch LED colour and brightness
const rgblight_segment_t PROGMEM my_layer0_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 0, 95,255,90}); //Spring green     (Code is extra for static key lighting of layers)
const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 0, 255,69,0}); //Orange-red    	(Code is extra for static key lighting of layers)
const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 0, 100,149,237}); //Cornflower	    (Code is extra for static key lighting of layers)
const rgblight_segment_t PROGMEM my_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 0, 50,205,50}); //	Lime Green   	(Code is extra for static key lighting of layers)
const rgblight_segment_t PROGMEM my_layer4_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 0, 255,215,0}); //Gold            	(Code is extra for static key lighting of layers)
const rgblight_segment_t PROGMEM my_layer5_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 0, 0,0,139}); //Dark blue  		(Code is extra for static key lighting of layers)
const rgblight_segment_t PROGMEM my_layer6_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 0, 75,0,130}); //Indigo    		(Code is extra for static key lighting of layers)
const rgblight_segment_t PROGMEM my_layer7_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 0, 186,85,211}); //Medium orchid	(Code is extra for static key lighting of layers)
const rgblight_segment_t PROGMEM my_layer8_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 0, 0,100,0}); //Dark green     	(Code is extra for static key lighting of layers)
const rgblight_segment_t PROGMEM my_layer9_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 0, 210,105,30}); //Chocolate		(Code is extra for static key lighting of layers)
const rgblight_segment_t PROGMEM my_layer10_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 0, 255,255,255}); //White		(Code is extra for static key lighting of layers)
const rgblight_segment_t *const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST( //Lighting layers
    my_layer0_layer,
    my_layer1_layer,
    my_layer2_layer,
    my_layer3_layer,
    my_layer4_layer,
    my_layer5_layer,
    my_layer6_layer,
    my_layer7_layer,
    my_layer8_layer,
    my_layer9_layer,
    my_layer10_layer
);


void keyboard_post_init_user(void) {	//run as last task in keyboard init
  #ifdef RGB_MATRIX_ENABLE
    //NOTE 1: Layer lighting doesn't work in RGB matrix mode
	//NOTE 2: VIA lighting tab doesn't work and will crash in RGB matrix mode
	//NOTE 3: VIA layers doesn't seem to work properly in RGB matrix mode
	//rgb_matrix_enable_noeeprom(); //turn on RGB matrix based on previous state
	rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE); //set initial RGB matrix mode
	rgb_matrix_sethsv_noeeprom(50, 255, 100); //sets LED to green-yellow
  #endif
  #ifdef RGBLIGHT_ENABLE
    rgblight_layers = my_rgb_layers;// Enable the LED layers
	rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_GRADIENT+8); //Set to static gradient 9
	layer_move(0); //start on layer 0 to get the lighting activated
  #endif
};


#ifdef RGBLIGHT_ENABLE
layer_state_t layer_state_set_user(layer_state_t state) {
	rgblight_set_layer_state(0, layer_state_cmp(state, 0));    // Multiple layers will light up if both kb layers are active
    rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, layer_state_cmp(state, 2));
    rgblight_set_layer_state(3, layer_state_cmp(state, 3));
    rgblight_set_layer_state(4, layer_state_cmp(state, 4));
	rgblight_set_layer_state(5, layer_state_cmp(state, 5));
    rgblight_set_layer_state(6, layer_state_cmp(state, 6));
    rgblight_set_layer_state(7, layer_state_cmp(state, 7));
    rgblight_set_layer_state(8, layer_state_cmp(state, 8));
    rgblight_set_layer_state(9, layer_state_cmp(state, 9));
    rgblight_set_layer_state(10, layer_state_cmp(state, 10));

	// This is what the LED layout is.
	// 1,                 0,
	// 3,                 2,
	// 9,   8, 7,  6,  5, 4,
	// 13, 12, 11, 10,
	// 18, 17, 16, 15,    14,
	// 22, 21, 20, 19,
	// 27, 26, 25, 24,    23

	switch(biton32(state)){ // Change all other LEDs based on layer state as well
		case 0:
			rgblight_sethsv_noeeprom(HSV_RED);
			break;
		case 1:
			rgblight_sethsv_noeeprom(HSV_ORANGE);
			break;
		case 2:
			rgblight_sethsv_noeeprom(HSV_AZURE);
			break;
		case 3:
			rgblight_sethsv_noeeprom(HSV_SPRINGGREEN);
			break;
		case 4:
			rgblight_sethsv_noeeprom(HSV_GOLD);
			break;
		case 5:
			rgblight_sethsv_noeeprom(HSV_TURQUOISE);
			break;
		case 6:
			rgblight_sethsv_noeeprom(HSV_CHARTREUSE);
			break;
		case 7:
			rgblight_sethsv_noeeprom(HSV_PURPLE);
			break;
		case 8:
			rgblight_sethsv_noeeprom(HSV_BLUE);
			break;
		case 9:
			rgblight_sethsv_noeeprom(HSV_YELLOW);
			break;
		case 10:
			rgblight_sethsv_noeeprom(HSV_WHITE);
			break;
	  }
    return state;
	};
#endif
