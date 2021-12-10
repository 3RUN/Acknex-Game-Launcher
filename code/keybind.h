#ifndef _KEYBIND_H_
#define _KEYBIND_H_

// input words
STRING *input_none_str = "none";
STRING *mouse_left_str = "mouse_left";
STRING *mouse_right_str = "mouse_right";
STRING *mouse_middle_str = "mouse_middle";

// other stuff related to .ini key bindings file
STRING *keybind_section_str = "Key Bindings";

// function to check for specific input keys and return their scancodes!
int keybind_return_scancode_from_letter(STRING *key);

// return a letter from the given scancode
// this can be used for saving input from the game options
STRING *keybind_return_letter_from_scancode(int scancode);

#endif