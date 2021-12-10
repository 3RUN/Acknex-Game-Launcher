#ifndef _LAUNCHER_INPUT_H_
#define _LAUNCHER_INPUT_H_

// not proud of how this looks like... but it works at least xD
// I'm sure there are plenty of ways to improve this, feel free to do so

// input strings
STRING *launcher_input_bind_str = "Press anykey to bind it to selected command!";
STRING *launcher_input_help_command_str = "Command";
STRING *launcher_input_help_key_str = "Key";

// popup modal boolean
int is_launcher_input_popup_modal_on = false;
int is_launcher_input_popup_closing = false;

// helper function to check for input setting
void launcher_input_check_overwrite(STRING *bindkey);

// set input key to the selected action
void launcher_input_bind_new_key(STRING *entry, STRING *bindkey);

// remove binding for the given input
void launcher_input_remove_bind_key(STRING *entry);

// wait for input from user to bind a new key
void launcher_input_wait_for_binding(STRING *entry);

// add keybinding button
void launcher_input_add_keybinding(STRING *entry, STRING *input);

// create input tab config
void launcher_create_input_tab();

#endif