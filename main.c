
#include <acknex.h>
#include <default.c>
#include <windows.h>
#include <strio.c>

#define PRAGMA_POINTER

#define PRAGMA_PATH "code"

// debug screen resolutions (write in acklog)
#define DEBUG_SCREEN_RESOLUTION

// enable/disable tabs
#define USE_GRAPHICS_TAB
#define USE_INPUT_TAB
#define USE_GAME_TAB

// enable/disable settings
#define USE_GRAPHICS_QUALITY

// enable/disable language, path_to_exe
#define USE_GAME_LANGUAGE
#define USE_GAME_PATH_TO_EXE

// launcher states
#define LAUNCHER_CONFIG_WINDOW 0
#define LAUNCHER_EXECUTE_GAME 1

// simple state machine for launcher
int launcher_state = LAUNCHER_CONFIG_WINDOW;
int launcher_old_state = LAUNCHER_CONFIG_WINDOW;

STRING *config_file_str = "config.ini";
STRING *project_name_str = "Unnamed_Project"; // insert your project's name here !
STRING *project_launcher_str = "";            // this will update automatically with the project name you give, by adding 'launcher' at the end

// switch launcher's state to the given one
void launcher_switch_state_to(var state)
{
    launcher_old_state = launcher_state;
    launcher_state = state;
}

#include "imgui_theme.h"
#include "imgui.h"
#include "cmd.h"
#include "engine.h"
#include "keybind.h"
#include "ini.h"
#include "screenres_list.h"
#include "config.h"
#include "savedir.h"
#include "launcher.h"
#include "launcher_graphics.h"
#include "launcher_input.h"
#include "launcher_game.h"

#include "imgui_theme.c"
#include "engine.c"
#include "keybind.c"
#include "screenres_list.c"
#include "config.c"
#include "savedir.c"
#include "launcher.c"
#include "launcher_graphics.c"
#include "launcher_input.c"
#include "launcher_game.c"

// main startup function
// it get's executed automatically on engine start
void launcher_startup()
{
    // launcher's name in the window
    str_cpy(project_launcher_str, project_name_str);
    str_cat(project_launcher_str, "'s Launcher");

    // set launcher window
    // check for existing game folder or create new one
    savedir_create_folder();
    wait_for(savedir_create_folder);

    // set proper path to the config file
    STRING *temp_str = "#256";
    str_cpy(temp_str, config_file_str);
    path_make_absolute(temp_str); // add 'save_dir' full path (in documents folder)

    screen_resolutions_find_all(); // find all available screen resolution (primary monitor only)
    config_initialize(temp_str);   // initialize config (set defaults and load from the config file)
    launcher_initialize(temp_str); // initialize launcher's gui
    engine_initialize();           // initialize engine settings
}

// main loop function
void on_frame_event()
{
    switch (launcher_state)
    {
    case LAUNCHER_CONFIG_WINDOW:
        launcher_update();
        break;

    case LAUNCHER_EXECUTE_GAME:
        if (!config_save_n_execute())
        {
            launcher_show_wrong_path_to_game_warning();
            launcher_switch_state_to(LAUNCHER_CONFIG_WINDOW);
        }
        else
        {
            sys_exit(NULL);
        }
        break;
    }
}

// function triggered when esc is pressed
void on_esc_event()
{
    // if we are in the input binding state, ignore escape key events
    // same thing for wrong path warning message
    if (is_launcher_input_popup_modal_on == true || is_launcher_has_wrong_path_popup_modal_on == true)
    {
        return;
    }

    //sys_exit(NULL);
}

// main function
void main()
{
    warn_level = 6;

    video_mode = 1;
    video_switch(video_mode, 0, 0);

    on_d3d_lost = imgui_reset;
    on_scanmessage = custom_scan_message;
    on_frame = on_frame_event;
    on_esc = on_esc_event;

    // without this imgui will cause bug with mouse pointer
    // background of the mouse map will be visible...
    // and debug panel will be messed up too
    level_load("");

    // grey background instead of poisonous blue...
    vec_set(&sky_color.blue, COLOR_GREY);
}