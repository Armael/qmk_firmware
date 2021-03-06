/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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
#include "keymap_bepo.h"
#include "sendstring_bepo.h"

enum layers {
    _MAIN = 0,
    _ALEPH,
    _BETH,
    _ALEPH_P,
    _GIMEL,
    _DALET
};

enum custom_keycodes {
    MYKC_ESPLT = SAFE_RANGE,
    MYKC_EBEGN,
    MYKC_EEND,
    MYKC_EPREV,
    MYKC_ENEXT,
    MYKC_ECLOSE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |   Z    |   B  |   É  |   P  |   O  |   È  |                              |   ^! |   V  |   D  |   L  |   J  |  W     |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |  Ctrl  |  A   |  U   |  I   |  E   |   ,  |                              |   C  |  T   |  S   |   R  |   N  |   M    |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |  Shift |   À  |   Y  |   X  |   .  |   K  | esc  |      |  |      | Gimel|   '? |   Q  |  G   |  H   |   F  |  Ç     |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |Dalet |Super | Space| Enter| Tab  |  |bkspc | Enter| Aleph| Super|Dalet |
 *                        |      |      | Bet  | Alt  |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 *
* caps word? : https://github.com/andrewjrae/qmk_firmware/blob/kyria/keyboards/kyria/keymaps/ajrae/keymap.c
* (on double tap shift)
 */
    [_MAIN] = LAYOUT(
          BP_Z,    BP_B, BP_EACU,   BP_P,   BP_O,   BP_EGRV,                                               BP_DCIR,    BP_V,    BP_D,    BP_L,    BP_J,    BP_W,
       KC_LCTL,    BP_A,    BP_U,   BP_I,   BP_E,   BP_COMM,                                                  BP_C,    BP_T,    BP_S,    BP_R,    BP_N,    BP_M,
       KC_LSFT, BP_AGRV,    BP_Y,   BP_X, BP_DOT,      BP_K,   KC_ESC, _______,    _______, MO(_GIMEL),    BP_QUOT,    BP_Q,    BP_G,    BP_H,    BP_F, BP_CCED,
         OSL(_DALET), KC_LGUI, LT(_BETH, KC_SPC), MT(MOD_LALT, KC_ENT), KC_TAB,    KC_BSPC,     KC_ENT, MO(_ALEPH), KC_RGUI, OSL(_DALET)
    ),
/*
 * Aleph Layer: Symbols and intl/fr
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |   $    |  "   |  /(«)|  \(»)|  œ   |  `   |                              |  @   |  <   |  >   |  /   |  *   |  %     |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  |   |  ù   |  ¨(D)|  &   |  +   |                              |  #   |  (   |  )   |  =   |  -   |  °     |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  æ   |  {   |   }  |  :   |  ~   |      |      |  |      |      |  °(D)|  [   |  ]   |  μ(D)|      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |  _   |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_ALEPH] = LAYOUT(
           BP_DLR, BP_DQUO, BP_LDAQ, BP_RDAQ,   BP_OE,  BP_GRV,                                           BP_AT, BP_LABK, BP_RABK, BP_SLSH, BP_ASTR, BP_PERC,
          _______, BP_PIPE, BP_UGRV, BP_DIAE, BP_AMPR, BP_PLUS,                                         BP_HASH, BP_LPRN, BP_RPRN,  BP_EQL, BP_MINS,  BP_DEG,
          _______,   BP_AE, BP_LCBR, BP_RCBR, BP_COLN, BP_TILD, _______, _______,     _______, _______, BP_RNGA, BP_LBRC, BP_RBRC, BP_DGRK, _______, _______,
                                     _______, _______, BP_UNDS, _______, _______,     _______, _______, _______, _______, _______
    ),
/*
 * Beth Layer: Number keys, media, navigation
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  1   |  2   |  3   |   4  |   5  |                              |  6   |  7   |  8   |  9   |  0   |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        | Left |  Up  | Down | Right|VolUp |                              | Del  | Home |PgDown| PgUp | End  |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |VolDwn| Mute |      |  |      |      | Ins  |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |Aleph+|      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_BETH] = LAYOUT(
      _______,    BP_1,    BP_2,    BP_3,    BP_4,    BP_5,                                        BP_6,    BP_7,      BP_8,     BP_9,    BP_0, _______,
      _______, KC_LEFT,   KC_UP, KC_DOWN, KC_RGHT, KC_VOLU,                                      KC_DEL, KC_HOME, KC_PGDOWN,  KC_PGUP,  KC_END, _______,
      _______, _______, _______, _______, _______, KC_VOLD, KC_MUTE, _______, _______, _______,  KC_INS, _______,   _______,  _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, MO(_ALEPH_P), _______, _______
    ),
/*
 * Aleph+: remaining bits of the altgr layer (mostly intl dead keys)
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |  ´(D)|  §   |      |  `(D)|                              |      |      |  ð   |  ø(D)|      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |      |   €  |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |   …  |      |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |  _   |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_ALEPH_P] = LAYOUT(
      _______, _______, BP_ACUT, BP_SECT, _______, BP_DGRV,                                     _______, _______,  BP_ETH, BP_DSLS, _______, _______,
      _______, _______, _______, _______, BP_EURO, _______,                                     _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, BP_ELLP, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, BP_UNDS, _______, _______, _______, _______, _______, _______, _______, _______
    ),
/*
 * Gimel Layer: Function keys, RGB
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        | F1   |  F2  | F3   | F4   | F5   |                              | F6   | F7   |  F8  | F9   | F10  |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        | TOG  | SAI  | HUI  | VAI  | MOD  |                              |      |      |      | F11  | F12  |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      | SAD  | HUD  | VAD  | RMOD |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_GIMEL] = LAYOUT(
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
      _______, RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI, RGB_MOD,                                     _______, _______, _______, KC_F11,  KC_F12,  _______,
      _______, _______, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD,_______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
/*
 * Dalet layer: macros
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |                              |      | EPREV| EEND | EBEGN| ENEXT|        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |      |ECLOSE| ESPLT|      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      | Space|      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_DALET] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,                          _______, MYKC_EPREV, MYKC_EEND, MYKC_EBEGN, MYKC_ENEXT, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, MYKC_ECLOSE, MYKC_ESPLT, _______, _______, _______,
                                 _______, _______,  KC_SPC, _______, _______, _______, _______, _______, _______, _______
    )
// /*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),
};

/* const uint16_t PROGMEM combo_1[] = {BP_A, BP_B, COMBO_END}; */
/* const uint16_t PROGMEM combo_2[] = {BP_U, BP_EACU, COMBO_END}; */
/* const uint16_t PROGMEM combo_3[] = {BP_I, BP_P, COMBO_END}; */
/* const uint16_t PROGMEM combo_4[] = {BP_E, BP_O, COMBO_END}; */
/* const uint16_t PROGMEM combo_5[] = {BP_COMM, BP_EGRV, COMBO_END}; */
/* const uint16_t PROGMEM combo_6[] = {BP_C, BP_DCIR, COMBO_END}; */
/* const uint16_t PROGMEM combo_7[] = {BP_T, BP_V, COMBO_END}; */
/* const uint16_t PROGMEM combo_8[] = {BP_S, BP_D, COMBO_END}; */
/* const uint16_t PROGMEM combo_9[] = {BP_R, BP_L, COMBO_END}; */
/* const uint16_t PROGMEM combo_0[] = {BP_N, BP_J, COMBO_END}; */

/* combo_t key_combos[COMBO_COUNT] = { */
/*   COMBO(combo_1, BP_1), */
/*   COMBO(combo_2, BP_2), */
/*   COMBO(combo_3, BP_3), */
/*   COMBO(combo_4, BP_4), */
/*   COMBO(combo_5, BP_5), */
/*   COMBO(combo_6, BP_6), */
/*   COMBO(combo_7, BP_7), */
/*   COMBO(combo_8, BP_8), */
/*   COMBO(combo_9, BP_9), */
/*   COMBO(combo_0, BP_0), */
/* }; */

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case MYKC_EPREV:
      if (record->event.pressed) {
          SEND_STRING(SS_LCTL("x")"p");
      }
      return false; // Skip all further processing of this key
    case MYKC_ENEXT:
      if (record->event.pressed) {
          SEND_STRING(SS_LCTL("x")"o");
      }
      return false;
    case MYKC_ECLOSE:
      if (record->event.pressed) {
          SEND_STRING(SS_LCTL("x")"0"SS_LCTL("x")"+");
      }
      return false;
    case MYKC_ESPLT:
      if (record->event.pressed) {
          SEND_STRING(SS_LCTL("x")"3"SS_LCTL("x")"+");
      }
      return false;
    case MYKC_EBEGN:
      if (record->event.pressed) {
          SEND_STRING(SS_LALT("<"));
      }
      return false;
    case MYKC_EEND:
      if (record->event.pressed) {
          SEND_STRING(SS_LALT(">"));
      }
      return false;
    default:
      return true; // Process all other keycodes normally
  }
}

