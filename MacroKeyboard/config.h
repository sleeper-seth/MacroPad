/*
  0 1 2  --> Linux mode
  3 4 5  --> Windows Mode
  6 7 8  --> Apple Mode
*/

const int NUM_BUTTONS = 9;
const int MODE_ADDRESS = 22;
const int KEY_IN_EMOTICON_MODE = 2;
const int KEY_IN_SERIAL_MODE = 2;
const int KEY_ADDRESS_START = 30;
const int APPLE_MODE = 1;
const int WINDOWS_MODE = 2;
const int LINUX_MODE = 3;
const int LONG_PRESS_TIME  = 3000; // milliseconds

// Windows
String W_KEYMAP[NUM_BUTTONS] = {
  W_EYES,
  W_BEER,
  W_LOVE_FACE,
  W_FIRE,
  W_THUMBS_UP,
  W_100,
  W_ROFL,
  W_CHECK,
  W_ROCKET
};

// Apple
String A_KEYMAP[NUM_BUTTONS] = {
  A_EYES,
  A_BEER,
  A_LOVE_FACE,
  A_FIRE,
  A_THUMBS_UP,
  A_100,
  A_ROFL,
  A_CHECK,
  A_ROCKET
};

// Pin connections on the PCB
const ezButton buttons[NUM_BUTTONS] = {
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
