#include QMK_KEYBOARD_H

enum custom_keycodes {
    M_BTICK = SAFE_RANGE,
};

enum os_layers {
    LSPEC0 = 0,
    LWIN0 = 1,
    LWIN1 = 2,
    LMAC0 = 3,
    LMAC1 = 4,
    LLIN0 = 5,
    LLIN1 = 6,
};

void matrix_init_user(void) {
    set_single_persistent_default_layer(0);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case M_BTICK:
            if (record->event.pressed) {
                SEND_STRING("`");
            }
            return false;
    }
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LSPEC0] = LAYOUT(
        RGB_TOG    , TO(LLIN0)  , TO(LMAC0)  , TO(LWIN0) , KC_NO     , QK_BOOT   ,                         QK_BOOT   , KC_NO     , TO(LWIN0) , TO(LMAC0) , TO(LLIN0) , RGB_TOG   ,
        KC_NO      , KC_NO      , KC_NO      , KC_NO     , KC_NO     , KC_NO     ,                         KC_NO     , KC_NO     , KC_NO     , KC_NO     , KC_NO     , KC_NO     ,
        KC_NO      , KC_NO      , KC_NO      , KC_NO     , KC_NO     , KC_NO     ,                         KC_NO     , KC_NO     , KC_NO     , KC_NO     , KC_NO     , KC_NO     ,
        KC_NO      , KC_NO      , KC_NO      , KC_NO     , KC_NO     , KC_NO     , KC_NO     , KC_NO     , KC_NO     , KC_NO     , KC_NO     , KC_NO     , KC_NO     , KC_NO     ,
                                                           KC_NO     , KC_NO     , KC_NO     , KC_NO     , KC_NO     , KC_NO
    ),
    [LWIN0] = LAYOUT(
        KC_ESC     , KC_1       , KC_2       , KC_3      , KC_4      , KC_5      ,                         KC_6      , KC_7      , KC_8      , KC_9      , KC_0      , KC_MEDIA_PLAY_PAUSE ,
        KC_TAB     , KC_Q       , KC_W       , KC_E      , KC_R      , KC_T      ,                         KC_Y      , KC_U      , KC_I      , KC_O      , KC_P      , KC_BSPC   ,
        MO(LWIN1)  , KC_A       , KC_S       , KC_D      , KC_F      , KC_G      ,                         KC_H      , KC_J      , KC_K      , KC_L      , KC_SCLN   , MO(LWIN1) ,
        KC_LSFT    , KC_Z       , KC_X       , KC_C      , KC_V      , KC_B      , KC_VOLD   , KC_VOLU   , KC_N      , KC_M      , KC_COMM   , KC_DOT    , KC_SLSH   , KC_RSFT   ,
                                                           KC_LCTL   , KC_LALT   , KC_SPC    , KC_ENT    , KC_RSFT   , KC_RCTL
    ),
    [LWIN1] = LAYOUT(
        KC_NO      , KC_F1      , KC_F2      , KC_F3     , KC_F4     , KC_F5     ,                         KC_F6     , KC_F7     , KC_F8     , KC_F9     , KC_F10    , KC_F11    ,
        KC_TAB     , KC_EXLM    , KC_AT      , KC_CIRC   , KC_DLR    , KC_PERC   ,                         KC_PIPE   , KC_LBRC   , KC_RBRC   , KC_QUOT   , KC_PPLS   , KC_F12    ,
        KC_DEL     , KC_TILD    , KC_HASH    , KC_AMPR   , KC_LPRN   , KC_RPRN   ,                         KC_LEFT   , KC_DOWN   , KC_UP     , KC_RIGHT  , KC_PMNS   , KC_RSFT   ,
        KC_LSFT    , KC_QUES    , M_BTICK    , KC_ASTR   , KC_UNDS   , KC_F11    , TO(LSPEC0), TO(LSPEC0), KC_F12    , KC_PEQL   , KC_LT     , KC_GT     , KC_NO     , KC_RSFT   ,
                                                           KC_LCTL   , KC_LALT   , KC_SPC    , KC_ESC    , KC_RSFT   , KC_NO
    ),
    [LMAC0] = LAYOUT(
        KC_ESC     , KC_1       , KC_2       , KC_3      , KC_4      , KC_5      ,                         KC_6      , KC_7      , KC_8      , KC_9      , KC_0      , KC_MEDIA_PLAY_PAUSE ,
        KC_TAB     , KC_Q       , KC_W       , KC_E      , KC_R      , KC_T      ,                         KC_Y      , KC_U      , KC_I      , KC_O      , KC_P      , KC_BSPC   ,
        MO(LMAC1)  , KC_A       , KC_S       , KC_D      , KC_F      , KC_G      ,                         KC_H      , KC_J      , KC_K      , KC_L      , KC_SCLN   , MO(LMAC1) ,
        KC_LSFT    , KC_Z       , KC_X       , KC_C      , KC_V      , KC_B      , KC_VOLD   , KC_VOLU   , KC_N      , KC_M      , KC_COMM   , KC_DOT    , KC_SLSH   , KC_RSFT   ,
                                                           KC_LGUI   , KC_LALT   , KC_SPC    , KC_ENT    , KC_RSFT   , KC_RCTL
    ),
    [LMAC1] = LAYOUT(
        KC_NO      , KC_F1      , KC_F2      , KC_F3     , KC_F4     , KC_F5     ,                         KC_F6     , KC_F7     , KC_F8     , KC_F9     , KC_F10    , KC_F11    ,
        KC_TAB     , KC_EXLM    , KC_AT      , KC_CIRC   , KC_DLR    , KC_PERC   ,                         KC_PIPE   , KC_LBRC   , KC_RBRC   , KC_QUOT   , KC_PPLS   , KC_F12    ,
        KC_DEL     , KC_TILD    , KC_HASH    , KC_AMPR   , KC_LPRN   , KC_RPRN   ,                         KC_LEFT   , KC_DOWN   , KC_UP     , KC_RIGHT  , KC_PMNS   , KC_RSFT   ,
        KC_LSFT    , KC_QUES    , M_BTICK    , KC_ASTR   , KC_UNDS   , KC_F11    , TO(LSPEC0), TO(LSPEC0), KC_F12    , KC_PEQL   , KC_LT     , KC_GT     , KC_NO     , KC_RSFT   ,
                                                           KC_LGUI   , KC_LALT   , KC_SPC    , KC_ESC    , KC_RSFT   , KC_NO
    ),
    [LLIN0] = LAYOUT(
        KC_ESC     , KC_1       , KC_2       , KC_3      , KC_4      , KC_5      ,                         KC_6      , KC_7      , KC_8      , KC_9      , KC_0      , KC_MEDIA_PLAY_PAUSE ,
        KC_TAB     , KC_Q       , KC_W       , KC_E      , KC_R      , KC_T      ,                         KC_Y      , KC_U      , KC_I      , KC_O      , KC_P      , KC_BSPC   ,
        MO(LLIN1)  , KC_A       , KC_S       , KC_D      , KC_F      , KC_G      ,                         KC_H      , KC_J      , KC_K      , KC_L      , KC_SCLN   , MO(LLIN1) ,
        KC_LSFT    , KC_Z       , KC_X       , KC_C      , KC_V      , KC_B      , KC_VOLD   , KC_VOLU   , KC_N      , KC_M      , KC_COMM   , KC_DOT    , KC_SLSH   , KC_RSFT   ,
                                                           KC_LGUI   , KC_LALT   , KC_SPC    , KC_ENT    , KC_RSFT   , KC_RCTL
    ),
    [LLIN1] = LAYOUT(
        KC_NO      , KC_F1      , KC_F2      , KC_F3     , KC_F4     , KC_F5     ,                         KC_F6     , KC_F7     , KC_F8     , KC_F9     , KC_F10    , KC_F11    ,
        KC_TAB     , KC_EXLM    , KC_AT      , KC_CIRC   , KC_DLR    , KC_PERC   ,                         KC_PIPE   , KC_LBRC   , KC_RBRC   , KC_QUOT   , KC_PPLS   , KC_F12    ,
        KC_DEL     , KC_TILD    , KC_HASH    , KC_AMPR   , KC_LPRN   , KC_RPRN   ,                         KC_LEFT   , KC_DOWN   , KC_UP     , KC_RIGHT  , KC_PMNS   , KC_RSFT   ,
        KC_LSFT    , KC_QUES    , M_BTICK    , KC_ASTR   , KC_UNDS   , KC_F11    , TO(LSPEC0), TO(LSPEC0), KC_F12    , KC_PEQL   , KC_LT     , KC_GT     , KC_NO     , KC_RSFT   ,
                                                           KC_LGUI   , KC_LALT   , KC_SPC    , KC_ESC    , KC_RSFT   , KC_NO
    ),
};
