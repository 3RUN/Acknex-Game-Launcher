#ifndef _LAUNCHER_GAME_H_
#define _LAUNCHER_GAME_H_

// game config
STRING *launcher_game_language_list_str[GAME_LANGUAGE_MAX];
STRING *launcher_game_language_used_str = "None";
STRING *launcher_game_language_english_str = "English";
STRING *launcher_game_language_russian_str = "Russian";
STRING *launcher_game_language_german_str = "German";

// initialize all game tab config
void launcher_game_tab_initialize();

// refresh game config from the settings
void launcher_game_tab_refresh();

// create game tab config
void launcher_create_game_tab();

#endif