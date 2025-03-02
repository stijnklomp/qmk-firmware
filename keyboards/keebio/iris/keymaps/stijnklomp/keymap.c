#include QMK_KEYBOARD_H
#if __has_include("keymap.h")
#    include "keymap.h"
#endif

enum custom_keycodes {
    M_BACKTICK = SAFE_RANGE, // Ensure unique keycode
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case M_BACKTICK:
            if (record->event.pressed) {
                SEND_STRING("`");  // Sends a backtick when pressed
            }
            return false; // Skip normal keypress processing
    }
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC     , KC_1       , KC_2       , KC_3       , KC_4       , KC_5       ,                          KC_6       , KC_7       , KC_8       , KC_9       , KC_0       , KC_MEDIA_PLAY_PAUSE ,
        KC_TAB     , KC_Q       , KC_W       , KC_E       , KC_R       , KC_T       ,                          KC_Y       , KC_U       , KC_I       , KC_O       , KC_P       , KC_BSPC             ,
        MO(1)      , KC_A       , KC_S       , KC_D       , KC_F       , KC_G       ,                          KC_H       , KC_J       , KC_K       , KC_L       , KC_SCLN    , MO(1)               ,
        KC_LSFT    , KC_Z       , KC_X       , KC_C       , KC_V       , KC_B       , KC_VOLD   , KC_VOLU    , KC_N       , KC_M       , KC_COMM    , KC_DOT     , KC_SLSH    , KC_RSFT             ,
                                                            KC_LGUI    , KC_LALT    , KC_SPC    , KC_ENT     , KC_RSFT    , KC_RCTL
    ),
    [1] = LAYOUT(
        RGB_TOG    , KC_F1      , KC_F2      , KC_F3      , KC_F4      , KC_F5      ,                          KC_F6      , KC_F7      , KC_F8      , KC_F9      , KC_F10     , KC_F11              ,
        KC_TAB     , S(KC_1)    , S(KC_2)    , S(KC_6)    , S(KC_4)    , S(KC_5)    ,                          KC_PPLS    , KC_QUOT    , KC_RBRC    , KC_LBRC    , S(KC_BSLS)  , KC_F12             ,
        KC_DEL     , S(KC_GRV)  , S(KC_3)    , S(KC_7)    , S(KC_9)    , S(KC_0)    ,                          KC_PMNS    , KC_RGHT    , KC_UP      , KC_DOWN    , KC_LEFT    , KC_RSFT             ,
        KC_LSFT    , S(KC_SLSH) , M_BACKTICK , S(KC_8)    , S(KC_MINS) , KC_F11     , KC_NO     , KC_NO      , KC_NO      , KC_NO      , KC_NO      , KC_NO      , KC_NO      , KC_NO               ,
                                                            KC_LGUI    , KC_LALT    , KC_SPC    , KC_ESC     , KC_RSFT    , KC_NO
    ),
    [2] = LAYOUT(
        KC_ESC     , KC_NO      , KC_NO      , KC_NO      , KC_NO      , KC_NO      ,                          KC_NO      , KC_NO      , KC_NO      , KC_NO      , KC_NO      , KC_NO               ,
        KC_TAB     , S(KC_1)    , S(KC_2)    , S(KC_6)    , S(KC_4)    , S(KC_5)    ,                          KC_BSLS    , KC_QUOT    , KC_RBRC    , KC_LBRC    , KC_EQL     , RGB_TOG             ,
        KC_DEL     , KC_GRV     , S(KC_3)    , S(KC_7)    , S(KC_9)    , S(KC_0)    ,                          KC_MINS    , KC_RGHT    , KC_UP      , KC_DOWN    , KC_LEFT    , KC_RSFT             ,
        KC_LSFT    , S(KC_SLSH) , KC_NO      , S(KC_8)    , S(KC_MINS) , KC_NO      , KC_NO     , KC_NO      , KC_NO      , KC_NO      , KC_NO      , KC_NO      , KC_NO      , KC_NO               ,
                                                            KC_LGUI   , KC_LALT     , KC_ESC    , KC_NO      , KC_RSFT    , KC_NO
    )
};

#ifdef OTHER_KEYMAP_C
#    include OTHER_KEYMAP_C
#endif // OTHER_KEYMAP_C
