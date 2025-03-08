#include QMK_KEYBOARD_H
#include "config.h"

enum custom_keycodes {
    SPEC = SAFE_RANGE,
    WIN1, // Windows
    WIN2,
    MAC1, // macOS
    MAC2,
    LIN1, // Linux
    LIN2,
    M_BACKTICK,
};

enum os_layers {
    SPECIALS_LAYER = 0,
    OS_WINDOWS_LAYER_1 = 1,
    OS_WINDOWS_LAYER_2 = 2,
    OS_MACOS_LAYER_1 = 3,
    OS_MACOS_LAYER_2 = 4,
    OS_LINUX_LAYER_1 = 5,
    OS_LINUX_LAYER_2 = 6,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case M_BACKTICK:
            if (record->event.pressed) {
                SEND_STRING("`");
            }
            return false;

    case SPEC:
        if (record->event.pressed) {
            layer_move(SPECIALS_LAYER);
        }
        return false;

    case WIN1:
        if (record->event.pressed) {
            layer_move(OS_WINDOWS_LAYER_1);
        }
        return false;

    case WIN2:
        if (record->event.pressed) {
            layer_move(OS_WINDOWS_LAYER_2);
        }
        return false;

    case MAC1:
        if (record->event.pressed) {
            layer_move(OS_MACOS_LAYER_1);
        }
        return false;

    case MAC2:
        if (record->event.pressed) {
            layer_move(OS_MACOS_LAYER_2);
        }
        return false;

    case LIN1:
        if (record->event.pressed) {
            layer_move(OS_LINUX_LAYER_1);
        }
        return false;

