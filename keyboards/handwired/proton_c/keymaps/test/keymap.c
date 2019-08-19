/* Copyright 2019
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

/*                        ________
 *           ,-----------| usb-c  |-----------,
 *           |O 5v                     A9/TX O| J -
 *  gnd OLED |O GND                   A10/RX O| I -
 *           |O DFU                      GND O|
 *  vcc OLED |O 3.3v                     GND O| switch gnd
 *       - R |O A2                    SDA/B7 O| OLED sda
 *       - Q |O A1                    SCL/B6 O| OLED scl
 *       - P |O A0                        B5 O| F -
 *       - O |O B8                        B4 O| E -
 *       - N |O B13/SCLK     C13/LED []   B3 O| D -
 *       - M |O B14/MISO                  B2 O| C -
 *       - L |O B15/MOSI                  B1 O| B -
 *       - K |O B9                        B0 O| A -
 *            =----==---============---==----=
 *   - space |O B10                       A4 O|
 *       - Z |O B11                       A5 O|
 *       - Y |O B12                       A6 O| V -
 *       - X |O B14/SWC                   A7 O| U -
 *       - W |O B13/SWD                   A8 O| T -
 *           |O RST                      A15 O| S -
 *           '--------------------------------'
 *
 *           ,--------------,
 *           | B0 | B1 | B2 |
 *           '--------------'
 * */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//   B0,                  B1,              B2
[0] = LAYOUT_3x1( LCTL(LGUI(KC_LEFT)), LCTL(KC_LSHIFT), LCTL(LGUI(KC_RIGHT)) )
};


#ifdef OLED_DRIVER_ENABLE
void oled_task_user(void) {
  // Host Keyboard Layer Status
  oled_write_P(PSTR("Layer: "), false);
  switch (biton32(layer_state)) {
    case 0:
      oled_write_P(PSTR("Default\n"), false);
      break;
    case 1:
      oled_write_P(PSTR("FN\n"), false);
      break;
    case 2:
      oled_write_P(PSTR("ADJ\n"), false);
      break;
    default:
      // Or use the write_ln shortcut over adding '\n' to the end of your string
      oled_write_ln_P(PSTR("Undefined"), false);
  }

  // Host Keyboard LED Status
  uint8_t led_usb_state = host_keyboard_leds();
  oled_write_P(led_usb_state & (1<<USB_LED_NUM_LOCK) ? PSTR("NUMLCK ") : PSTR("       "), false);
  oled_write_P(led_usb_state & (1<<USB_LED_CAPS_LOCK) ? PSTR("CAPLCK ") : PSTR("       "), false);
  oled_write_P(led_usb_state & (1<<USB_LED_SCROLL_LOCK) ? PSTR("SCRLCK ") : PSTR("       "), false);
}
#endif