
#include "Keyboard.h"
#include <ezButton.h>
#include "keycodes.h"
#include "config.h"


const int BUTTON_NUM = 9;

const ezButton buttons[] = {
	ezButton(21), 
	ezButton(20), 
  ezButton(19),
	ezButton(18), 
	ezButton(15), 
	ezButton(14),
  ezButton(16), 
	ezButton(10), 
	ezButton(9), 
};

const int pins[] = {
  21,
  20,
  19,
  18,
  15,
  14,
  16,
  10,
  9,
};

// A Mac equivalent requires the "Unicode Hex Input" to be enabled,
// then hold Option, enter the keycode, release Option.

void sendSequenceMac(String seq){
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.print(seq);
  delay(20);
  Keyboard.releaseAll();
  delay(100);
  }

// void sendSequenceMac(String seq){
//   Keyboard.press(KEY_LEFT_CTRL);
//   Keyboard.press(KEY_LEFT_GUI);
//   Keyboard.press(' ');
//   Keyboard.releaseAll();
//   delay(500);
//   Keyboard.write('CAT');
//   Keyboard.press(KEY_DOWN_ARROW);
//   Keyboard.press(KEY_RETURN);
//   Keyboard.releaseAll();
//   delay(500);
// }

void setup() {
  Keyboard.begin();
  for(int i=0;i<BUTTON_NUM;i++){
    buttons[i].setDebounceTime(50);
  }
}

void loop() {

  for(int i=0;i<BUTTON_NUM;i++){
    buttons[i].loop();
  }

  for(int i=0;i<BUTTON_NUM;i++){
    if(buttons[i].isPressed()) {
      sendSequenceMac(A_KEYMAP[i]);
      // String numberString = String(pins[i]);
      // Keyboard.print(numberString);
    }
  }
}



