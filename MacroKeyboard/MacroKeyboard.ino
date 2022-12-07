
#include "Keyboard.h"
#include <ezButton.h>
#include "keycodes.h"
#include "config.h"
#include "Arduino.h"
#include <CoopTask.h>

CoopTask<>* taskKeyboard;
int singlePressedButton = -1;

void setup() {
  Keyboard.begin();
  // Scheduler.startLoop(loop2);
  taskKeyboard = createCoopTask(F("Keyboard"), loopKeyboard);

  Serial.begin(9600);

  for(int i=0;i<NUM_BUTTONS;i++){
    buttons[i].setDebounceTime(50);
  }
}

void loop() {
  // int [NUM_BUTTONS] pressed;

  for(int i=0;i<NUM_BUTTONS;i++){
    buttons[i].loop();
  }

  for (int i=0;i<NUM_BUTTONS;i++){
    if (buttons[i].isPressed()) {
      singlePressedButton = i;

    }
  }

  runCoopTasks();

  yield();
}

void loopKeyboard() {
  for (;;) {
    if (singlePressedButton >= 0) {
      // sendSequenceMac(A_KEYMAP[singlePressedButton]);
      sendSequenceWindows(W_KEYMAP[singlePressedButton]);
        // Serial.println("wut wut");

      singlePressedButton = -1;
    }
    delay(10);
  }

  return 0;
}

// A Mac equivalent requires the "Unicode Hex Input" to be enabled,
// then hold Option, enter the keycode, release Option.
void sendSequenceMac(String seq){
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
void sendSequenceLinux(String seq) {
  Serial.println(seq);
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