    case LIN2:
        if (record->event.pressed) {
            layer_move(OS_LINUX_LAYER_2);
        }
        return false;
    }
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [SPECIALS_LAYER] = LAYOUT(
        RGB_TOG    , TO(LIN1)   , TO(MAC1)   , TO(WIN1)   , KC_NO      , QK_BOOT    ,                          QK_BOOT    , KC_NO      , KC_NO      , KC_NO      , KC_NO      , RGB_TOG             ,
        KC_NO      , KC_NO      , KC_NO      , KC_NO      , KC_NO      , KC_NO      ,                          KC_NO      , KC_NO      , KC_NO      , KC_NO      , KC_NO      , KC_NO               ,
        KC_NO      , KC_NO      , KC_NO      , KC_NO      , KC_NO      , KC_NO      ,                          KC_NO      , KC_NO      , KC_NO      , KC_NO      , KC_NO      , KC_NO               ,
        KC_NO      , KC_NO      , KC_NO      , KC_NO      , KC_NO      , KC_NO      , KC_NO     , KC_NO      , KC_NO      , KC_NO      , KC_NO      , KC_NO      , KC_NO      , KC_NO               ,
                                                            KC_NO      , KC_NO      , KC_NO     , KC_NO      , KC_NO      , KC_NO
    ),
    [OS_WINDOWS_LAYER_1] = LAYOUT(
        KC_ESC     , KC_1       , KC_2       , KC_3       , KC_4       , KC_5       ,                          KC_6       , KC_7       , KC_8       , KC_9       , KC_0       , KC_MEDIA_PLAY_PAUSE ,
        KC_TAB     , KC_Q       , KC_W       , KC_E       , KC_R       , KC_T       ,                          KC_Y       , KC_U       , KC_I       , KC_O       , KC_P       , KC_BSPC             ,
        MO(WIN2)   , KC_A       , KC_S       , KC_D       , KC_F       , KC_G       ,                          KC_H       , KC_J       , KC_K       , KC_L       , KC_SCLN    , MO(WIN2)            ,
        KC_LSFT    , KC_Z       , KC_X       , KC_C       , KC_V       , KC_B       , KC_VOLD   , KC_VOLU    , KC_N       , KC_M       , KC_COMM    , KC_DOT     , KC_SLSH    , KC_RSFT             ,
                                                            KC_LGUI    , KC_LALT    , KC_SPC    , KC_ENT     , KC_RSFT    , KC_RCTL
    ),
    [OS_WINDOWS_LAYER_2] = LAYOUT(
        KC_NO      , KC_F1      , KC_F2      , KC_F3      , KC_F4      , KC_F5      ,                          KC_F6      , KC_F7      , KC_F8      , KC_F9      , KC_F10     , KC_F11              ,
        KC_TAB     , S(KC_1)    , S(KC_2)    , S(KC_6)    , S(KC_4)    , S(KC_5)    ,                          KC_PPLS    , KC_QUOT    , KC_RBRC    , KC_LBRC    , S(KC_BSLS) , KC_F12              ,
        KC_DEL     , S(KC_GRV)  , S(KC_3)    , S(KC_7)    , S(KC_9)    , S(KC_0)    ,                          KC_PMNS    , KC_RGHT    , KC_UP      , KC_DOWN    , KC_LEFT    , KC_RSFT             ,
        KC_LSFT    , S(KC_SLSH) , M_BACKTICK , S(KC_8)    , S(KC_MINS) , KC_F11     , MO(SPEC)  , MO(SPEC)   , KC_NO      , KC_NO      , KC_NO      , KC_NO      , KC_NO      , KC_NO               ,
                                                            KC_LGUI    , KC_LALT    , KC_SPC    , KC_ESC     , KC_RSFT    , KC_NO
    ),
    [OS_MACOS_LAYER_1] = LAYOUT(
        KC_ESC     , KC_1       , KC_2       , KC_3       , KC_4       , KC_5       ,                          KC_6       , KC_7       , KC_8       , KC_9       , KC_0       , KC_MEDIA_PLAY_PAUSE ,
        KC_TAB     , KC_Q       , KC_W       , KC_E       , KC_R       , KC_T       ,                          KC_Y       , KC_U       , KC_I       , KC_O       , KC_P       , KC_BSPC             ,
        MO(MAC2)   , KC_A       , KC_S       , KC_D       , KC_F       , KC_G       ,                          KC_H       , KC_J       , KC_K       , KC_L       , KC_SCLN    , MO(MAC2)            ,
        KC_LSFT    , KC_Z       , KC_X       , KC_C       , KC_V       , KC_B       , KC_VOLD   , KC_VOLU    , KC_N       , KC_M       , KC_COMM    , KC_DOT     , KC_SLSH    , KC_RSFT             ,
                                                            KC_LGUI    , KC_LALT    , KC_SPC    , KC_ENT     , KC_RSFT    , KC_RCTL
    ),
    [OS_MACOS_LAYER_2] = LAYOUT(
        RGB_TOG    , KC_F1      , KC_F2      , KC_F3      , KC_F4      , KC_F5      ,                          KC_F6      , KC_F7      , KC_F8      , KC_F9      , KC_F10     , KC_F11              ,
        KC_TAB     , S(KC_1)    , S(KC_2)    , S(KC_6)    , S(KC_4)    , S(KC_5)    ,                          KC_PPLS    , KC_QUOT    , KC_RBRC    , KC_LBRC    , S(KC_BSLS) , KC_F12              ,
        KC_DEL     , S(KC_GRV)  , S(KC_3)    , S(KC_7)    , S(KC_9)    , S(KC_0)    ,                          KC_PMNS    , KC_RGHT    , KC_UP      , KC_DOWN    , KC_LEFT    , KC_RSFT             ,
        KC_LSFT    , S(KC_SLSH) , M_BACKTICK , S(KC_8)    , S(KC_MINS) , KC_F11     , MO(SPEC)  , MO(SPEC)   , KC_NO      , KC_NO      , KC_NO      , KC_NO      , KC_NO      , KC_NO               ,
                                                            KC_LGUI    , KC_LALT    , KC_SPC    , KC_ESC     , KC_RSFT    , KC_NO
    ),
    [OS_LINUX_LAYER_1] = LAYOUT(
        KC_ESC     , KC_1       , KC_2       , KC_3       , KC_4       , KC_5       ,                          KC_6       , KC_7       , KC_8       , KC_9       , KC_0       , KC_MEDIA_PLAY_PAUSE ,
        KC_TAB     , KC_Q       , KC_W       , KC_E       , KC_R       , KC_T       ,                          KC_Y       , KC_U       , KC_I       , KC_O       , KC_P       , KC_BSPC             ,
        MO(LIN2)   , KC_A       , KC_S       , KC_D       , KC_F       , KC_G       ,                          KC_H       , KC_J       , KC_K       , KC_L       , KC_SCLN    , MO(LIN2)            ,
        KC_LSFT    , KC_Z       , KC_X       , KC_C       , KC_V       , KC_B       , KC_VOLD   , KC_VOLU    , KC_N       , KC_M       , KC_COMM    , KC_DOT     , KC_SLSH    , KC_RSFT             ,
                                                            KC_LGUI    , KC_LALT    , KC_SPC    , KC_ENT     , KC_RSFT    , KC_RCTL
    ),
    [OS_LINUX_LAYER_2] = LAYOUT(
        RGB_TOG    , KC_F1      , KC_F2      , KC_F3      , KC_F4      , KC_F5      ,                          KC_F6      , KC_F7      , KC_F8      , KC_F9      , KC_F10     , KC_F11              ,
        KC_TAB     , S(KC_1)    , S(KC_2)    , S(KC_6)    , S(KC_4)    , S(KC_5)    ,                          KC_PPLS    , KC_QUOT    , KC_RBRC    , KC_LBRC    , S(KC_BSLS) , KC_F12              ,
        KC_DEL     , S(KC_GRV)  , S(KC_3)    , S(KC_7)    , S(KC_9)    , S(KC_0)    ,                          KC_PMNS    , KC_RGHT    , KC_UP      , KC_DOWN    , KC_LEFT    , KC_RSFT             ,
        KC_LSFT    , S(KC_SLSH) , M_BACKTICK , S(KC_8)    , S(KC_MINS) , KC_F11     , MO(SPEC)  , MO(SPEC)   , KC_NO      , KC_NO      , KC_NO      , KC_NO      , KC_NO      , KC_NO               ,
                                                            KC_LGUI    , KC_LALT    , KC_SPC    , KC_ESC     , KC_RSFT    , KC_NO
    ),
};
