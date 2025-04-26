#include QMK_KEYBOARD_H
#include <stdbool.h>

// Custom keys usually start with "CK" (Custom Key)
enum custom_keycodes {
    SGL_BTICK = SAFE_RANGE, // "`"
    SGL_BSLS, // "\"
    CK_LCTL, // Left Control (KC_LCTL)
    CK_RCTL, // Right Control (KC_RCTL)
    CK_LALT, // Left Alt (KC_LALT)
    CK_TAB, // Tab (KC_TAB)
    CK_LSFT, // Left Shift (KC_LSFT)
    CK_LEFT, // Left (KC_LEFT)
    CK_RIGHT, // Right (KC_RIGHT)
    CK_LGUI, // Left GUI (KC_LGUI)
    CK_Q, // q (KC_Q)
    CK_C, // c (KC_C)
    CK_BSPC, // Backspace (KC_BSPC)
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
    // Default layer
    set_single_persistent_default_layer(LSPEC0);
}

bool is_windows_layer(uint32_t layer_state) {
    uint8_t highest_layer = get_highest_layer(layer_state);
    return (highest_layer == LWIN0 || highest_layer == LWIN1);
}

bool is_macos_layer(uint32_t layer_state) {
    uint8_t highest_layer = get_highest_layer(layer_state);
    return (highest_layer == LMAC0 || highest_layer == LMAC1);
}

