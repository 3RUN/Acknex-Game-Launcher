
// initialize config into the given file
void config_initialize(STRING *config_file)
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

    // default game settings
    strcpy(config_default.game_language_str, _chr(game_def_language_str));

    // set default path to the working directory + project's name with .exe at the end
    str_cpy(game_def_path_to_exe_str, work_dir);
    str_cat(game_def_path_to_exe_str, project_name_str);
    str_cat(game_def_path_to_exe_str, ".exe");
    strcpy(config_default.game_path_to_exe_str, _chr(game_def_path_to_exe_str));

    // load/write config
    config_load_from_file(config_file);
}

// save config
var config_save_n_execute()
{
    memcpy(&config_saved, &config_current, sizeof(CONFIG));

    // set proper path to the config file
    STRING *temp_str = "#256";
    str_cpy(temp_str, config_file_str);
    path_make_absolute(temp_str);  // add 'save_dir' full path (in documents folder)
    config_save_to_file(temp_str); // save all settings back to the config file

    // execute
    // but only if file exists !
    if (file_exists(config_current.game_path_to_exe_str))
    {
        return exec(config_current.game_path_to_exe_str, NULL);
    }
    else
    {
        return false;
    }
}

// reset config to defaults
void config_reset_to_default()
{
    if (launcher_selected_tab_id == TAB_GRAPHICS)
    {
        config_current.is_desktop_res = config_default.is_desktop_res;
        config_current.graphics_video_res_id = config_default.graphics_video_res_id;
        config_current.graphics_display_mode = config_default.graphics_display_mode;
        config_current.graphics_quality_mode = config_default.graphics_quality_mode;
        config_current.graphics_fps_cap = config_default.graphics_fps_cap;
    }
    else if (launcher_selected_tab_id == TAB_INPUT)
    {
        strcpy(config_current.input_forward_str, config_default.input_forward_str);
        strcpy(config_current.input_backward_str, config_default.input_backward_str);
        strcpy(config_current.input_left_str, config_default.input_left_str);
        strcpy(config_current.input_right_str, config_default.input_right_str);
        strcpy(config_current.input_toggle_map_str, config_default.input_toggle_map_str);
    }
    else if (launcher_selected_tab_id == TAB_GAME)
    {
        strcpy(config_current.game_language_str, config_default.game_language_str);
        strcpy(config_current.game_path_to_exe_str, config_default.game_path_to_exe_str);
    }

    // memcpy(&config_current, &config_default, sizeof(CONFIG));
    memcpy(&config_saved, &config_default, sizeof(CONFIG));
}

// load config from the file
void config_load_from_file(STRING *config_file)
{
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
    ini_read_write_var(&config_current.graphics_fps_cap, config_file, config_graphics_section_str, graphics_fps_cap_entry_str, config_default.graphics_fps_cap);

    // game
    ini_read_write_char(config_current.game_language_str, config_file, config_game_section_str, game_language_entry_str, config_default.game_language_str);
    ini_read_write_char(config_current.game_path_to_exe_str, config_file, config_game_section_str, game_path_to_exe_entry_str, config_default.game_path_to_exe_str);
}

// save config into the given file
void config_save_to_file(STRING *config_file)
{
    // input
    ini_write(config_file, config_input_section_str, input_forward_entry_str, config_current.input_forward_str);
    ini_write(config_file, config_input_section_str, input_backward_entry_str, config_current.input_backward_str);
    ini_write(config_file, config_input_section_str, input_left_entry_str, config_current.input_left_str);
    ini_write(config_file, config_input_section_str, input_right_entry_str, config_current.input_right_str);
    ini_write(config_file, config_input_section_str, input_toggle_map_entry_str, config_current.input_toggle_map_str);

    // graphics
    ini_write_int(config_file, config_graphics_section_str, graphics_is_desktop_entry_str, config_current.is_desktop_res);
    ini_write_int(config_file, config_graphics_section_str, graphics_video_res_id_entry_str, config_current.graphics_video_res_id);
    ini_write_int(config_file, config_graphics_section_str, graphics_display_mode_entry_str, config_current.graphics_display_mode);
    ini_write_int(config_file, config_graphics_section_str, graphics_quality_mode_entry_str, config_current.graphics_quality_mode);
    ini_write_var(config_file, config_graphics_section_str, graphics_fps_cap_entry_str, config_current.graphics_fps_cap);

    // game
    ini_write(config_file, config_game_section_str, game_language_entry_str, config_current.game_language_str);
    ini_write(config_file, config_game_section_str, game_path_to_exe_entry_str, config_current.game_path_to_exe_str);
}