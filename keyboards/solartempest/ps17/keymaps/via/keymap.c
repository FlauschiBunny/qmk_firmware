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
    _LAYER0,
    _LAYER1,
    _LAYER2,
    _LAYER3,
    _LAYER4,
    _LAYER5,
    _LAYER6,
    _LAYER7,
    _LAYER8,
    _LAYER9
};
	  
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_LAYER0] = LAYOUT(
		KC_PGDOWN, KC__MUTE, KC_PGUP,
		MO(_LAYER1), KC_KP_SLASH, KC_KP_ASTERISK, KC_KP_MINUS,
        KC_KP_7, KC_KP_8, KC_KP_9, KC_KP_PLUS,
        KC_KP_4, KC_KP_5, KC_KP_6,
        KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_ENTER,
        KC_KP_0,          KC_KP_DOT
    ),
    [_LAYER1] = LAYOUT(
		KC_RIGHT, KC_TRNS, KC_LEFT,
        KC_TRNS, KC_MEDIA_STOP, KC_SPACE, KC_NUMLOCK,
        TO(_LAYER4), TG(_LAYER2), TG(_LAYER3), KC_BSPACE,
        KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, RESET,
        RESET,          KC_TRNS
    ),
    [_LAYER2] = LAYOUT(
		KC_RBRACKET, KC_TRNS, KC_LBRACKET,
        TO(0), KC_B, KC_T, C(S(KC_N)),
        KC_J, KC_S, KC_D, C(KC_MINS),
        C(KC_C), C(KC_V), KC_M,
        C(KC_N), C(S(KC_Z)), KC_LSHIFT, C(KC_PPLS),
        KC_SPACE,          KC_LALT
    ),
    [_LAYER3] = LAYOUT(
		ATABF, KC_TRNS, ATABR,
        TO(0), KC_WWW_REFRESH, KC_HOME, C(KC_T),
        C(S(KC_TAB)), KC_UP, C(KC_TAB), C(KC_W),
        KC_LEFT, KC_DOWN, KC_RIGHT,
        KC_WWW_BACK, KC_SPACE, KC_WWW_FORWARD, KC_ENTER,
        KC_PGDOWN,          KC_PGUP
    ),
    [_LAYER4] = LAYOUT(
		ATABF, KC_TRNS, ATABR,
        TO(0), KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_UP, KC_TRNS, KC_TRNS,
        KC_LEFT, KC_DOWN, KC_RIGHT,
        C(S(KC_M)), LWIN(KC_F4), KC_TRNS, KC_NUMLOCK,
        KC_F13,          KC_F14
    ),
    [_LAYER5] = LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,          KC_TRNS
    ),
    [_LAYER6] = LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,          KC_TRNS
    ),
    [_LAYER7] = LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,          KC_TRNS
    ),
    [_LAYER8] = LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,          KC_TRNS
    ),
    [_LAYER9] = LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,          KC_TRNS
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
			unregister_code(KC_LSHIFT);
			unregister_code(KC_TAB);
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
const rgblight_segment_t PROGMEM my_layer0_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 0, 95,255,90}); //Spring green		(Code is extra for static key lighting of layers)
const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 0, 5,255,120}); //Yellow-orange	(Code is extra for static key lighting of layers)
const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 0, 128,255,100}); //Cyan			(Code is extra for static key lighting of layers)
const rgblight_segment_t PROGMEM my_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 0, 215,255,120}); //Magenta		(Code is extra for static key lighting of layers)
const rgblight_segment_t PROGMEM my_layer4_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 0, 15,255,120}); //Orange-red		(Code is extra for static key lighting of layers)
const rgblight_segment_t *const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST( //Lighting layers
    my_layer0_layer,
    my_layer1_layer,
    my_layer2_layer,
    my_layer3_layer,
    my_layer4_layer
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
	
	/*static uint16_t underglow_brightness = 140; //This code can be used to have edge and underglow LEDs selectively brighter
	static uint16_t perkey_brightness = 80;
	static uint16_t lastrow_brightness = 50; //for less shine-through at case edges (brighter is okay for FR4 plate)
	static uint16_t current_hue = 0; //hue calculated to be used
	static uint16_t layer0_huestart = 56; //hue gradient starting colour - green/blue
	static uint16_t layer0_hueincrement = 2; //hue gradient colour increment
	static uint16_t layer1_huestart = 15; //hue gradient starting colour - orange/green
	static uint16_t layer1_hueincrement = 2; //hue gradient colour increment
	static uint16_t layer2_huestart = 220; //hue gradient starting colour - magenta/orange (this layer is for photoshop)
	static uint16_t layer2_hueincrement = 2; //hue gradient colour increment
	static uint16_t layer3_huestart = 135; //hue gradient starting colour - blue/purple
	static uint16_t layer3_hueincrement = 2; //hue gradient colour increment
	static uint16_t layer4_huestart = 30; //hue gradient starting colour - orange/red
	static uint16_t layer4_hueincrement = 1; //hue gradient colour increment
	*/
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
			rgblight_sethsv_noeeprom(50,255,100);
			/*for (uint8_t i = 0; i < RGBLED_NUM; i++){ //This code can be used to have edge and underglow LEDs selectively brighter
				current_hue=i*layer0_hueincrement+layer0_huestart; //Determine the calculated hue
				if(current_hue>255){current_hue=current_hue-255;}; //Roll over max hue of 256
				if (i == 1 || i == 3 || i == 9 || i == 18 || i == 25 || i == 27) {	  
				  rgblight_sethsv_at(current_hue,255,underglow_brightness,i);
				} else if (i == 0 || i == 2 || i == 4 || i == 14 || i == 23) { //make right side of the numpad underglow darker
				  rgblight_sethsv_at(current_hue,255,lastrow_brightness,i);
				} else if (i == 26 || i == 24 || i == 19 || i ==10) { //make per key end LEDs lighter to reduce glare
				  rgblight_sethsv_at(current_hue,255,lastrow_brightness,i);
				} else {
				  rgblight_sethsv_at(current_hue,255,perkey_brightness,i);
				};
			};*/
			break;
		case 1:
			rgblight_sethsv_noeeprom(5,255,100);
			/*for (uint8_t i = 0; i < RGBLED_NUM; i++){ //This code can be used to have edge and underglow LEDs selectively brighter
				current_hue=i*layer1_hueincrement+layer1_huestart; //Determine the calculated hue
				if(current_hue>255){current_hue=current_hue-255;}; //Roll over max hue of 256
				if (i == 1 || i == 3 || i == 9 || i == 18 || i == 25 || i == 27) {	  
				  rgblight_sethsv_at(current_hue,255,underglow_brightness,i);
				} else if (i == 0 || i == 2 || i == 4 || i == 14 || i == 23) { //make right side of the numpad underglow darker
				  rgblight_sethsv_at(current_hue,255,lastrow_brightness,i);
				} else if (i == 26 || i == 24 || i == 19 || i ==10) { //make per key end LEDs lighter to reduce glare
				  rgblight_sethsv_at(current_hue,255,lastrow_brightness,i);
				} else {
				  rgblight_sethsv_at(current_hue,255,perkey_brightness,i);
				};
			};*/
			break;
		case 2:
			rgblight_sethsv_noeeprom(128,255,100);
			/*for (uint8_t i = 0; i < RGBLED_NUM; i++){ //This code can be used to have edge and underglow LEDs selectively brighter
				current_hue=i*layer2_hueincrement+layer2_huestart; //Determine the calculated hue
				if(current_hue>255){current_hue=current_hue-255;}; //Roll over max hue of 256
				if (i == 1 || i == 3 || i == 9 || i == 18 || i == 25 || i == 27) {	  
				  rgblight_sethsv_at(current_hue,255,underglow_brightness,i);
				} else if (i == 0 || i == 2 || i == 4 || i == 14 || i == 23) { //make right side of the numpad underglow darker
				  rgblight_sethsv_at(current_hue,255,lastrow_brightness,i);
				} else if (i == 26 || i == 24 || i == 19 || i ==10) { //make per key end LEDs lighter to reduce glare
				  rgblight_sethsv_at(current_hue,255,lastrow_brightness,i);
				} else {
				  rgblight_sethsv_at(current_hue,255,perkey_brightness,i);
				};
			};*/
			break;
		case 3:
			rgblight_sethsv_noeeprom(215,255,100);
			/*for (uint8_t i = 0; i < RGBLED_NUM; i++){ //This code can be used to have edge and underglow LEDs selectively brighter
				current_hue=i*layer3_hueincrement+layer3_huestart; //Determine the calculated hue
				if(current_hue>255){current_hue=current_hue-255;}; //Roll over max hue of 256
				if (i == 1 || i == 3 || i == 9 || i == 18 || i == 25 || i == 27) {	  
				  rgblight_sethsv_at(current_hue,255,underglow_brightness,i);
				} else if (i == 0 || i == 2 || i == 4 || i == 14 || i == 23) { //make right side of the numpad underglow darker
				  rgblight_sethsv_at(current_hue,255,lastrow_brightness,i);
				} else if (i == 26 || i == 24 || i == 19 || i ==10) { //make per key end LEDs lighter to reduce glare
				  rgblight_sethsv_at(current_hue,255,lastrow_brightness,i);
				} else {
				  rgblight_sethsv_at(current_hue,255,perkey_brightness,i);
				};
			};*/
			break;
		case 4:
			rgblight_sethsv_noeeprom(15,255,100);
			/*for (uint8_t i = 0; i < RGBLED_NUM; i++){ //This code can be used to have edge and underglow LEDs selectively brighter
				current_hue=i*layer4_hueincrement+layer4_huestart; //Determine the calculated hue
				if(current_hue>255){current_hue=current_hue-255;}; //Roll over max hue of 256
				if (i == 1 || i == 3 || i == 9 || i == 18 || i == 25 || i == 27) {	  
				  rgblight_sethsv_at(current_hue,255,underglow_brightness,i);
				} else if (i == 0 || i == 2 || i == 4 || i == 14 || i == 23) { //make right side of the numpad underglow darker
				  rgblight_sethsv_at(current_hue,255,lastrow_brightness,i);
				} else if (i == 26 || i == 24 || i == 19 || i ==10) { //make per key end LEDs lighter to reduce glare
				  rgblight_sethsv_at(current_hue,255,lastrow_brightness,i);
				} else {
				  rgblight_sethsv_at(current_hue,255,perkey_brightness,i);
				};
			};*/
			break;
	  }
    return state;
	};
#endif
