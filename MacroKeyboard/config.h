/* This file contains all the user-servicable parts for the emoji keyboard.
 * KEYMAP_SIZE specifies the number of buttons in the keyboard
 * KEYMAP is an array of the unicode symbols to be output when the corresponding pin goes low.
 */
const int KEYMAP_SIZE = 7;
const String KEYMAP[KEYMAP_SIZE] = {
  WINK_TONGUE,
  FROWN,
  SMILE,
  PUKE,
  PILE_OF_POO,
  BLOW_KISS,
  BLOW_KISS,
};

/**
 * This is the KEYMAP for Apple. Need because Apple reqiures a different part.
 */
const String A_KEYMAP[KEYMAP_SIZE] = {
  A_WINK_TONGUE,
  A_FROWN,
  A_SMILE,
  A_PUKE,
  A_PILE_OF_POO,
  A_BLOW_KISS,
  A_BLOW_KISS
};