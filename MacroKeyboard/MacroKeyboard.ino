
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
        Serial.println("wut wut");

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


