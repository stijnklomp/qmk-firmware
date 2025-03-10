#include QMK_KEYBOARD_H

enum custom_keycodes {
    M_BTICK = SAFE_RANGE,
    KC_ONE, // Left Control (KC_LCTL)
    KC_TWO, // Left Alt (KC_LALT)
    KC_THREE, // Tab (KC_TAB)
    KC_FOUR, // Left Shift (KC_LSFT)
    KC_FIVE, // Left (KC_LEFT)
    KC_SIX, // Right (KC_RIGHT)
    KC_SEVEN, // Left GUI (KC_LGUI)
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
    set_single_persistent_default_layer(LSPEC0);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static bool left_control_pressed = false;
    (void)left_control_pressed;
    static bool left_alt_pressed = false;
    (void)left_alt_pressed;
    static bool left_tab_pressed = false;
    (void)left_tab_pressed;
    static bool left_shift_pressed = false;
    (void)left_shift_pressed;
    static bool left_pressed = false;
    (void)left_pressed;
    static bool right_pressed = false;
    (void)right_pressed;
    static bool left_gui_pressed = false;
    (void)left_gui_pressed;

    switch (keycode) {
        case M_BTICK:
            if (record->event.pressed) {
                SEND_STRING("`");
            }
            return false;

        case KC_ONE: // Left Control
            if (record->event.pressed) {
                left_control_pressed = true;
                register_code(KC_LCTL);
            } else {
                left_control_pressed = false;
                unregister_code(KC_LCTL);
            }
            return false;

        case KC_TWO: // Left Alt
            if (record->event.pressed) {
                left_alt_pressed = true;
                register_code(KC_LALT);
            } else {
                if (get_highest_layer(layer_state) == LMAC0 || get_highest_layer(layer_state) == LMAC1) {
                    unregister_code(KC_LGUI);
                    if (left_shift_pressed) {
                        unregister_code(KC_LSFT);
                    }
                }
                left_alt_pressed = false;
                unregister_code(KC_LALT);
            }
            return false;


        case KC_THREE: // KC_TAB
            if (record->event.pressed) {
                left_tab_pressed = true;
                if (get_highest_layer(layer_state) == LMAC0 || get_highest_layer(layer_state) == LMAC1) {
                    if (left_gui_pressed) {
                        unregister_code(KC_LGUI);
                        if (left_shift_pressed) {
                            tap_code16(S(LCTL(KC_TAB)));
                        } else {
                            tap_code16(LCTL(KC_TAB));
                        }
                        register_code(KC_LGUI);
                    } else if (left_alt_pressed) {
                        unregister_code(KC_LALT);
                        if (left_shift_pressed) {
                            register_code(KC_LSFT);
                            register_code(KC_LGUI);
                            tap_code(KC_TAB);
                        } else {
                            register_code(KC_LGUI);
                            tap_code(KC_TAB);
                        }
                        register_code(KC_LALT);
                    } else {
                        tap_code(KC_TAB);
                    }
                } else {
                    tap_code(KC_TAB);
                }
            } else {
                left_tab_pressed = false;
            }
            return false;

        case KC_FOUR: // Left Shift
            if (record->event.pressed) {
                left_shift_pressed = true;
                register_code(KC_LSFT);
            } else {
                left_shift_pressed = false;
                unregister_code(KC_LSFT);
            }
            return false;

        case KC_FIVE: // Left
            if (record->event.pressed) {
                left_pressed = true;
                if (get_highest_layer(layer_state) == LWIN0 || get_highest_layer(layer_state) == LWIN1) {
                    if (left_alt_pressed) { // Home
                        unregister_code(KC_LALT);
                        tap_code(KC_HOME);
                        register_code(KC_LALT);
                    } else {
                        register_code(KC_LEFT);
                    }
                } else if (get_highest_layer(layer_state) == LMAC0 || get_highest_layer(layer_state) == LMAC1) {
                    if (left_gui_pressed) {
                        unregister_code(KC_LGUI);
                        if (left_shift_pressed) {
                            tap_code16(S(LALT(KC_LEFT)));
                        } else {
                            tap_code16(LALT(KC_LEFT));
                        }
                        register_code(KC_LGUI);
                    } else if (left_alt_pressed) {
                        unregister_code(KC_LALT);
                        if (left_shift_pressed) {
                            tap_code16(S(LGUI(KC_LEFT)));
                        } else {
                            tap_code16(LGUI(KC_LEFT));
                        }
                        register_code(KC_LALT);
                    } else {
                        register_code(KC_LEFT);
                    }
                } else {
                    register_code(KC_LEFT);
                }
            } else {
                left_pressed = false;
                unregister_code(KC_LEFT);
            }
            return false;

        case KC_SIX: // Right
            if (record->event.pressed) {
                right_pressed = true;
                if (get_highest_layer(layer_state) == LWIN0 || get_highest_layer(layer_state) == LWIN1) {
                    if (left_alt_pressed) { // End
                        unregister_code(KC_LALT);
                        tap_code(KC_END);
                        register_code(KC_LALT);
                    } else {
                        register_code(KC_RIGHT);
                    }
                } else if (get_highest_layer(layer_state) == LMAC0 || get_highest_layer(layer_state) == LMAC1) {
                    if (left_gui_pressed) {
                        unregister_code(KC_LGUI);
                        if (left_shift_pressed) {
                            tap_code16(S(LALT(KC_RIGHT)));
                        } else {
                            tap_code16(LALT(KC_RIGHT));
                        }
                        register_code(KC_LGUI);
                    } else if (left_alt_pressed) {
                        unregister_code(KC_LALT);
                        if (left_shift_pressed) {
                            tap_code16(S(LGUI(KC_RIGHT)));
                        } else {
                            tap_code16(LGUI(KC_RIGHT));
                        }
                        register_code(KC_LALT);
                    } else {
                        register_code(KC_RIGHT);
                    }
                } else {
                    unregister_code(KC_RIGHT);
                }
            } else {
                right_pressed = false;
            }
            return false;

        case KC_SEVEN: // Left GUI
            if (record->event.pressed) {
                left_gui_pressed = true;
                register_code(KC_LGUI);
            } else {
                left_gui_pressed = false;
                unregister_code(KC_LGUI);
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
        KC_THREE   , KC_Q       , KC_W       , KC_E      , KC_R      , KC_T      ,                         KC_Y      , KC_U      , KC_I      , KC_O      , KC_P      , KC_BSPC   ,
        MO(LWIN1)  , KC_A       , KC_S       , KC_D      , KC_F      , KC_G      ,                         KC_H      , KC_J      , KC_K      , KC_L      , KC_SCLN   , MO(LWIN1) ,
        KC_FOUR    , KC_Z       , KC_X       , KC_C      , KC_V      , KC_B      , KC_VOLD   , KC_VOLU   , KC_N      , KC_M      , KC_COMM   , KC_DOT    , KC_SLSH   , KC_FOUR   ,
                                                           KC_ONE    , KC_TWO    , KC_SPC    , KC_ENT    , KC_FOUR   , KC_ONE
    ),
    [LWIN1] = LAYOUT(
        KC_NO      , KC_F1      , KC_F2      , KC_F3     , KC_F4     , KC_F5     ,                         KC_F6     , KC_F7     , KC_F8     , KC_F9     , KC_F10    , KC_F11    ,
        KC_THREE   , KC_EXLM    , KC_AT      , KC_CIRC   , KC_DLR    , KC_PERC   ,                         KC_PIPE   , KC_LBRC   , KC_RBRC   , KC_QUOT   , KC_PPLS   , KC_F12    ,
        KC_DEL     , KC_TILD    , KC_HASH    , KC_AMPR   , KC_LPRN   , KC_RPRN   ,                         KC_FIVE   , KC_DOWN   , KC_UP     , KC_SIX    , KC_PMNS   , KC_NO     ,
        KC_FOUR    , KC_QUES    , M_BTICK    , KC_ASTR   , KC_UNDS   , KC_F11    , TO(LSPEC0), TO(LSPEC0), KC_F12    , KC_PEQL   , KC_LT     , KC_GT     , KC_NO     , KC_FOUR   ,
                                                           KC_ONE    , KC_TWO    , KC_SPC    , KC_ESC    , KC_FOUR   , KC_ONE
    ),
    [LMAC0] = LAYOUT(
        KC_ESC     , KC_1       , KC_2       , KC_3      , KC_4      , KC_5      ,                         KC_6      , KC_7      , KC_8      , KC_9      , KC_0      , KC_MEDIA_PLAY_PAUSE ,
        KC_THREE   , KC_Q       , KC_W       , KC_E      , KC_R      , KC_T      ,                         KC_Y      , KC_U      , KC_I      , KC_O      , KC_P      , KC_BSPC   ,
        MO(LMAC1)  , KC_A       , KC_S       , KC_D      , KC_F      , KC_G      ,                         KC_H      , KC_J      , KC_K      , KC_L      , KC_SCLN   , MO(LMAC1) ,
        KC_LSFT    , KC_Z       , KC_X       , KC_C      , KC_V      , KC_B      , KC_VOLD   , KC_VOLU   , KC_N      , KC_M      , KC_COMM   , KC_DOT    , KC_SLSH   , KC_LSFT   ,
                                                           KC_SEVEN  , KC_TWO    , KC_SPC    , KC_ENT    , KC_LSFT   , KC_SEVEN
    ),
    [LMAC1] = LAYOUT(
        KC_NO      , KC_F1      , KC_F2      , KC_F3     , KC_F4     , KC_F5     ,                         KC_F6     , KC_F7     , KC_F8     , KC_F9     , KC_F10    , KC_F11    ,
        KC_THREE   , KC_EXLM    , KC_AT      , KC_CIRC   , KC_DLR    , KC_PERC   ,                         KC_PIPE   , KC_LBRC   , KC_RBRC   , KC_QUOT   , KC_PPLS   , KC_F12    ,
        KC_DEL     , KC_TILD    , KC_HASH    , KC_AMPR   , KC_LPRN   , KC_RPRN   ,                         KC_FIVE   , KC_DOWN   , KC_UP     , KC_SIX    , KC_PMNS   , KC_NO     ,
        KC_LSFT    , KC_QUES    , M_BTICK    , KC_ASTR   , KC_UNDS   , KC_F11    , TO(LSPEC0), TO(LSPEC0), KC_F12    , KC_PEQL   , KC_LT     , KC_GT     , KC_NO     , KC_LSFT   ,
                                                           KC_SEVEN  , KC_TWO    , KC_SPC    , KC_ESC    , KC_LSFT   , KC_SEVEN
    ),
    [LLIN0] = LAYOUT(
        KC_ESC     , KC_1       , KC_2       , KC_3      , KC_4      , KC_5      ,                         KC_6      , KC_7      , KC_8      , KC_9      , KC_0      , KC_MEDIA_PLAY_PAUSE ,
        KC_TAB     , KC_Q       , KC_W       , KC_E      , KC_R      , KC_T      ,                         KC_Y      , KC_U      , KC_I      , KC_O      , KC_P      , KC_BSPC   ,
        MO(LLIN1)  , KC_A       , KC_S       , KC_D      , KC_F      , KC_G      ,                         KC_H      , KC_J      , KC_K      , KC_L      , KC_SCLN   , MO(LLIN1) ,
        KC_LSFT    , KC_Z       , KC_X       , KC_C      , KC_V      , KC_B      , KC_VOLD   , KC_VOLU   , KC_N      , KC_M      , KC_COMM   , KC_DOT    , KC_SLSH   , KC_LSFT   ,
                                                           KC_LALT   , KC_LGUI   , KC_SPC    , KC_ENT    , KC_LSFT   , KC_LALT
    ),
    [LLIN1] = LAYOUT(
        KC_NO      , KC_F1      , KC_F2      , KC_F3     , KC_F4     , KC_F5     ,                         KC_F6     , KC_F7     , KC_F8     , KC_F9     , KC_F10    , KC_F11    ,
        KC_TAB     , KC_EXLM    , KC_AT      , KC_CIRC   , KC_DLR    , KC_PERC   ,                         KC_PIPE   , KC_LBRC   , KC_RBRC   , KC_QUOT   , KC_PPLS   , KC_F12    ,
        KC_DEL     , KC_TILD    , KC_HASH    , KC_AMPR   , KC_LPRN   , KC_RPRN   ,                         KC_LEFT   , KC_DOWN   , KC_UP     , KC_RIGHT  , KC_PMNS   , KC_NO     ,
        KC_LSFT    , KC_QUES    , M_BTICK    , KC_ASTR   , KC_UNDS   , KC_F11    , TO(LSPEC0), TO(LSPEC0), KC_F12    , KC_PEQL   , KC_LT     , KC_GT     , KC_NO     , KC_LSFT   ,
                                                           KC_LALT   , KC_LGUI   , KC_SPC    , KC_ESC    , KC_LSFT   , KC_LALT
    ),
};
