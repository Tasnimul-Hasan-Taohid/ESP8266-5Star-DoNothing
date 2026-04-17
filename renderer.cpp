#include "renderer.h"

Renderer::Renderer() : _d(OLED_WIDTH, OLED_HEIGHT, &Wire, OLED_RESET) {}

bool Renderer::begin() {
  Wire.begin(OLED_SDA, OLED_SCL);
  if (!_d.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDR)) return false;
  _d.clearDisplay();
  _d.setTextColor(SSD1306_WHITE);
  _d.display();
  return true;
}

// ─── Boot ──────────────────────────────────────────────────────
void Renderer::drawBoot() {
  _d.clearDisplay();

  // Draw a chunky 5-star logo (pixel art)
  // Big "5" on left, stars on right
  _d.setTextSize(3);
  _d.setCursor(8, 10);
  _d.print("5");

  // Star shapes (5 small stars in a row)
  auto drawStar = [&](int cx, int cy, int r) {
    // Simple 4-point cross star
    _d.drawFastHLine(cx - r, cy, r * 2 + 1, SSD1306_WHITE);
    _d.drawFastVLine(cx, cy - r, r * 2 + 1, SSD1306_WHITE);
    _d.drawLine(cx - r + 1, cy - r + 1, cx + r - 1, cy + r - 1, SSD1306_WHITE);
    _d.drawLine(cx + r - 1, cy - r + 1, cx - r + 1, cy + r - 1, SSD1306_WHITE);
    _d.fillCircle(cx, cy, r / 2, SSD1306_WHITE);
  };

  int starY = 20;
  for (int i = 0; i < 5; i++) {
    drawStar(54 + i * 15, starY, 5);
  }

  _d.setTextSize(1);
  _centered("STAR", 36);
  _d.drawFastHLine(20, 44, 88, SSD1306_WHITE);
  _centered("Do Nothing Device", 48);

  _d.display();
}

// ─── Idle screen ───────────────────────────────────────────────
void Renderer::drawIdle(int totalPresses) {
  _d.clearDisplay();

  // Big "5★" centred top
  _d.setTextSize(2);
  _centered("5 STAR", 4, 2);

  _d.drawFastHLine(0, 22, OLED_WIDTH, SSD1306_WHITE);

  _d.setTextSize(1);
  _centered("DO  NOTHING", 28);
  _centered("DEVICE", 38);

  _d.drawFastHLine(0, 50, OLED_WIDTH, SSD1306_WHITE);

  // Press count bottom
  String s = "Nothings done: " + String(totalPresses);
  _centered(s, 54);

  _d.display();
}

// ─── Response screen ───────────────────────────────────────────
void Renderer::drawResponse(const char* msg) {
  _d.clearDisplay();

  // Top strip
  _d.fillRect(0, 0, OLED_WIDTH, 12, SSD1306_WHITE);
  _d.setTextColor(SSD1306_BLACK);
  _d.setTextSize(1);
  _centered("5 STAR", 2);
  _d.setTextColor(SSD1306_WHITE);

  // Message
  _wrapped(msg, 4, 18);

  // Bottom strip
  _d.fillRect(0, 55, OLED_WIDTH, 9, SSD1306_WHITE);
  _d.setTextColor(SSD1306_BLACK);
  _centered("Do Nothing.", 57);
  _d.setTextColor(SSD1306_WHITE);

  _d.display();
}

// ─── Milestone screen ──────────────────────────────────────────
void Renderer::drawMilestone(const char* msg, int count) {
  _d.clearDisplay();

  // Inverted header
  _d.fillRect(0, 0, OLED_WIDTH, 12, SSD1306_WHITE);
  _d.setTextColor(SSD1306_BLACK);
  _centered("MILESTONE!", 2);
  _d.setTextColor(SSD1306_WHITE);

  // Count big
  _d.setTextSize(2);
  _centered(String(count), 16, 2);
  _d.setTextSize(1);

  _d.drawFastHLine(0, 32, OLED_WIDTH, SSD1306_WHITE);

  _wrapped(msg, 4, 36);

  _d.display();
}

// ─── Helpers ───────────────────────────────────────────────────
void Renderer::_centered(const String& t, int y, uint8_t sz) {
  _d.setTextSize(sz);
  int16_t x1, y1; uint16_t w, h;
  _d.getTextBounds(t, 0, 0, &x1, &y1, &w, &h);
  _d.setCursor(max(0, (int)((OLED_WIDTH - (int)w) / 2)), y);
  _d.print(t);
}

void Renderer::_wrapped(const char* text, int x, int y) {
  _d.setTextSize(1);
  int cx = x, cy = y;
  String word = "";
  const char* p = text;
  while (*p) {
    if (*p == '\n') {
      if (word.length()) { _d.setCursor(cx, cy); _d.print(word); word = ""; }
      cx = x; cy += 9; p++; continue;
    }
    word += *p++;
    if ((cx - x + (int)word.length() * 6) >= OLED_WIDTH - x - 2) {
      cx = x; cy += 9;
    }
    if (*p == ' ' || !*p) {
      _d.setCursor(cx, cy);
      _d.print(word);
      cx += word.length() * 6 + 4;
      word = "";
      if (*p) p++;
    }
  }
  if (word.length()) { _d.setCursor(cx, cy); _d.print(word); }
}
