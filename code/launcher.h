#ifndef _LAUNCHER_H_
#define _LAUNCHER_H_

// launcher menu window size
#define LAUNCHER_WINDOW_WIDTH 640
#define LAUNCHER_WINDOW_HEIGHT 320

// button size
#define BUTTON_WIDTH 96
#define BUTTON_HEIGHT 32

// button size (used for browse button)
#define BROWSE_BUTTON_WIDTH 95
#define BROWSE_BUTTON_HEIGHT 22

// input button size
#define INPUT_BOTTON_WIDTH 256
#define INPUT_BUTTON_HEIGHT 20

// checkbox right edge offset
#define CHECKBOX_OFFSET 23

// combobox offset
#define COMBOBOX_WIDTH 440

// tab IDs
#define TAB_GRAPHICS 0
#define TAB_INPUT 1
#define TAB_GAME 2

// button strings
STRING *launcher_reset_to_def_str = "Reset to defaults";
STRING *launcher_launch_game_str = "Play!";
STRING *launcher_quit_game_str = "Quit";

// wrong path warning message
STRING *launcher_wrong_path_str = "Can't launch the game, set correct path to executable.";

// font
ImFont *launcher_font = NULL;
ImFont *launcher_graphics_tooltip_font = NULL;
ImFont *launcher_input_font = NULL;

// currently selected tab
int launcher_selected_tab_id = 0;

// wrong path to game modal
int is_launcher_has_wrong_path_popup_modal_on = false;
int is_launcher_has_wrong_path_popup_closing = false;

// create configuration window
void launcher_create_window(int width, int height);

// create tooltip with the given string
void launcher_create_tooltip(STRING *str);

// initialize configuration
void launcher_initialize(STRING *config_file);

// show warning message when game's .exe doesn't exist or not found
void launcher_show_wrong_path_to_game_warning();

// update configuration
void launcher_update();

#endif