#pragma once

#define OLED_SDA        4
#define OLED_SCL        5
#define OLED_WIDTH      128
#define OLED_HEIGHT     64
#define OLED_RESET      -1
#define OLED_I2C_ADDR   0x3C

#define BUTTON_PIN      0       // GPIO0 / FLASH button
#define DEBOUNCE_MS     50

#define IDLE_MS         4000    // Return to idle after 4s
#define DEBUG_BAUD      115200
