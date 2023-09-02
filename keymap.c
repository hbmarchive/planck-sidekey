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

// Stores state of M_ALTT macro - true if we are currently tabbing between
// windows.
static bool m_altt_pressed = false;

// Toggle for keys that affect the the desktop - value can be changed in
// function layer
static bool m_is_chromebook = false;

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
    KC_CAPS, KC_CAPS,  KC_NUBS,        KC_RBRC,     KC_RCBR,  KC_RPRN,  KC_SCLN,  KC_QUOT,         KC_BSLS,        KC_GRV,   KC_SLSH,  KC_TRNS,
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
  switch (keycode) {
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