#ifdef RGBLIGHT_ENABLE
void keyboard_post_init_user(void) {
  rgblight_enable_noeeprom(); // Enables RGB, without saving settings
  rgblight_sethsv_noeeprom(HSV_WHITE);
  rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
}
#endif


oled_rotation_t oled_init_user(oled_rotation_t rotation) {
	return OLED_ROTATION_180;
}

static void render_kyria_logo(void) {
    static const char PROGMEM kyria_logo[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,192,224,240,112,120, 56, 60, 28, 30, 14, 14, 14,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 14, 14, 14, 30, 28, 60, 56,120,112,240,224,192,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,192,224,240,124, 62, 31, 15,  7,  3,  1,128,192,224,240,120, 56, 60, 28, 30, 14, 14,  7,  7,135,231,127, 31,255,255, 31,127,231,135,  7,  7, 14, 14, 30, 28, 60, 56,120,240,224,192,128,  1,  3,  7, 15, 31, 62,124,240,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,240,252,255, 31,  7,  1,  0,  0,192,240,252,254,255,247,243,177,176, 48, 48, 48, 48, 48, 48, 48,120,254,135,  1,  0,  0,255,255,  0,  0,  1,135,254,120, 48, 48, 48, 48, 48, 48, 48,176,177,243,247,255,254,252,240,192,  0,  0,  1,  7, 31,255,252,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,255,255,255,  0,  0,  0,  0,  0,254,255,255,  1,  1,  7, 30,120,225,129,131,131,134,134,140,140,152,152,177,183,254,248,224,255,255,224,248,254,183,177,152,152,140,140,134,134,131,131,129,225,120, 30,  7,  1,  1,255,255,254,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0,255,255,  0,  0,192,192, 48, 48,  0,  0,240,240,  0,  0,  0,  0,  0,  0,240,240,  0,  0,240,240,192,192, 48, 48, 48, 48,192,192,  0,  0, 48, 48,243,243,  0,  0,  0,  0,  0,  0, 48, 48, 48, 48, 48, 48,192,192,  0,  0,  0,  0,  0,
        0,  0,  0,255,255,255,  0,  0,  0,  0,  0,127,255,255,128,128,224,120, 30,135,129,193,193, 97, 97, 49, 49, 25, 25,141,237,127, 31,  7,255,255,  7, 31,127,237,141, 25, 25, 49, 49, 97, 97,193,193,129,135, 30,120,224,128,128,255,255,127,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0, 63, 63,  3,  3, 12, 12, 48, 48,  0,  0,  0,  0, 51, 51, 51, 51, 51, 51, 15, 15,  0,  0, 63, 63,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48, 48, 63, 63, 48, 48,  0,  0, 12, 12, 51, 51, 51, 51, 51, 51, 63, 63,  0,  0,  0,  0,  0,
        0,  0,  0,  0, 15, 63,255,248,224,128,  0,  0,  3, 15, 63,127,255,239,207,141, 13, 12, 12, 12, 12, 12, 12, 12, 30,127,225,128,  0,  0,255,255,  0,  0,128,225,127, 30, 12, 12, 12, 12, 12, 12, 12, 13,141,207,239,255,127, 63, 15,  3,  0,  0,128,224,248,255, 63, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  3,  7, 15, 62,124,248,240,224,192,128,  1,  3,  7, 15, 30, 28, 60, 56,120,112,112,224,224,225,231,254,248,255,255,248,254,231,225,224,224,112,112,120, 56, 60, 28, 30, 15,  7,  3,  1,128,192,224,240,248,124, 62, 15,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  7, 15, 14, 30, 28, 60, 56,120,112,112,112,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,112,112,112,120, 56, 60, 28, 30, 14, 15,  7,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
    };
    oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
}

