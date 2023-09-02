#include QMK_KEYBOARD_H

enum my_layers {
  BASE_LAYER,
  RIGHT_TAP_LAYER,
  RIGHT_HOLD_LAYER,
  LEFT_TAP_LAYER,
  LEFT_HOLD_LAYER
};

enum my_keycodes {
    M_ALTT = SAFE_RANGE,
    M_NDESK,
    M_PDESK,
    M_XTAB,
    M_APP1,
    M_APP2,
    M_APP3,
    M_APP4,
    M_1PASS,
    M_NTRM,
    M_EMOJI,
    M_ISCB,
    M_ISWIN
};

// Tap-hold tap dances require custom types and functions.

typedef enum {
  TD_NONE,
  TD_UNKNOWN,
  TD_SINGLE_TAP,
  TD_DOUBLE_TAP,
  TD_HOLD
} td_state_t;

typedef struct {
  td_state_t state;
} td_tap_t;

static td_tap_t td_left = {
  .state = TD_NONE
};

static td_tap_t td_right = {
  .state = TD_NONE
};

td_state_t td_get_state(tap_dance_state_t *state);

void left_finished(tap_dance_state_t *state, void *user_data);
void left_reset(tap_dance_state_t *state, void *user_data);
void right_finished(tap_dance_state_t *state, void *user_data);
void right_reset(tap_dance_state_t *state, void *user_data);

// Tap Dance definitions

enum {
  TD_LEFT,
  TD_RIGHT
};

tap_dance_action_t tap_dance_actions[] = {
    [TD_LEFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, left_finished, left_reset),
    [TD_RIGHT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, right_finished, right_reset)
};

// Stores state of M_ALTT macro - true if we are currently tabbing between
// windows.
static bool m_altt_pressed = false;

// Toggle for keys that affect the the desktop - value can be changed in
// function layer
static bool m_is_chromebook = false;

// Used to temporarily store the state of the mod keys.
static uint8_t mod_state = 0;

// State for managing shift backspace behaviour.
static bool kc_del_registered = false;










