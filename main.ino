#include "config.h"
#include "renderer.h"
#include "messages.h"
#include <EEPROM.h>

// ─── Objects ───────────────────────────────────────────────────
Renderer renderer;

// ─── State ─────────────────────────────────────────────────────
int           totalPresses  = 0;
bool          showingMsg    = false;
unsigned long msgShownAt    = 0;
int           lastMsgIdx    = -1;

// ─── Button ────────────────────────────────────────────────────
bool          lastBtn       = HIGH;
unsigned long lastDebounce  = 0;

// ─── EEPROM ────────────────────────────────────────────────────
#define EEPROM_MAGIC  0xBE
#define ADDR_MAGIC    0
#define ADDR_COUNT    1   // 2 bytes (uint16)

void loadCount() {
  EEPROM.begin(8);
  if (EEPROM.read(ADDR_MAGIC) == EEPROM_MAGIC) {
    totalPresses  = EEPROM.read(ADDR_COUNT)
                  | (EEPROM.read(ADDR_COUNT + 1) << 8);
  } else {
    totalPresses  = 0;
  }
  Serial.print("[COUNT] Loaded: ");
  Serial.println(totalPresses);
}

void saveCount() {
  EEPROM.write(ADDR_MAGIC,     EEPROM_MAGIC);
  EEPROM.write(ADDR_COUNT,     totalPresses & 0xFF);
  EEPROM.write(ADDR_COUNT + 1, (totalPresses >> 8) & 0xFF);
  EEPROM.commit();
}

// ─── Pick a response ───────────────────────────────────────────
const char* pickResponse() {
  // Avoid repeating the same one twice
  int idx;
  do { idx = (int)(millis() % RESPONSE_COUNT); }
  while (idx == lastMsgIdx && RESPONSE_COUNT > 1);
  lastMsgIdx = idx;
  return RESPONSES[idx];
}

// ─── Check milestone ───────────────────────────────────────────
const char* checkMilestone(int count) {
  for (int i = 0; i < MILESTONE_COUNT; i++) {
    if (MILESTONES[i].count == count) return MILESTONES[i].msg;
  }
  return nullptr;
}

// ──────────────────────────────────────────────────────────────
void setup() {
  Serial.begin(DEBUG_BAUD);
  delay(100);
  Serial.println("\n\n== 5 Star Do Nothing Device ==");

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  loadCount();

  if (!renderer.begin()) {
    Serial.println("[FATAL] Display failed");
    while (1) yield();
  }

  renderer.drawBoot();
  delay(2000);
  renderer.drawIdle(totalPresses);
  Serial.println("[APP] Ready. Press the button. Nothing will happen.");
}

// ──────────────────────────────────────────────────────────────
void loop() {
  unsigned long now = millis();

  // ── Button read ────────────────────────────────────────────
  bool raw = digitalRead(BUTTON_PIN);
  if (raw != lastBtn) lastDebounce = now;

  if ((now - lastDebounce) > DEBOUNCE_MS) {
    if (lastBtn == HIGH && raw == LOW) {
      // Button pressed
      totalPresses++;
      saveCount();
      Serial.print("[PRESS] Total: ");
      Serial.println(totalPresses);

      // Check milestone first
      const char* milestone = checkMilestone(totalPresses);
      if (milestone) {
        renderer.drawMilestone(milestone, totalPresses);
      } else {
        renderer.drawResponse(pickResponse());
      }

      showingMsg = true;
      msgShownAt = now;
    }
    lastBtn = raw;
  }

  // ── Return to idle after timeout ───────────────────────────
  if (showingMsg && (now - msgShownAt >= IDLE_MS)) {
    showingMsg = false;
    renderer.drawIdle(totalPresses);
  }

  yield();
}
