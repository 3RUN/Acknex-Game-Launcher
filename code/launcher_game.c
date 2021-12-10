
// initialize all game tab config
void launcher_game_tab_initialize()
{
    int i = 0;
    for (i = 0; i < GAME_LANGUAGE_MAX; i++)
    {
        if (!launcher_game_language_list_str[i])
        {
            launcher_game_language_list_str[i] = str_create("");

            switch (i)
            {
            case GAME_LANGUAGE_ENGLISH:
                str_cpy(launcher_game_language_list_str[i], launcher_game_language_english_str);
                break;

            case GAME_LANGUAGE_RUSSIAN:
                str_cpy(launcher_game_language_list_str[i], launcher_game_language_russian_str);
                break;

            case GAME_LANGUAGE_GERMAN:
                str_cpy(launcher_game_language_list_str[i], launcher_game_language_german_str);
                break;
            }
        }
    }

    launcher_game_tab_refresh();
}

// refresh game config from the settings
void launcher_game_tab_refresh()
{
    int i = 0;
    for (i = 0; i < GAME_LANGUAGE_MAX; i++)
    {
        if (strcmp(config_current.game_language_str, _chr(launcher_game_language_list_str[i])))
        {
            str_cpy(launcher_game_language_used_str, _str(config_current.game_language_str));
        }
    }
}

// create game tab config
void launcher_create_game_tab()
{
    int tab_flags = ImGuiTabBarFlags_NoCloseWithMiddleMouseButton | ImGuiTabBarFlags_NoTabListScrollingButtons | ImGuiTabBarFlags_NoTooltip;
    if (imgui_begin_tabitem(_chr(config_game_section_str), NULL, tab_flags))
    {
        // set proper id (used for reseting to defaults)
        launcher_selected_tab_id = TAB_GAME;

// language part
#ifdef USE_GAME_LANGUAGE
        imgui_text(_chr(game_language_entry_str));
        imgui_same_line();
        imgui_align_right_with_offset(COMBOBOX_WIDTH);
        imgui_push_item_width(COMBOBOX_WIDTH - 1);
        if (imgui_begin_combo("##Language Combo", _chr(launcher_game_language_used_str), ImGuiComboFlags_HeightSmall))
        {
            int n = 0;
            for (n = 0; n < GAME_LANGUAGE_MAX; n++)
            {
                BOOL is_selected = str_cmp(launcher_game_language_used_str, launcher_game_language_list_str[n]);
                if (imgui_selectable(_chr(launcher_game_language_list_str[n]), &is_selected, 0))
                {
                    str_cpy(launcher_game_language_used_str, launcher_game_language_list_str[n]);
                    strcpy(config_current.game_language_str, _chr(launcher_game_language_used_str));
                }
                if (is_selected)
                {
                    imgui_set_item_default_focus();
                }
            }
            imgui_end_combo();
        }
        imgui_pop_item_width();
#endif

// path to the game part
#ifdef USE_GAME_PATH_TO_EXE
        imgui_text(_chr(game_path_to_exe_entry_str));
        imgui_same_line();

        VECTOR pos;
        vec_set(&pos, imgui_get_cursor_screen_pos());
        var offset_width = imgui_get_content_region_avail_width() - COMBOBOX_WIDTH;
        imgui_set_cursor_screen_pos(vector(pos.x + offset_width, pos.y, pos.z));
        int len = strlen(config_current.game_path_to_exe_str);

        imgui_push_item_width(COMBOBOX_WIDTH - BUTTON_WIDTH - engine_theme_item_spacing[0]);
        imgui_input_text("##Textbox", config_current.game_path_to_exe_str, len, ImGuiInputTextFlags_ReadOnly | ImGuiInputTextFlags_AutoSelectAll);
        imgui_pop_item_width();

        imgui_same_line();
        if (imgui_button_withsize(_chr(game_browse_button_str), BROWSE_BUTTON_WIDTH, BROWSE_BUTTON_HEIGHT))
        {
            char *temp_path_str = file_dialog_open(NULL, "*.exe");
            if (temp_path_str)
            {
                strcpy(config_current.game_path_to_exe_str, temp_path_str);
            }
        }
#endif

        imgui_end_tabitem();
        imgui_separator();
    }
}