const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [BASE_LAYER] = LAYOUT_planck_grid(
    KC_ESC,               KC_Q,           KC_W,           KC_F,           KC_P,           KC_B,    KC_J,    KC_L,    KC_U,           KC_Y,           KC_NUBS,        KC_DEL,
    KC_TAB,               KC_A,           KC_R,           KC_S,           KC_T,           KC_G,    KC_M,    KC_N,    KC_E,           KC_I,           KC_O,           KC_BSPC,
    OSL(LEFT_TAP_LAYER),  KC_Z,           KC_X,           KC_C,           KC_D,           KC_V,    KC_K,    KC_H,    KC_COMM,        KC_DOT,         KC_SLSH,        OSL(RIGHT_TAP_LAYER),
    MO(LEFT_HOLD_LAYER),  OSM(MOD_LCTL),  OSM(MOD_LALT),  OSM(MOD_LGUI),  OSM(MOD_LSFT),  KC_SPC,  KC_ENT,  KC_ESC,  OSM(MOD_RGUI),  OSM(MOD_RALT),  OSM(MOD_RCTL),  MO(RIGHT_HOLD_LAYER)
  ),

  [RIGHT_TAP_LAYER] = LAYOUT_planck_grid(
    KC_TRNS,  KC_EXLM,  LSFT(KC_2),     LSFT(KC_3),  KC_DLR,   KC_PERC,  KC_CIRC,  KC_AMPR,         KC_ASTR,        KC_UNDS,  KC_PLUS,  KC_TRNS,
    KC_TRNS,  KC_TAB,   LSFT(KC_NUBS),  KC_LBRC,     KC_LCBR,  KC_LPRN,  KC_COLN,  LSFT(KC_QUOT),   LSFT(KC_BSLS),  KC_MINS,  KC_EQL,   KC_TRNS,
    KC_TRNS,  KC_CAPS,  KC_NUBS,        KC_RBRC,     KC_RCBR,  KC_RPRN,  KC_SCLN,  KC_QUOT,         KC_BSLS,        KC_GRV,   KC_SLSH,  KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,        KC_TRNS,     KC_NO,    KC_NO,    KC_NO,    TO(BASE_LAYER),  KC_TRNS,        KC_TRNS,  KC_TRNS,  KC_TRNS
  ),

  [RIGHT_HOLD_LAYER] = LAYOUT_planck_grid(
    KC_TRNS,  KC_PAST,  KC_1,     KC_2,     KC_3,        KC_PPLS,     KC_NO,       KC_NO,       KC_NO,    KC_NO,    KC_NO,    KC_TRNS,
    KC_TRNS,  KC_PSLS,  KC_4,     KC_5,     KC_6,        KC_PMNS,     KC_NO,       M_NTRM,      M_EMOJI,  KC_NO,    KC_NO,    KC_TRNS,
    KC_TRNS,  KC_0,     KC_7,     KC_8,     KC_9,        KC_DOT,      KC_NO,       KC_NO,       KC_NO,    KC_NO,    KC_NO,    KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  LCTL(KC_C),  LCTL(KC_V),  LCTL(KC_V),  LCTL(KC_C),  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS
  ),

  [LEFT_TAP_LAYER] = LAYOUT_planck_grid(
    KC_TRNS,  KC_NO,    KC_F1,    KC_F2,    KC_F3,   KC_F4,   M_XTAB,   M_ISWIN,         M_ISCB,   KC_PSCR,  KC_INS,        KC_TRNS,
    KC_TRNS,  KC_NO,    KC_F5,    KC_F6,    KC_F7,   KC_F8,   KC_BRIU,  KC_VOLU,         KC_MPLY,  KC_MNXT,  LSFT(KC_INS),  KC_TRNS,
    KC_TRNS,  KC_Z,     KC_F9,    KC_F10,   KC_F11,  KC_F12,  KC_BRID,  KC_VOLD,         KC_MUTE,  KC_MPRV,  LCTL(KC_INS),  KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_NO,   KC_NO,   KC_NO,    TO(BASE_LAYER),  KC_TRNS,  KC_TRNS,  KC_TRNS,       KC_TRNS
  ),

  [LEFT_HOLD_LAYER] = LAYOUT_planck_grid(
    KC_TRNS,  KC_NO,    KC_NO,    KC_NO,    KC_NO,       KC_NO,             M_XTAB,      M_PDESK,     LCTL(KC_TAB),  M_ALTT,   M_NDESK,  KC_TRNS,
    KC_TRNS,  KC_NO,    M_APP4,   M_APP1,   M_APP2,      M_APP3,            KC_WH_U,     KC_LEFT,     KC_DOWN,       KC_UP,    KC_RGHT,  KC_TRNS,
    KC_TRNS,  KC_NO,    KC_NO,    KC_NO,    M_1PASS,     LSFT(LCTL(KC_C)),  KC_WH_D,     KC_HOME,     KC_PGDN,       KC_PGUP,  KC_END,   KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  LCTL(KC_C),  LCTL(KC_V),        LCTL(KC_V),  LCTL(KC_C),  KC_TRNS,       KC_TRNS,  KC_TRNS,  KC_TRNS
  ),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  // Stop pressing the alt key once a key other than the alt-tab macro has been
  // pressed.
  if (keycode != M_ALTT && m_altt_pressed) {
    unregister_code(KC_LALT);
    m_altt_pressed = false;
  }

  // Ensure shift is not pressed when the tap layers is active.
  if (IS_LAYER_ON(LEFT_TAP_LAYER) || IS_LAYER_ON(RIGHT_TAP_LAYER)) {
    switch (keycode) {
      case KC_Z:
      case KC_SLSH:
        break;
      default:
        del_mods(MOD_MASK_SHIFT);
        del_oneshot_mods(MOD_MASK_SHIFT);
    }
  }

  mod_state = get_mods();

  switch (keycode) {
    // Shift-backspace produces delete.
    case KC_BSPC:
      if (record->event.pressed) {
        if (mod_state & MOD_MASK_SHIFT) {
          del_mods(MOD_MASK_SHIFT);
          register_code(KC_DEL);
          kc_del_registered = true;
          set_mods(mod_state);
          return false;
        }
      } else {
        if (kc_del_registered) {
          unregister_code(KC_DEL);
          kc_del_registered = false;
          return false;
        }
      }
      break;
    case M_ALTT:
      if (record->event.pressed) {
        if (!m_altt_pressed) {
          register_code(KC_LALT);
          m_altt_pressed = true;
        }
        tap_code(KC_TAB);
      }
      break;
    case M_APP1:
      if (record->event.pressed) {
        if (m_is_chromebook) {
          SEND_STRING(SS_DOWN(X_LALT));
          SEND_STRING(SS_TAP(X_1));
          SEND_STRING(SS_UP(X_LALT));
        } else {
          SEND_STRING(SS_DOWN(X_LSFT)SS_DOWN(X_LCTL)SS_DOWN(X_LALT)SS_DOWN(X_LGUI));
          SEND_STRING(SS_TAP(X_1));
          SEND_STRING(SS_UP(X_LGUI)SS_UP(X_LALT)SS_UP(X_LCTL)SS_UP(X_LSFT));
        }
      }
      break;
    case M_APP2:
      if (record->event.pressed) {
        if (m_is_chromebook) {
          SEND_STRING(SS_DOWN(X_LALT));
          SEND_STRING(SS_TAP(X_2));
          SEND_STRING(SS_UP(X_LALT));
        } else {
          SEND_STRING(SS_DOWN(X_LSFT)SS_DOWN(X_LCTL)SS_DOWN(X_LALT)SS_DOWN(X_LGUI));
          SEND_STRING(SS_TAP(X_2));
          SEND_STRING(SS_UP(X_LGUI)SS_UP(X_LALT)SS_UP(X_LCTL)SS_UP(X_LSFT));
        }
      }
      break;
    case M_APP3:
      if (record->event.pressed) {
        if (m_is_chromebook) {
          SEND_STRING(SS_DOWN(X_LALT));
          SEND_STRING(SS_TAP(X_3));
          SEND_STRING(SS_UP(X_LALT));
        } else {
          SEND_STRING(SS_DOWN(X_LSFT)SS_DOWN(X_LCTL)SS_DOWN(X_LALT)SS_DOWN(X_LGUI));
          SEND_STRING(SS_TAP(X_3));
          SEND_STRING(SS_UP(X_LGUI)SS_UP(X_LALT)SS_UP(X_LCTL)SS_UP(X_LSFT));
        }
      }
      break;
    case M_APP4:
      if (record->event.pressed) {
        if (m_is_chromebook) {
          SEND_STRING(SS_DOWN(X_LALT));
          SEND_STRING(SS_TAP(X_4));
          SEND_STRING(SS_UP(X_LALT));
        } else {
          SEND_STRING(SS_DOWN(X_LSFT)SS_DOWN(X_LCTL)SS_DOWN(X_LALT)SS_DOWN(X_LGUI));
          SEND_STRING(SS_TAP(X_4));
          SEND_STRING(SS_UP(X_LGUI)SS_UP(X_LALT)SS_UP(X_LCTL)SS_UP(X_LSFT));
        }
      }
      break;
    case M_1PASS:
      if (record->event.pressed) {
        if (m_is_chromebook) {
          SEND_STRING(SS_DOWN(X_LALT)SS_TAP(X_1)SS_UP(X_LALT));
          SEND_STRING(SS_DELAY(100));
          SEND_STRING(SS_DOWN(X_LSFT)SS_DOWN(X_LCTL));
          SEND_STRING(SS_TAP(X_X));
          SEND_STRING(SS_UP(X_LCTL)SS_UP(X_LSFT));
        } else {
          SEND_STRING(SS_DOWN(X_LSFT)SS_DOWN(X_LCTL));
          SEND_STRING(SS_TAP(X_SPC));
          SEND_STRING(SS_UP(X_LCTL)SS_UP(X_LSFT));
        }
      }
      break;
    case M_NDESK:
      if (record->event.pressed) {
        if (m_is_chromebook) {
          SEND_STRING(SS_DOWN(X_LGUI));
          SEND_STRING(SS_TAP(X_RBRC));
          SEND_STRING(SS_UP(X_LGUI));
        } else {
          SEND_STRING(SS_DOWN(X_LCTL)SS_DOWN(X_LGUI));
          SEND_STRING(SS_TAP(X_RGHT));
          SEND_STRING(SS_UP(X_LGUI)SS_UP(X_LCTL));
        }
      }
      break;
    case M_PDESK:
      if (record->event.pressed) {
        if (m_is_chromebook) {
          SEND_STRING(SS_DOWN(X_LGUI));
          SEND_STRING(SS_TAP(X_LBRC));
          SEND_STRING(SS_UP(X_LGUI));
        } else {
          SEND_STRING(SS_DOWN(X_LCTL)SS_DOWN(X_LGUI));
          SEND_STRING(SS_TAP(X_LEFT));
          SEND_STRING(SS_UP(X_LGUI)SS_UP(X_LCTL));
        }
      }
      break;
    case M_XTAB:
      if (record->event.pressed) {
        if (m_is_chromebook) {
          SEND_STRING(SS_DOWN(X_LCTL)SS_TAP(X_W)SS_UP(X_LCTL));
        } else {
          SEND_STRING(SS_DOWN(X_LCTL)SS_TAP(X_F4)SS_UP(X_LCTL));
        }
      }
      break;
    case M_NTRM:
      if (record->event.pressed) {
        if (m_is_chromebook) {
          SEND_STRING(SS_DOWN(X_LCTL)SS_TAP(X_T)SS_UP(X_LCTL));
        } else {
          SEND_STRING(SS_DOWN(X_LSFT)SS_DOWN(X_LCTL));
          SEND_STRING(SS_TAP(X_1));
          SEND_STRING(SS_UP(X_LCTL)SS_UP(X_LSFT));
        }
      }
      break;
    case M_EMOJI:
      if (record->event.pressed) {
        if (m_is_chromebook) {
          SEND_STRING(SS_DOWN(X_LSFT)SS_DOWN(X_LGUI));
          SEND_STRING(SS_TAP(X_SPC));
          SEND_STRING(SS_UP(X_LGUI)SS_UP(X_LSFT));
        } else {
          SEND_STRING(SS_DOWN(X_LGUI)SS_TAP(X_SCLN)SS_UP(X_LGUI));
        }
      }
      break;
    case M_ISCB:
      if (record->event.pressed) {
        m_is_chromebook = true;
      }
      break;
    case M_ISWIN:
      if (record->event.pressed) {
        m_is_chromebook = false;
      }
      break;
  }

  return true;
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (!record->event.pressed) {
    if (IS_LAYER_ON(LEFT_TAP_LAYER) && keycode != TD(TD_LEFT)) {
      layer_off(LEFT_TAP_LAYER);
    }
  }
  if (!record->event.pressed) {
    if (IS_LAYER_ON(RIGHT_TAP_LAYER) && keycode != TD(TD_RIGHT)) {
      layer_off(RIGHT_TAP_LAYER);
    }
  }
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // Set the tapping term for the homerow mods.
    case LCTL_T(KC_W):
    case LALT_T(KC_F):
    case LGUI_T(KC_P):
    case LGUI_T(KC_L):
    case LALT_T(KC_U):
    case LCTL_T(KC_Y):
      return TAPPING_TERM_MODS;
    // Set the tapping term for tap dance keys.
    case TD(TD_LEFT):
    case TD(TD_RIGHT):
      return TAPPING_TERM_TAP_DANCE;
    default:
      return TAPPING_TERM;
  }
}