/* static void render_qmk_logo(void) { */
/*   static const char PROGMEM qmk_logo[] = { */
/*     0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94, */
/*     0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4, */
/*     0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0}; */

/*   oled_write_P(qmk_logo, false); */
/* } */

bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(_BETH, KC_SPC):
            return true;
        default:
            return false;
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    /* if (get_highest_layer(state) == _ALEPH && (get_mods() & MOD_MASK_SHIFT)) { */
    /*     layer_on(_ALEPH_P); */
    /*     layer_off(_ALEPH); */
    /* } */
    /* state = update_tri_layer_state(state, _BETH, _ALEPH, _ALEPH_P); */

    /* if (IS_LAYER_ON_STATE(state, _ALEPH)) { */
    /*     if (get_mods() & MOD_MASK_SHIFT) */
    /*         state = state | (1UL << _ALEPH_P); */
    /*     else */
    /*         state = state & ~(1UL << _ALEPH_P); */
    /* } */
    /* if (IS_LAYER_OFF_STATE(state, _ALEPH)) { */
    /*     state = state & ~(1UL << _ALEPH_P); */
    /* } */
    return state;
}

static void render_status(void) {
    // QMK Logo and version information
    /* render_qmk_logo(); */
    /* oled_write_P(PSTR("Kyria rev1.0\n\n"), false); */

    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case _MAIN:
            oled_write_P(PSTR("Main\n"), false);
            break;
        case _ALEPH:
            oled_write_P(PSTR("Aleph\n"), false);
            break;
        case _ALEPH_P:
            oled_write_P(PSTR("Aleph+\n"), false);
            break;
        case _BETH:
            oled_write_P(PSTR("Beth\n"), false);
            break;
        case _GIMEL:
            oled_write_P(PSTR("Gimel\n"), false);
            break;
        case _DALET:
            oled_write_P(PSTR("Dalet\n"), false);
            break;
        default:
            oled_write_P(PSTR("?\n"), false);
    }

    // Host Keyboard LED Status
    uint8_t led_usb_state = host_keyboard_leds();
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_NUM_LOCK) ? PSTR("NUMLCK ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_CAPS_LOCK) ? PSTR("CAPLCK ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_SCROLL_LOCK) ? PSTR("SCRLCK ") : PSTR("       "), false);
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status(); // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_kyria_logo();
    }
}
