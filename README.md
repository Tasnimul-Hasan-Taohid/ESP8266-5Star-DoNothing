# 🍫 5 Star Do Nothing Device

Inspired by Cadbury 5 Star's legendary "Do Nothing" philosophy, this is a physical button that does exactly nothing and tells you about it.

If you press the button. The OLED says something. Nothing happens. Then you press it again. This continues indefinitely. Your press count is saved to EEPROM so it survives power-offs. There are milestone messages at 1, 5, 10, 25, 50, 100, 200, and 500 presses in case you really commit to the bit.

This is a useless device. That is the point. 5 Star would be proud.

---

## Features

- 25 hand-written "Do Nothing" responses
- Milestone roasts at 8 different press counts
- Press count saved to EEPROM (survives reboot)
- Idle screen shows total "nothings done"
- Boot animation with pixel art 5★ logo

---

## Hardware

Same as every other repo in this series:

| Part | Detail |
|---|---|
| Board | ESP8266 — NodeMCU or Wemos D1 Mini |
| Display | 0.96" OLED SSD1306 I2C |
| Button | GPIO0 (the built-in FLASH button works perfectly) |

Wiring: D1→SCL, D2→SDA, 3.3V→VCC, GND→GND. Done.

---

## Libraries

- Adafruit GFX
- Adafruit SSD1306

---

## Milestone messages

| Presses | Message |
|---|---|
| 1 | "First press. Here we go." |
| 5 | "5 presses. 5 Star approved." |
| 10 | "10 presses. Someone stop you?" |
| 25 | "25 presses. Get some help." |
| 50 | "50 presses. You need a 5 Star. SERIOUSLY." |
| 100 | "100 presses. This is your life now. Congrats." |
| 200 | "200 presses. Call your mum." |
| 500 | "500 presses. Legend." |

---

## Why does this exist

No reason. 5 Star said do nothing. We did nothing. In firmware.

---

## License

MIT. Do nothing with it.