td_state_t td_get_state(tap_dance_state_t *state) {

  if (state->count == 1) {
    // If the keypress has been interrupted by another keypress or is no longer
    // held down by the end of the tap time, then we know it was just a single
    // tap.
    if (state->interrupted || !state->pressed)
      return TD_SINGLE_TAP;
    else
      // If it is still held at the end of the tap time, then it is a hold.
      return TD_HOLD;
  } else if (state->count > 1) {
    // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and
    // actually wanting a double tap action when hitting 'pp'. Suggested use
    // case for this return value is when you want to send two keystrokes of the
    // key, and not the 'double tap' action/macro.

    // In the case where there has been more than one tap in the tap time, we
    // have to make a judgement call. If the key is still held down we will
    // assume it was a flutter and call it a hold.
    if (state->pressed)
      return TD_HOLD;
    // If the keypress has finished or has been interrupted then we will assume
    // that there was some actual fast typing going on and issue two taps, which
    // will be the most common scenario.
    if (state->interrupted || !state->pressed)
      return TD_DOUBLE_TAP;
  }

  return TD_UNKNOWN;
}

void left_finished(tap_dance_state_t *state, void *user_data) {
    td_left.state = td_get_state(state);
    switch (td_left.state) {
        case TD_SINGLE_TAP:
          layer_on(LEFT_TAP_LAYER);
          break;
        case TD_DOUBLE_TAP:
          register_code(KC_Z);
          break;
        case TD_HOLD:
          layer_on(LEFT_HOLD_LAYER);
          break;
        default:
          break;
    }
}

void left_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_left.state) {
        case TD_SINGLE_TAP:
          // LEFT_TAP_LAYER turned off in post_process_record_user()
          break;
        case TD_DOUBLE_TAP:
          unregister_code(KC_Z);
          break;
        case TD_HOLD:
          layer_off(LEFT_HOLD_LAYER);
        default:
          break;
    }
    td_left.state = TD_NONE;
}

void right_finished(tap_dance_state_t *state, void *user_data) {
    td_right.state = td_get_state(state);
    switch (td_right.state) {
        case TD_SINGLE_TAP:
          layer_on(RIGHT_TAP_LAYER);
          break;
        case TD_DOUBLE_TAP:
          register_code(KC_SLSH);
          break;
        case TD_HOLD:
          layer_on(RIGHT_HOLD_LAYER);
          break;
        default:
          break;
    }
}

void right_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_right.state) {
        case TD_SINGLE_TAP:
          // RIGHT_TAP_LAYER turned off in post_process_record_user()
          break;
        case TD_DOUBLE_TAP:
          unregister_code(KC_SLSH);
          break;
        case TD_HOLD:
          layer_off(RIGHT_HOLD_LAYER);
        default:
          break;
    }
    td_right.state = TD_NONE;
}
