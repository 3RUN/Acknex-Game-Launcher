
// create launcher window
void launcher_create_window(int width, int height)
{
    var propX = camera->size_x / screen_size.x;
    var propY = camera->size_y / screen_size.y;

    video_set(width, height, 0, 2);

    screen_size.x = width;
    screen_size.y = height;

    camera->pos_x = floor(camera->pos_x * propX);
    camera->pos_y = floor(camera->pos_y * propY);
    camera->size_x = floor(screen_size.x * propX);
    camera->size_y = floor(screen_size.y * propY);

    video_window(NULL, NULL, 16 + 32 + 64, project_launcher_str);
}

// create tooltip with the given string
void launcher_create_tooltip(STRING *str)
{
    if (imgui_is_item_hovered())
    {
        imgui_set_tooltip(_chr(str));
        imgui_begin_tooltip();
        imgui_end_tooltip();
    }
}

// initialize launcher's gui
void launcher_initialize(STRING *config_file)
{
    // create launcher window
    launcher_create_window(LAUNCHER_WINDOW_WIDTH, LAUNCHER_WINDOW_HEIGHT);

    // initialize imgui
    imgui_init(0);
    imgui_change_theme();

    // create launcher fonts
    launcher_font = imgui_add_ttf_from_file("c:\\Windows\\Fonts\\Arial.ttf", 20, GLYPH_RANGE_Default);
    launcher_graphics_tooltip_font = imgui_add_ttf_from_file("c:\\Windows\\Fonts\\Arial.ttf", 16, GLYPH_RANGE_Default);
    launcher_input_font = imgui_add_ttf_from_file("c:\\Windows\\Fonts\\Arial.ttf", 18, GLYPH_RANGE_Default);

    // other launcher stuff
    launcher_graphics_tab_initialize();
    launcher_game_tab_initialize();
}

// show warning message when game's .exe doesn't exist or not found
void launcher_show_wrong_path_to_game_warning()
{
    is_launcher_has_wrong_path_popup_modal_on = true;

    while (!key_any)
    {
        wait(1);
    }

    is_launcher_has_wrong_path_popup_closing = true;
}

// update launcher
void launcher_update()
{
    imgui_start_imode();

    imgui_set_next_window_pos(0, 0, ImGuiCond_Always);
    imgui_set_next_window_size(LAUNCHER_WINDOW_WIDTH, LAUNCHER_WINDOW_HEIGHT, ImGuiCond_Always);
    int launcher_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings;
    imgui_begin("##Launcher Menu", NULL, launcher_flags);

    imgui_push_font(launcher_font);
    int launcher_tabs_flags = ImGuiTabBarFlags_NoCloseWithMiddleMouseButton | ImGuiTabBarFlags_NoTabListScrollingButtons | ImGuiTabBarFlags_NoTooltip;
    imgui_begin_tabbar("##Launcher Tabs", launcher_tabs_flags);

// tabs here
#ifdef USE_GRAPHICS_TAB
    launcher_create_graphics_tab();
#endif

#ifdef USE_INPUT_TAB
    launcher_create_input_tab();
#endif

#ifdef USE_GAME_TAB
    launcher_create_game_tab();
#endif

    imgui_end_tabbar();

    // place 3 buttons at the lower edge of the window
    imgui_align_bottom_with_offset(BUTTON_HEIGHT);

    // reset to defaults button
    if (imgui_button_withsize(_chr(launcher_reset_to_def_str), BUTTON_WIDTH * 2, 32))
    {
        config_reset_to_default();
        launcher_graphics_tab_refresh();
        launcher_game_tab_refresh();
    }

    imgui_same_line();
    imgui_align_right_with_offset(BUTTON_WIDTH * 2 + engine_theme_item_spacing[1]);

    // play button
    if (imgui_button_withsize(_chr(launcher_launch_game_str), BUTTON_WIDTH, 32))
    {
        launcher_switch_state_to(LAUNCHER_EXECUTE_GAME);
    }

    imgui_same_line();

    // quit button
    if (imgui_button_withsize(_chr(launcher_quit_game_str), BUTTON_WIDTH, 32))
    {
        sys_exit(NULL);
    }

    imgui_pop_font();
    imgui_end();

    // modal popup to change the input !
    if (is_launcher_has_wrong_path_popup_modal_on == true)
    {
        imgui_open_popup("##Wrong Path Modal");
        is_launcher_has_wrong_path_popup_modal_on = false;
    }

    int wrong_path_modal_flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize;
    if (imgui_begin_popup_modals_params("##Wrong Path Modal", NULL, wrong_path_modal_flags))
    {
        if (is_launcher_has_wrong_path_popup_closing == true)
        {
            imgui_close_current_popup();
            is_launcher_has_wrong_path_popup_closing = false;
        }

        imgui_text(_chr(launcher_wrong_path_str));
        imgui_end_popup();
    }

    imgui_end_imode();
}