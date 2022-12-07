/*
  1 2 3
  4 5 6
  7 8 9
*/

const int NUM_BUTTONS = 9;

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
const String A_KEYMAP[NUM_BUTTONS] = {
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

// Pin connections
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
