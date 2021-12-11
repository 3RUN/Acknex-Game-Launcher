#ifndef _CONFIG_H_
#define _CONFIG_H_

// different display modes
#define DISPLAY_MODES_MAX 3
#define DISPLAY_MODE_WINDOWED 0
#define DISPLAY_MODE_WINDOWED_FULLSCREEN 1
#define DISPLAY_MODE_FULLSCREEN 2

// different quality modes
#define MAX_QUALITY_OPTIONS 4
#define QUALITY_LOW 0
#define QUALITY_MEDIUM 1
#define QUALITY_HIGH 2
#define QUALITY_ULTRA 3

// max amount of available languages
#define GAME_LANGUAGE_MAX 3
#define GAME_LANGUAGE_ENGLISH 0
#define GAME_LANGUAGE_RUSSIAN 1
#define GAME_LANGUAGE_GERMAN 2

// config sections
STRING *config_input_section_str = "Input";
STRING *config_graphics_section_str = "Graphics";
STRING *config_game_section_str = "Game";

// config input entries
STRING *input_forward_entry_str = "Move forward";
STRING *input_backward_entry_str = "Move backward";
STRING *input_left_entry_str = "Move left (strafe)";
STRING *input_right_entry_str = "Move right (strafe)";
STRING *input_toggle_map_entry_str = "Toggle map";

// config graphics entries
STRING *graphics_is_desktop_entry_str = "Use desktop resolution";
STRING *graphics_video_res_id_entry_str = "Video resolution id";
STRING *graphics_display_mode_entry_str = "Display mode";
STRING *graphics_quality_mode_entry_str = "Quality mode";
STRING *graphics_vsync_entry_str = "V-Sync";
STRING *graphics_fps_cap_entry_str = "Fps cap";

// config game entries
STRING *game_language_entry_str = "Language";
STRING *game_path_to_exe_entry_str = "Path to the executable";
STRING *game_browse_button_str = "Browse";

// default input keys
STRING *input_def_forward_str = "w";
STRING *input_def_backward_str = "s";
STRING *input_def_left_str = "a";
STRING *input_def_right_str = "d";
STRING *input_def_toggle_map_str = "m";

// default graphics config
int is_desktop_def_res = false;
int graphics_video_res_def_id = 0;
int graphics_display_def_mode = DISPLAY_MODE_WINDOWED;
int graphics_quality_def_mode = QUALITY_LOW;
int graphics_fps_def_cap = 60;
int is_vsync_def_on = false;

// default game config
STRING *game_def_language_str = "English";
STRING *game_def_path_to_exe_str = "";

// structure to save all game config
typedef struct CONFIG
{
    // input
    char input_forward_str[32];
    char input_backward_str[32];
    char input_left_str[32];
    char input_right_str[32];
    char input_toggle_map_str[32];

    // graphics
    int is_desktop_res;
    int graphics_video_res_id;
    int graphics_display_mode;
    int graphics_quality_mode;
    int graphics_fps_cap;
    int is_vsync_on;

    // game
    char game_language_str[32];
    char game_path_to_exe_str[MAX_PATH];

} CONFIG;

CONFIG config_default; // never changed (used for reseting to default values)
CONFIG config_current; // changed directly in options menu, if cancel button pressed - resets back to old config
CONFIG config_saved;   // previously saved config, if yes/apply button pressed - get's overwritten by current config

// initialize config into the given file
void config_initialize(STRING *config_file);

// save config
var config_save_n_execute();

// reset config to defaults
void config_reset_to_default();

// load config from the file
void config_load_from_file(STRING *config_file);

// save config into the given file
void config_save_to_file(STRING *config_file);

#endif