#ifndef _LAUNCHER_GRAPHICS_H_
#define _LAUNCHER_GRAPHICS_H_

// fps limits
#define FPS_MIN 30
#define FPS_MAX 512

// tooltips
STRING *launcher_graphics_tooltip_use_desktop_res_str = "Run the game in fullscreen mode with desktop resolution";

// resolution config
STRING *launcher_graphics_resolution_available_list_str[SCREEN_RESOLUTION_MAX]; // list of screen resolutions
STRING *launcher_graphics_resolution_currently_used_str = "None";               // currently set screen resolution
STRING *launcher_graphics_monitor_res_str = "Use desktop resolution of a primary monitor (fullscreen)";
STRING *launcher_graphics_less_than_desktop_str = "NOTE: Video resolution in \"Windowed\" mode should be less or equal to desktop resolution!";
STRING *launcher_graphics_res_str = "Resolution";

// display mode config
STRING *launcher_graphics_display_mode_list_str[DISPLAY_MODES_MAX]; // list of available display modes (windowed, windowed fullscreen, fullscreen)
STRING *launcher_graphics_display_currently_used_str = "None";      // currently set display mode
STRING *launcher_graphics_display_mode_str = "Display mode";
STRING *launcher_graphics_display_windowed_str = "Windowed";
STRING *launcher_graphics_display_windowed_fullscreen_str = "Borderless";
STRING *launcher_graphics_display_fullscreen_str = "Fullscreen";

// quality config
STRING *launcher_graphics_quality_list_str[MAX_QUALITY_OPTIONS];
STRING *launcher_graphics_quality_list_current_str = "None";
STRING *launcher_graphics_config_quality_str = "Quality";
STRING *launcher_graphics_config_quality_low_str = "Low";
STRING *launcher_graphics_config_quality_medium_str = "Medium";
STRING *launcher_graphics_config_quality_high_str = "High";
STRING *launcher_graphics_config_quality_ultra_str = "Ultra";

// fps cap and v-sync
STRING *launcher_graphics_fps_cap_str = "FPS Cap";
STRING *launcher_graphics_vsync_str = "V-Sync";
STRING *launcher_graphics_vsync_double_str = "Double buffering";
STRING *launcher_graphics_vsync_triple_str = "Triple buffering";

// initialize all graphics tab config
void launcher_graphics_tab_initialize();

// refresh graphics config from the settings
void launcher_graphics_tab_refresh();

// create graphics tab config
void launcher_create_graphics_tab();

#endif