bool is_linux_layer(uint32_t layer_state) {
    uint8_t highest_layer = get_highest_layer(layer_state);
    return (highest_layer == LLIN0 || highest_layer == LLIN1);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // The reason for having lots of complex custom key binds is because it:
    // - allows me to map macOS controls closer to Windows controls
    // - makes the different operating system layers closer to each other for every app within the OS' GUI
    static bool move_to_next_or_prev_apps = false;
    (void)move_to_next_or_prev_apps;
    static bool left_control_pressed = false;
    (void)left_control_pressed;
    static bool right_control_pressed = false;
    (void)right_control_pressed;
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
    static bool q_pressed = false;
    (void)q_pressed;
    static bool c_pressed = false;
    (void)c_pressed;
    static bool backspace_pressed = false;
    (void)backspace_pressed;

    switch (keycode) {
        // TODO
        // 1: Map 'Right Control (KC_RCTL) + Tab (CK_TAB)' to "move to different sub-window within Kitty"
        // 2.1: Move '(' + ')' to 'y' (2nd layer)
        // 2.2: Put '] + shift' on 'u' (2nd layer), '{' on 'i' (2nd layer)

        case SGL_BTICK: // "`"
            if (record->event.pressed) {
                SEND_STRING("`");
            }
            return false;

        case SGL_BSLS: // KC_BSLS
            if (record->event.pressed) {
                // The many if statements are to prevent special keys ("«" and "|") from being typed accidentally when certain keys are held
                // or to prevent no key at all being from being typed if control is held (which can happen, for example, when you move between words and then type whilst releasing the control key at the same time)
                if (left_control_pressed) {
                    unregister_code(KC_LCTL);
                }
                if (right_control_pressed) {
                    unregister_code(KC_RCTL);
                }
                if (left_alt_pressed) {
                    unregister_code(KC_LALT);
                }
                if (left_gui_pressed) {
                    unregister_code(KC_LGUI);
                }
                tap_code(KC_BSLS);
                if (left_control_pressed) {
                    register_code(KC_LCTL);
                }
                if (right_control_pressed) {
                    register_code(KC_RCTL);
                }
                if (left_alt_pressed) {
                    register_code(KC_LALT);
                }
                if (left_gui_pressed) {
                    register_code(KC_LGUI);
                }
            }
            return false;

        case CK_LCTL: // Left Control
            if (record->event.pressed) {
                left_control_pressed = true;
                register_code(KC_LCTL);
            } else {
                left_control_pressed = false;
                unregister_code(KC_LCTL);
            }
            return false;

        case CK_RCTL: // Right Control
            if (record->event.pressed) {
                right_control_pressed = true;
                register_code(KC_RCTL);
            } else {
                right_control_pressed = false;
                unregister_code(KC_RCTL);
            }
            return false;

        case CK_LALT: // Left Alt
            if (record->event.pressed) {
                left_alt_pressed = true;
                register_code(KC_LALT);
            } else {
                left_alt_pressed = false;
                if (is_macos_layer(layer_state) || is_linux_layer(layer_state)) {
                    if (move_to_next_or_prev_apps) {
                        // This is needed to make "command" + "tab" work
                        // without it, the next/previous app won't be selected when you release "command"
                        move_to_next_or_prev_apps = false;
                        unregister_code(KC_LGUI);
                        if (left_shift_pressed) {
                            unregister_code(KC_LSFT);
                        }
                    }
                }

                unregister_code(KC_LALT);
            }
            return false;

        case CK_TAB: // KC_TAB
            if (record->event.pressed) {
                left_tab_pressed = true;
                if (right_control_pressed) {
                    if (left_shift_pressed) {
                        // Use "left control" + "[" to move to the previous window
                        tap_code16(LCTL(KC_LBRC));
                        return false;
                    }

                    // Use "left control" + "]" to move to the next window
                    tap_code16(LCTL(KC_RBRC));
                    return false;
                }

                if (is_macos_layer(layer_state) || is_linux_layer(layer_state)) {
                    if (left_gui_pressed) {
                        // Use "command" + "shift" + "{" or "}" instead of the default "control" + "tab" behavior as this is not always consistent in all apps
                        if (left_shift_pressed) {
                            tap_code16(S(LGUI(KC_LCBR)));
                        } else {
                            tap_code16(S(LGUI(KC_RCBR)));
                        }
                        return false;
                    }

                    if (left_alt_pressed) {
                        // Use "command" + ("shift") + "tab" to move to next/previous app
                        move_to_next_or_prev_apps = true;
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
                        return false;
                    }
                }

                tap_code(KC_TAB);
            } else {
                left_tab_pressed = false;
            }
            return false;

        case CK_LSFT: // Left Shift
            if (record->event.pressed) {
                left_shift_pressed = true;
                register_code(KC_LSFT);
            } else {
                left_shift_pressed = false;
                unregister_code(KC_LSFT);
            }
            return false;

        case CK_LEFT: // Left
            if (record->event.pressed) {
                left_pressed = true;
                if (is_windows_layer(layer_state) || is_linux_layer(layer_state)) {
                    if (left_alt_pressed) {
                        // Beginning of line (home)
                        unregister_code(KC_LALT);
                        tap_code(KC_LALT);
                        tap_code(KC_HOME);
                        register_code(KC_LALT);
                        return false;
                    }
                }

                if (is_macos_layer(layer_state)) {
                    if (left_gui_pressed) {
                        // Beginning of word or previous word
                        unregister_code(KC_LGUI);
                        if (left_shift_pressed) {
                            tap_code16(S(LALT(KC_LEFT)));
                        } else {
                            tap_code16(LALT(KC_LEFT));
                        }
                        register_code(KC_LGUI);
                        return false;
                    }

                    if (left_alt_pressed) {
                        // Beginning of line
                        unregister_code(KC_LALT);
                        if (left_shift_pressed) {
                            tap_code16(S(LGUI(KC_LEFT)));
                            left_shift_pressed = true;
                            register_code(KC_LSFT);
                        } else {
                            tap_code16(LGUI(KC_LEFT));
                        }
                        register_code(KC_LALT);
                        return false;
                    }
                }

                register_code(KC_LEFT);
            } else {
                left_pressed = false;
                unregister_code(KC_LEFT);
            }
            return false;

        case CK_RIGHT: // Right
            if (record->event.pressed) {
                right_pressed = true;
                if (is_windows_layer(layer_state) || is_linux_layer(layer_state)) {
                    if (left_alt_pressed) {
                        // End of line
                        unregister_code(KC_LALT);
                        tap_code(KC_LALT);
                        tap_code(KC_END);
                        register_code(KC_LALT);
                        return false;
                    }
                }

                if (is_macos_layer(layer_state)) {
                    if (left_gui_pressed) {
                        // End of word or end of next word
                        unregister_code(KC_LGUI);
                        if (left_shift_pressed) {
                            tap_code16(S(LALT(KC_RIGHT)));
                        } else {
                            tap_code16(LALT(KC_RIGHT));
                        }
                        register_code(KC_LGUI);
                        return false;
                    }

                    if (left_alt_pressed) {
                        // End of line
                        unregister_code(KC_LALT);
                        if (left_shift_pressed) {
                            tap_code16(S(LGUI(KC_RIGHT)));
                            left_shift_pressed = true;
                            register_code(KC_LSFT);
                        } else {
                            tap_code16(LGUI(KC_RIGHT));
                        }
                        register_code(KC_LALT);
                        return false;
                    }
                }

                register_code(KC_RIGHT);
            } else {
                right_pressed = false;
                unregister_code(KC_RIGHT);
            }
            return false;

        case CK_LGUI: // Left GUI
            if (record->event.pressed) {
                left_gui_pressed = true;
                register_code(KC_LGUI);
            } else {
                left_gui_pressed = false;
                unregister_code(KC_LGUI);
            }
            return false;

        case CK_Q: // q
            if (record->event.pressed) {
                q_pressed = true;
                if (is_macos_layer(layer_state)) {
                    if (left_gui_pressed) {
                        // Prevent closing of entire app and all its windows
                        return false;
                    }
                }

                tap_code(KC_Q);
            } else {
                q_pressed = false;
            }
            return false;

        case CK_C: // c
            if (record->event.pressed) {
                c_pressed = true;
                if (is_linux_layer(layer_state)) {
                    if (right_control_pressed) {
                        // Use "left control" + "shift" + "c" to return SIGINT in Kitty terminal
                        tap_code16(S(LCTL(KC_C)));
                        return false;
                    }
                }

                tap_code(KC_C);
            } else {
                c_pressed = false;
            }
            return false;

        case CK_BSPC: // Backspace
            if (record->event.pressed) {
                backspace_pressed = true;
                if (is_macos_layer(layer_state)) {
                    if (left_gui_pressed) {
                        // Remove single word
                        unregister_code(KC_LGUI);
                        register_code(KC_LALT);
                        tap_code(KC_BSPC);
                        register_code(KC_LGUI);
                        unregister_code(KC_LALT);
                        return false;
                    }

                    if (left_alt_pressed) {
                        // Remove everything left of cursor
                        unregister_code(KC_LALT);
                        register_code(KC_LGUI);
                        tap_code(KC_BSPC);
                        register_code(KC_LALT);
                        unregister_code(KC_LGUI);
                        return false;
                    }
                }

                tap_code(KC_BSPC);
            } else {
                backspace_pressed = false;
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
        CK_TAB     , KC_Q       , KC_W       , KC_E      , KC_R      , KC_T      ,                         KC_Y      , KC_U      , KC_I      , KC_O      , KC_P      , KC_BSPC   ,
        MO(LWIN1)  , KC_A       , KC_S       , KC_D      , KC_F      , KC_G      ,                         KC_H      , KC_J      , KC_K      , KC_L      , KC_SCLN   , MO(LWIN1) ,
        CK_LSFT    , KC_Z       , KC_X       , KC_C      , KC_V      , KC_B      , KC_VOLD   , KC_VOLU   , KC_N      , KC_M      , KC_COMM   , KC_DOT    , KC_SLSH   , CK_LSFT   ,
                                                           CK_LCTL   , CK_LALT   , KC_SPC    , KC_ENT    , CK_LSFT   , CK_RCTL
    ),
    [LWIN1] = LAYOUT(
        KC_MPRV    , KC_F1      , KC_F2      , KC_F3     , KC_F4     , KC_F5     ,                         KC_F6     , KC_F7     , KC_F8     , KC_F9     , KC_F10    , KC_MNXT   ,
        CK_TAB     , KC_EXLM    , KC_AT      , KC_CIRC   , KC_DLR    , KC_PERC   ,                         KC_PIPE   , KC_LBRC   , KC_RBRC   , KC_QUOT   , KC_PPLS   , KC_F12    ,
        KC_DEL     , KC_TILD    , KC_HASH    , KC_AMPR   , KC_LPRN   , KC_RPRN   ,                         CK_LEFT   , KC_DOWN   , KC_UP     , CK_RIGHT  , KC_PMNS   , KC_F11    ,
        CK_LSFT    , KC_QUES    , SGL_BTICK  , KC_ASTR   , KC_UNDS   , KC_F11    , TO(LSPEC0), TO(LSPEC0), KC_F12    , KC_PEQL   , KC_LT     , KC_GT     , SGL_BSLS  , CK_LSFT   ,
                                                           CK_LCTL   , CK_LALT   , KC_SPC    , KC_ESC    , CK_LSFT   , CK_RCTL
    ),
    [LMAC0] = LAYOUT(
        KC_ESC     , KC_1       , KC_2       , KC_3      , KC_4      , KC_5      ,                         KC_6      , KC_7      , KC_8      , KC_9      , KC_0      , KC_MEDIA_PLAY_PAUSE ,
        CK_TAB     , CK_Q       , KC_W       , KC_E      , KC_R      , KC_T      ,                         KC_Y      , KC_U      , KC_I      , KC_O      , KC_P      , CK_BSPC   ,
        MO(LMAC1)  , KC_A       , KC_S       , KC_D      , KC_F      , KC_G      ,                         KC_H      , KC_J      , KC_K      , KC_L      , KC_SCLN   , MO(LMAC1) ,
        CK_LSFT    , KC_Z       , KC_X       , KC_C      , KC_V      , KC_B      , KC_VOLD   , KC_VOLU   , KC_N      , KC_M      , KC_COMM   , KC_DOT    , KC_SLSH   , CK_LSFT   ,
                                                           CK_LGUI   , CK_LALT   , KC_SPC    , KC_ENT    , CK_LSFT   , CK_RCTL
    ),
    [LMAC1] = LAYOUT(
        KC_MPRV    , KC_F1      , KC_F2      , KC_F3     , KC_F4     , KC_F5     ,                         KC_F6     , KC_F7     , KC_F8     , KC_F9     , KC_F10    , KC_MNXT   ,
        CK_TAB     , KC_EXLM    , KC_AT      , KC_CIRC   , KC_DLR    , KC_PERC   ,                         KC_PIPE   , KC_LBRC   , KC_RBRC   , KC_QUOT   , KC_PPLS   , CK_BSPC   ,
        KC_DEL     , KC_TILD    , KC_HASH    , KC_AMPR   , KC_LPRN   , KC_RPRN   ,                         CK_LEFT   , KC_DOWN   , KC_UP     , CK_RIGHT  , KC_PMNS   , KC_NO     ,
        CK_LSFT    , KC_QUES    , SGL_BTICK  , KC_ASTR   , KC_UNDS   , KC_F11    , TO(LSPEC0), TO(LSPEC0), KC_F12    , KC_PEQL   , KC_LT     , KC_GT     , SGL_BSLS  , KC_F11    ,
                                                           CK_LGUI   , CK_LALT   , KC_SPC    , KC_ESC    , CK_LSFT   , CK_RCTL
    ),
    [LLIN0] = LAYOUT(
        KC_ESC     , KC_1       , KC_2       , KC_3      , KC_4      , KC_5      ,                         KC_6      , KC_7      , KC_8      , KC_9      , KC_0      , KC_MEDIA_PLAY_PAUSE ,
        CK_TAB     , KC_Q       , KC_W       , KC_E      , KC_R      , KC_T      ,                         KC_Y      , KC_U      , KC_I      , KC_O      , KC_P      , CK_BSPC   ,
        MO(LLIN1)  , KC_A       , KC_S       , KC_D      , KC_F      , KC_G      ,                         KC_H      , KC_J      , KC_K      , KC_L      , KC_SCLN   , MO(LLIN1) ,
        CK_LSFT    , KC_Z       , KC_X       , CK_C      , KC_V      , KC_B      , KC_VOLD   , KC_VOLU   , KC_N      , KC_M      , KC_COMM   , KC_DOT    , KC_SLSH   , CK_LSFT   ,
                                                           CK_LCTL   , CK_LALT   , KC_SPC    , KC_ENT    , CK_LSFT   , CK_RCTL
    ),
    [LLIN1] = LAYOUT(
        KC_MPRV    , KC_F1      , KC_F2      , KC_F3     , KC_F4     , KC_F5     ,                         KC_F6     , KC_F7     , KC_F8     , KC_F9     , KC_F10    , KC_MNXT   ,
        CK_TAB     , KC_EXLM    , KC_AT      , KC_CIRC   , KC_DLR    , KC_PERC   ,                         KC_PIPE   , KC_LBRC   , KC_RBRC   , KC_QUOT   , KC_PPLS   , CK_BSPC   ,
        KC_DEL     , KC_TILD    , KC_HASH    , KC_AMPR   , KC_LPRN   , KC_RPRN   ,                         CK_LEFT   , KC_DOWN   , KC_UP     , CK_RIGHT  , KC_PMNS   , KC_F11    ,
        CK_LSFT    , KC_QUES    , SGL_BTICK  , KC_ASTR   , KC_UNDS   , KC_F11    , TO(LSPEC0), TO(LSPEC0), KC_F12    , KC_PEQL   , KC_LT     , KC_GT     , SGL_BSLS  , KC_F11   ,
                                                           CK_LCTL   , CK_LALT   , KC_SPC    , KC_ESC    , CK_LSFT   , CK_RCTL
    ),
};
