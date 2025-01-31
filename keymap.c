#include QMK_KEYBOARD_H
#if __has_include("keymap.h")
#    include "keymap.h"
#endif
enum layer_number {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
      KC_ESC , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                        KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_BSPC,
      KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                        KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_MINS,
      KC_LCTL, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,                        KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,
      KC_LGUI, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_LBRC,      KC_RBRC, KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_EQL ,
                        KC_LALT, KC_LSFT, MO(1)  , KC_SPC ,                        KC_ENT , MO(2)  , KC_RSFT, KC_RALT
    ),
    [_LOWER] = LAYOUT(
      KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  ,                        KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
      KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 ,                        KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
      KC_TRNS, KC_MUTE, KC_VOLD, KC_VOLU, KC_BRIU, KC_BRID,                        KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
      KC_TRNS, KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,      KC_DEL , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                        KC_TRNS, MO(3)  , KC_TRNS, KC_TRNS
    ),
    [_RAISE] = LAYOUT(
      KC_TRNS, KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_CAPS,                        KC_PSCR, KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_HOME,
      KC_TRNS, KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,                        KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_END ,
      KC_TRNS, KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,                        KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_PGUP, KC_PGDN,
      KC_TRNS, KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_GRV ,      KC_BSLS, KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
                        KC_TRNS, KC_TRNS, MO(3)  , KC_TRNS,                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [_ADJUST] = LAYOUT(
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                        _______, _______, _______, _______,                         _______, _______, _______, _______
    )
};

#ifdef OTHER_KEYMAP_C
#    include OTHER_KEYMAP_C
#endif // OTHER_KEYMAP_C

//SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) return OLED_ROTATION_90;  // flips the display 90 degrees if offhand
  return OLED_ROTATION_270;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

#define L_BASE 0
#define L_LOWER (1 << 1)
#define L_RAISE (1 << 2)
#define L_ADJUST (1 << 3)
#define L_ADJUST_TRI (L_ADJUST | L_RAISE | L_LOWER)

char layerstate_str[10];

const char *print_layer_state(void) {
  switch (layer_state)
  {
  case L_BASE:
    snprintf(layerstate_str, sizeof(layerstate_str), "BASE ");
    break;
  case L_RAISE:
    snprintf(layerstate_str, sizeof(layerstate_str), "RAISE");
    break;
  case L_LOWER:
    snprintf(layerstate_str, sizeof(layerstate_str), "LOWER");
    break;
  case L_ADJUST:
  case L_ADJUST_TRI:
    snprintf(layerstate_str, sizeof(layerstate_str), "ADJST");
    break;
  default:
    snprintf(layerstate_str, sizeof(layerstate_str), "UNDEF");
  }

  return layerstate_str;
}

char capslock_str[10];
const char *print_caps_lock(void) {
    led_t led_state = host_keyboard_led_state();

    if (led_state.caps_lock) {
        snprintf(capslock_str, sizeof(capslock_str), "CAPS ");
    } else {
        snprintf(capslock_str, sizeof(capslock_str), "     ");
    }

    return capslock_str;
}

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    oled_write(print_layer_state(), false);
    oled_write(print_caps_lock(), false);
  } else {
    oled_write(read_logo(), false);
  }
    return false;
}
#endif // OLED_ENABLE

