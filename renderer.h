#pragma once

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "config.h"

class Renderer {
public:
  Renderer();
  bool begin();

  void drawIdle(int totalPresses);
  void drawResponse(const char* msg);
  void drawMilestone(const char* msg, int count);
  void drawBoot();

private:
  Adafruit_SSD1306 _d;
  void _centered(const String& t, int y, uint8_t sz = 1);
  void _wrapped(const char* t, int x, int y);
};
