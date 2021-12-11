
#include <acknex.h>
#include <default.c>
#include <windows.h>
#include <strio.c>

// config file
STRING *config_file_str = "config.ini";
STRING *project_name_str = "Unnamed_Project"; // insert your project's name here !

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

// example string to check if proper language was loaded or not
// it will be filled with text in game_apply_config
STRING *example_str = "Current language is: ";

// 'boolean' to check if all config was loaded and applied
int is_config_applied = false;

#include "keybind.h"
#include "ini.h"
#include "engine.h"
#include "savedir.h"
#include "screenres_list.h"

#include "keybind.c"
#include "engine.c"
#include "savedir.c"
#include "screenres_list.c"

// structure for all config
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

CONFIG config_current;
CONFIG config_default;

// returns path to the save folder
void path_make_absolute(STRING *path)
{
	static STRING *tmp = "#1024";
	str_cpy(tmp, save_dir);
	str_cat(tmp, "\\");
	str_cat(tmp, path);
	str_cpy(path, tmp);
}

// load all config from file
// if there is something wrong with the file ?
// then load default values
void game_load_config_from_file(STRING *config_file)
{
	// initialize default config structure
	strcpy(config_default.input_forward_str, _chr(input_def_forward_str));
	strcpy(config_default.input_backward_str, _chr(input_def_backward_str));
	strcpy(config_default.input_left_str, _chr(input_def_left_str));
	strcpy(config_default.input_right_str, _chr(input_def_right_str));
	strcpy(config_default.input_toggle_map_str, _chr(input_def_toggle_map_str));

	// default graphics settings
	config_default.is_desktop_res = is_desktop_def_res;
	config_default.graphics_video_res_id = graphics_video_res_def_id;
	config_default.graphics_display_mode = graphics_display_def_mode;
	config_default.graphics_quality_mode = graphics_quality_def_mode;
	config_default.graphics_fps_cap = graphics_fps_def_cap;
	config_default.is_vsync_on = is_vsync_def_on;

	// default game settings
	strcpy(config_default.game_language_str, _chr(game_def_language_str));

	// set default path to the working directory + project's name with .exe at the end
	str_cpy(game_def_path_to_exe_str, work_dir);
	str_cat(game_def_path_to_exe_str, project_name_str);
	str_cat(game_def_path_to_exe_str, ".exe");
	strcpy(config_default.game_path_to_exe_str, _chr(game_def_path_to_exe_str));

	// input
	ini_read_write_char(config_current.input_forward_str, config_file, config_input_section_str, input_forward_entry_str, config_default.input_forward_str);
	ini_read_write_char(config_current.input_backward_str, config_file, config_input_section_str, input_backward_entry_str, config_default.input_backward_str);
	ini_read_write_char(config_current.input_left_str, config_file, config_input_section_str, input_left_entry_str, config_default.input_left_str);
	ini_read_write_char(config_current.input_right_str, config_file, config_input_section_str, input_right_entry_str, config_default.input_right_str);
	ini_read_write_char(config_current.input_toggle_map_str, config_file, config_input_section_str, input_toggle_map_entry_str, config_default.input_toggle_map_str);

	// graphics
	ini_read_write_int(&config_current.is_desktop_res, config_file, config_graphics_section_str, graphics_is_desktop_entry_str, config_default.is_desktop_res);
	ini_read_write_int(&config_current.graphics_video_res_id, config_file, config_graphics_section_str, graphics_video_res_id_entry_str, config_default.graphics_video_res_id);
	ini_read_write_int(&config_current.graphics_display_mode, config_file, config_graphics_section_str, graphics_display_mode_entry_str, config_default.graphics_display_mode);
	ini_read_write_int(&config_current.graphics_quality_mode, config_file, config_graphics_section_str, graphics_quality_mode_entry_str, config_default.graphics_quality_mode);
	ini_read_write_int(&config_current.graphics_fps_cap, config_file, config_graphics_section_str, graphics_fps_cap_entry_str, config_default.graphics_fps_cap);
	ini_read_write_int(&config_current.is_vsync_on, config_file, config_graphics_section_str, graphics_vsync_entry_str, config_default.is_vsync_on);

	// game
	ini_read_write_char(config_current.game_language_str, config_file, config_game_section_str, game_language_entry_str, config_default.game_language_str);
	ini_read_write_char(config_current.game_path_to_exe_str, config_file, config_game_section_str, game_path_to_exe_entry_str, config_default.game_path_to_exe_str);
}

