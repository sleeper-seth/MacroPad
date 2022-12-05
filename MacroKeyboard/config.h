
const int NUM_BUTTONS = 9;
const String KEYMAP[NUM_BUTTONS] = {
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

/**
 * This is the KEYMAP for Apple. Need because Apple reqiures a different part.
 */
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

const int pins[NUM_BUTTONS] = {
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