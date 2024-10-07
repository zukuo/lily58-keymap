#include <string.h>
#include "oled_driver.h"
#include QMK_KEYBOARD_H

enum layer_number {
    _QWERTY = 0,
    _LOWER,
    _RAISE,
    _ADJUST,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_MINS, LCTL_T(KC_ESC), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_DEL, KC_BSLS, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_EQL, KC_LALT, KC_LGUI, MO(1), KC_ENT, KC_SPC, MO(2), KC_LBRC, KC_RBRC),
    [1] = LAYOUT(KC_NO, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_F11, KC_F12, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_PLUS, KC_EQL, KC_BSLS, KC_PIPE, KC_NO, KC_NO, KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, MO(3), KC_NO, KC_NO),
    [2] = LAYOUT(KC_SLEP, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_PGDN, KC_UP, KC_PGUP, KC_NO, KC_NO, KC_LCTL, KC_BRID, KC_BRIU, KC_VOLD, KC_VOLU, KC_MUTE, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END, KC_NO, KC_LSFT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_LALT, KC_LGUI, MO(3), KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO),
    [3] = LAYOUT(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

//SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE

/* 32 * 14 os logos */
static const char PROGMEM windows_logo[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbc, 0xbc, 0xbe, 0xbe, 0x00, 0xbe, 0xbe, 0xbf, 0xbf, 0xbf, 0xbf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x0f, 0x0f, 0x00, 0x0f, 0x0f, 0x1f, 0x1f, 0x1f, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static const char PROGMEM mac_logo[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xf0, 0xf8, 0xf8, 0xf8, 0xf0, 0xf6, 0xfb, 0xfb, 0x38, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 0x0f, 0x1f, 0x1f, 0x0f, 0x0f, 0x1f, 0x1f, 0x0f, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static const char PROGMEM logo[] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128, 64, 32, 32, 16, 16, 16, 16, 16, 16, 16, 16, 32, 32, 64,128,128,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0, 15, 15, 15, 15, 15, 15, 15, 15,255,255,255,255, 15, 15, 15, 15,  0,  0,  0,  0,255,255,255,255,  0,  0,  0,  0,  0,  0,  0,  0,255,255,255,255,  0,  0,  0,  0,255,255,255,255,240,240,240,240, 15, 15, 15, 15,  0,  0,  0,  0,255,255,255,255,  0,  0,  0,  0,  0,  0,  0,  0,255,255,255,255,  0,  0,  0,  0,240,240,240,240, 15, 15, 15, 15, 15, 15, 15, 15,240,240,240,240,  0,  0,  0,  0,  0,240, 12,  2,  1,  0, 12,  4,  4,  6,  2,130,134,196, 76,104, 40, 56, 24, 12,  0,  1,  2, 12,240,  0,  0,  0,
    0,  0,  0,  0,240,240,240,240,255,255,255,255,240,240,240,240,240,240,240,240,  0,  0,  0,  0, 15, 15, 15, 15,240,240,240,240,240,240,240,240, 15, 15, 15, 15,  0,  0,  0,  0,255,255,255,255,  0,  0,  0,  0,255,255,255,255,  0,  0,  0,  0, 15, 15, 15, 15,240,240,240,240,240,240,240,240, 15, 15, 15, 15,  0,  0,  0,  0, 15, 15, 15, 15,240,240,240,240,240,240,240,240, 15, 15, 15, 15,  0,  0,  0,  0,  0, 15, 48, 64,128,  0, 32,114, 89, 79,134,131,134,132,132, 68, 70, 98, 32, 48,  0,128, 64, 48, 15,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  2,  4,  4,  8,  8,  8,  8,  8,  8,  8,  8,  4,  4,  2,  1,  1,  0,  0,  0,  0,  0,  0,
};

char os[10] = "";

/* Make non-master horizontal and master vertical */
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
    } else {
        return OLED_ROTATION_270;
    }
    return rotation;
}

// Moving Car Logo
static void render_logo(void) {
    oled_write_raw_P(logo, sizeof(logo));
}

/* Detect OS */
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

/* Create Actual OLED Image */
bool oled_task_user(void) {
    if (is_keyboard_master()) {

        /* Draw OS Logo */
        oled_set_cursor(0, 0);
        if ((strcmp(os, "MacOS")) == 0 || (strcmp(os, "IOS") == 0)) {
            oled_write_raw_P(mac_logo, sizeof(mac_logo));

        } else if (strcmp(os, "Windows") == 0) {
            oled_write_raw_P(windows_logo, sizeof(windows_logo));

        } else if (strcmp(os, "Linux") == 0) {
            oled_set_cursor(1, 0);
            oled_write_char(0x99, false);
            oled_write_char(0x9A, false);
            oled_write("\n", false);
            oled_set_cursor(1, 1);
            oled_write_char(0xB9, false);
            oled_write_char(0xBA, false);
        }

        /* Draw Layer Logo */
        switch (get_highest_layer(layer_state)) {
            case 2:
                oled_set_cursor(3, 5);
                oled_write_char(0x18, false);
                break;
            case 1:
                oled_set_cursor(3, 5);
                oled_write_char(0x19, false);
                break;
            default:
                oled_set_cursor(3, 5);
                oled_write_char(0x04, false);
                break;
        }

    } else {
        /* Draw for non-master */
        render_logo();
    }
    return false;
}

#endif // OLED_ENABLE
