#include <string.h>
#include QMK_KEYBOARD_H

enum layer_number {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_MINS, LCTL_T(KC_ESC), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_DEL, KC_BSLS, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_EQL, KC_LALT, KC_LGUI, MO(1), KC_ENT, KC_SPC, MO(2), KC_LBRC, KC_RBRC),
	[1] = LAYOUT(KC_NO, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_F11, KC_F12, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_PLUS, KC_EQL, KC_BSLS, KC_PIPE, KC_NO, KC_NO, KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, MO(3), KC_NO, KC_NO),
	[2] = LAYOUT(KC_SLEP, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_PGDN, KC_UP, KC_PGUP, KC_NO, KC_NO, KC_LCTL, KC_BRID, KC_BRIU, KC_VOLD, KC_VOLU, KC_MUTE, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_LALT, KC_LGUI, MO(3), KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO),
	[3] = LAYOUT(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

char os[10] = "";

bool process_detected_host_os_kb(os_variant_t detected_os) {
    if (!process_detected_host_os_user(detected_os)) {
        return false;
    }
    switch (detected_os) {
        case OS_MACOS:
            strcpy(os, "MacOS");
            break;
        case OS_IOS:
            strcpy(os, "IOS");
            break;
        case OS_WINDOWS:
            strcpy(os, "Windows");
            break;
        case OS_LINUX:
            strcpy(os, "Linux");
            break;
        case OS_UNSURE:
            strcpy(os, "");
            break;
    }

    return true;
}

//SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
      return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  } else {
      return OLED_ROTATION_270;
  }
  return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// Handwritten zukuo
/* static void render_logo(void) { */
/*     static const char PROGMEM qmk_logo[] = { */
/*         0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,192, 64,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  8, 48,224,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128, 96,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128, 64, 48, 16, 16, 16, 16, 16, 16, 32, 32, 64, 64,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, */
/*         0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128, 64, 64, 32, 16,  8,  4,  2,  1,  0,  0,  0,  0,  0,  0,  0,  0,124,128,  0,  0,  0,  0,  0,  0,  0,255, 15, 48,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,252,  0,  0,  0,192,112,142,129,  0,  0,  0,  0,  0,  0,  0,254,  0,  0,  0,  0,  0,  0,  7, 31,248,128,  0,  0,  0,  0,  0,  0,  0, 30,  1,  0,  0,  0,  0,  0,  0,192,  0,  0,  0,  0,  0,  0,  0,  1,  2,  2,  4,  8, 48,192,  0,  0,  0,  0,  0,  0,  0, */
/*         0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,224,176,152,132,130,130,129, 64, 64, 64, 64, 64, 64, 32, 32, 32, 32, 32, 32, 32, 32, 16,  0,  0,  7, 24, 16, 32, 32, 16, 16, 15,  0,  0,  0,  0,  3, 28, 32, 32, 64, 64,  0,  0,  0,  0,  0,  0,127, 32, 28,  3,  0,  0,  0,  0,  1,  2,  4,  4,  0,  0,  0,  1, 30, 96,128,  0,  0,  0,128,128,127,  7, 24, 32, 32,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,  4,  8, 16, 16, 32, 64, 64, 64, 64,128,128, 64, 32, 24,  7,  0,  0,  0,  0,  0,  0, */
/*         0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, */
/*     }; */

/*     oled_write_raw_P(qmk_logo, sizeof(qmk_logo)); */
/* } */

// Moving Car Logo
static void render_logo(void) {
    static const char PROGMEM raw_logo[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,254,254,  6,  6,230,230,248,248,248,248,102,102,254,254,  6,  6,  6,  6,  6,  6,  6,  6,248,248,248,248,248,248, 24, 24, 24, 24,120,120, 96, 96,224,224,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,255,255,120,120, 25, 25,  7,  7, 31, 31, 30, 30,159,159,128,128,152,152,152,152,120,120,127,127,103,103,  7,  7,  0,  0,  0,  0, 24, 24, 24, 24,  1,  1,255,255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0, 31, 31,120,120,126,126,102,102,126,126,120,120,127,127,127,127,127,127,121,121,120,120,120,120,120,120,126,126,102,102,126,126,120,120,120,120,126,126, 31, 31,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,
    };
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {

        switch (get_highest_layer(layer_state)) {
            case 3:
                oled_write("ADJ", false);
                oled_write_ln("\n", false);
                break;
            case 2:
                oled_write("RAISE\n", false);
                break;
                // Layer 1
            case 1:
                oled_write("LOWER\n", false);
                break;
                // Layer 0
            default:
                oled_write("BASE", false);
                oled_write_ln("\n", false);
                break;
        }

        oled_write_ln("OS:", false);
        oled_write_ln(os, false);

    } else {
        render_logo();
        oled_scroll_right();
    }
    return false;
}
#endif // OLED_ENABLE
