
#include "Keyboard.h"
#include <ezButton.h>
#include "keycodes.h"
#include "config.h"
#include "Arduino.h"
#include <CoopTask.h>
#include <EEPROM.h>

CoopTask<>* taskKeyboard;
int singlePressedButton = -1;
unsigned long pressedTimes[NUM_BUTTONS] = {};

void setup() {
  Keyboard.begin();
  taskKeyboard = createCoopTask(F("Keyboard"), loopKeyboard);

  Serial.begin(9600);

  for(int i=0;i<NUM_BUTTONS;i++){
    buttons[i].setDebounceTime(50);
  }
} 

void loop() {
  bool longPressed[NUM_BUTTONS] = {};
  bool didRelease = false;

  // Loop buttons
  for(int i=0;i<NUM_BUTTONS;i++){
    buttons[i].loop();
  }

  // Check button status
  for (int i = 0; i < NUM_BUTTONS; i++){
    if (buttons[i].isPressed()) {
      singlePressedButton = i;
      pressedTimes[i] = millis();
    }

    if (buttons[i].isReleased()) {
      didRelease = true;
    }
  }

  // Evaluate long press behaviors
  if (didRelease) {
    int singleButton = -1;
    for (int i = 0; i < NUM_BUTTONS; i++){
      if (pressedTimes[i] > 0 && millis() - pressedTimes[i] > LONG_PRESS_TIME) {
        longPressed[i] = true;
        singleButton = i;
      }

      pressedTimes[i] = 0;
    }

    if (longPressed[0] && longPressed[1] && longPressed[2]) {
      EEPROM.update(MODE_ADDRESS, LINUX_MODE);
      Serial.println("LINUX_MODE");

    } else if (longPressed[3] && longPressed[4] && longPressed[5]) {
      EEPROM.update(MODE_ADDRESS, WINDOWS_MODE);
      Serial.println("WINDOWS_MODE");

    } else if (longPressed[6] && longPressed[7] && longPressed[8]) {
      EEPROM.update(MODE_ADDRESS, APPLE_MODE);
      Serial.println("APPLE_MODE");
    } else if (singleButton >= 0) {
      if (EEPROM.read(KEY_ADDRESS_START + singleButton) == KEY_IN_SERIAL_MODE) {
        EEPROM.update(KEY_ADDRESS_START + singleButton, KEY_IN_EMOTICON_MODE);
        Serial.println("Setting to Emoticon Mode");
      } else {
        EEPROM.update(KEY_ADDRESS_START + singleButton, KEY_IN_SERIAL_MODE);
        Serial.println(singleButton);
        Serial.println("Setting to Serial Mode");
      }
    }
  }

  // Run threads and give way
  runCoopTasks();
  yield();
}

void loopKeyboard() {
  for (;;) {
    if (singlePressedButton >= 0) {
      if (EEPROM.read(KEY_ADDRESS_START + singlePressedButton) == KEY_IN_SERIAL_MODE) {
        // Send single key press event over serial for advanced magic
        Serial.println(singlePressedButton);
      } else if (EEPROM.read(MODE_ADDRESS) == WINDOWS_MODE) {
        sendSequenceWindows(W_KEYMAP[singlePressedButton]);
      } else if (EEPROM.read(MODE_ADDRESS) == LINUX_MODE) {
        sendSequenceLinux(U_KEYMAP[singlePressedButton]);
      } else {
        sendSequenceMac(A_KEYMAP[singlePressedButton]);
      }

      singlePressedButton = -1;
    }
    delay(10);
  }

  return 0;
}

// A Mac equivalent requires the "Unicode Hex Input" to be enabled,
// then hold Option, enter the keycode, release Option.
void sendSequenceMac(String &seq){
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.print(seq);
  delay(20);
  Keyboard.releaseAll();
  delay(20);
}

/* The process for entering unicode key codes varies by OS.
 * This implementation is linux-specific, and relies on the code being ctrl+shift+u <keycode> <space>
 * the delay calls are present to prevent overwhelming the host with input.
 */
void sendSequenceLinux(String &seq) {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press('u');
  delay(40);
  Keyboard.releaseAll();
  delay(20);
  Keyboard.print(seq);
  Keyboard.print(" ");
  delay(50);
}

/* Windows requires opening up the emoji input popup
 * It can be a little fiddly, and longer delays are required
 */
void sendSequenceWindows(String &seq) {
  char winKey = KEY_LEFT_GUI;
  char escKey = KEY_ESC;

  Keyboard.press(winKey);
  Keyboard.press('.');
  delay(300);
  Keyboard.release(winKey);
  Keyboard.release('.');
  Keyboard.println(seq);
  delay(150 + seq.length() * 10);
  Keyboard.press(escKey);
  delay(20);

  Keyboard.releaseAll();
}