// apply all the config in one function
void game_apply_config()
{
	// set fps cap
	fps_max = config_current.graphics_fps_cap;
	
	// v-sync
	d3d_triplebuffer = config_current.is_vsync_on;

	// remove window's borders
	// otherwise window won't fit the screen and will cause troubles
	video_window(NULL, NULL, 1, project_name_str);

	// switch to fullmode if needed
	// this is weird... because it wouldn't change to fullscreen without changing video_mode as well...
	if (config_current.graphics_display_mode == DISPLAY_MODE_FULLSCREEN || config_current.is_desktop_res == true)
	{
		video_mode = 7;
		video_switch(video_mode, 0, 1);
	}

	wait(1); // wait one frame

	// apply them as we need to
	if (config_current.is_desktop_res == true)
	{
		engine_set_resolution_from_id(desktop_resolution_id, DISPLAY_MODE_FULLSCREEN);
	}
	else
	{
		// resolution id
		int id = config_current.graphics_video_res_id;

		// selected resolutionw with display modes
		engine_set_resolution_from_id(id, config_current.graphics_display_mode);
	}

	// graphics quality ?
	// we can set different graphics settings here as we wish
	if (config_current.graphics_quality_mode == QUALITY_LOW)
	{
	}
	else if (config_current.graphics_quality_mode == QUALITY_MEDIUM)
	{
	}
	else if (config_current.graphics_quality_mode == QUALITY_HIGH)
	{
	}
	else if (config_current.graphics_quality_mode == QUALITY_ULTRA)
	{
	}

	// language check
	if(strcmp(config_current.game_language_str, "English") == 0)
	{
		str_cat(example_str, "English");
	}
	else if(strcmp(config_current.game_language_str, "Russian") == 0)
	{
		str_cat(example_str, "Русский");
	}
	else if(strcmp(config_current.game_language_str, "German") == 0)
	{
		str_cat(example_str, "Hallo Freund");
	}
}

// this function start automatically
void game_startup()
{
	// set launcher window
	// check for existing game folder or create new one
	savedir_create_folder();
	wait_for(savedir_create_folder);

	// set proper path to the config file
	STRING *temp_str = "#256";
	str_cpy(temp_str, config_file_str);
	path_make_absolute(temp_str); // add 'save_dir' full path (in documents folder)

	screen_resolutions_find_all();        // find all available screen resolution (primary monitor only)
	game_load_config_from_file(temp_str); // load config from the file
	wait_for(game_load_config_from_file);

	game_apply_config(); // apply all the settings
	wait_for(game_apply_config);

	is_config_applied = true;
}

// function to test key_set
void player_toggle_map()
{
	beep();
}

// dummy player action, used to show how to use key bindings !
action player_controller()
{
	// note that to add more keybindings, you need to add them into (just make sure to do the same thing I've done with other keybindings):
	// - engine_load_config file (saving/loading keybindings to config file, also resetting to defaults)
	// - config_input (to make sure that it's visible in configuration window)
	var key_forward_scancode = keybind_return_scancode_from_letter(config_current.input_forward_str);
	var key_backward_scancode = keybind_return_scancode_from_letter(config_current.input_backward_str);
	var key_left_scancode = keybind_return_scancode_from_letter(config_current.input_left_str);
	var key_right_scancode = keybind_return_scancode_from_letter(config_current.input_right_str);
	var key_toggle_map_scancode = keybind_return_scancode_from_letter(config_current.input_toggle_map_str);

	// to make sure to use a key to call functions similar to on_ functions, I use:
	// "key_set (number, function)" where "number" is a scancode, and "function" is a pointer of function to be assigned to the given scancode
	// in order to remove previous keybinding, make sure to pass NULL instead of the function's pointer !
	key_set(key_toggle_map_scancode, NULL);              // remove previous keybinding !
	key_set(key_toggle_map_scancode, player_toggle_map); // assign new keybinding !

	VECTOR input;
	vec_fill(&input, 0);
	var key_forward = 0, key_backward = 0, key_left = 0, key_right = 0;

	while (my)
	{
		draw_text(example_str, 10, 50, COLOR_WHITE);

		// check if keys with the given scancode were pressed !
		key_forward = key_pressed(key_forward_scancode);
		key_backward = key_pressed(key_backward_scancode);
		key_left = key_pressed(key_left_scancode);
		key_right = key_pressed(key_right_scancode);

		// check for input
		input.x = (key_forward - key_backward);
		input.y = (key_left - key_right);
		input.z = 0;

		draw_text(str_printf(NULL, "input.x: %d\ninput.y: %d\n", (long)(input.x), (long)(input.y)), 10, 10, COLOR_WHITE);

		wait(1);
	}
}

void main()
{
	warn_level = 6;

	video_mode = 1;
	video_switch(video_mode, 0, 0);

	level_load("");

	// in your project make sure that all config was loaded and applied
	while(!is_config_applied){ wait(1); }

	// create dummy 'player' to test input
	ent_create(CUBE_MDL, vector(128, 0, 0), player_controller);
}