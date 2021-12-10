
// helper function to check for input setting
void launcher_input_check_overwrite(STRING *bindkey)
{
    if (strcmp(config_current.input_forward_str, _chr(bindkey)) == 0)
    {
        strcpy(config_current.input_forward_str, _chr(input_none_str));
    }
    if (strcmp(config_current.input_backward_str, _chr(bindkey)) == 0)
    {
        strcpy(config_current.input_backward_str, _chr(input_none_str));
    }
    if (strcmp(config_current.input_left_str, _chr(bindkey)) == 0)
    {
        strcpy(config_current.input_left_str, _chr(input_none_str));
    }
    if (strcmp(config_current.input_right_str, _chr(bindkey)) == 0)
    {
        strcpy(config_current.input_right_str, _chr(input_none_str));
    }
    if (strcmp(config_current.input_toggle_map_str, _chr(bindkey)) == 0)
    {
        strcpy(config_current.input_toggle_map_str, _chr(input_none_str));
    }
}

// set input key to the selected action
void launcher_input_bind_new_key(STRING *entry, STRING *bindkey)
{
    // check if given key is already in use, and if yes
    // then remove it !
    launcher_input_check_overwrite(bindkey);
    wait_for(launcher_input_check_overwrite);

    // assign the key
    if (str_cmp(entry, input_forward_entry_str))
    {
        strcpy(config_current.input_forward_str, _chr(bindkey));
    }
    else if (str_cmp(entry, input_backward_entry_str))
    {
        strcpy(config_current.input_backward_str, _chr(bindkey));
    }
    else if (str_cmp(entry, input_left_entry_str))
    {
        strcpy(config_current.input_left_str, _chr(bindkey));
    }
    else if (str_cmp(entry, input_right_entry_str))
    {
        strcpy(config_current.input_right_str, _chr(bindkey));
    }
    else if (str_cmp(entry, input_toggle_map_entry_str))
    {
        strcpy(config_current.input_toggle_map_str, _chr(bindkey));
    }
}

// remove binding for the given input
void launcher_input_remove_bind_key(STRING *entry)
{
    if (str_cmp(entry, input_forward_entry_str))
    {
        strcpy(config_current.input_forward_str, _chr(input_none_str));
    }
    else if (str_cmp(entry, input_backward_entry_str))
    {
        strcpy(config_current.input_backward_str, _chr(input_none_str));
    }
    else if (str_cmp(entry, input_left_entry_str))
    {
        strcpy(config_current.input_left_str, _chr(input_none_str));
    }
    else if (str_cmp(entry, input_right_entry_str))
    {
        strcpy(config_current.input_right_str, _chr(input_none_str));
    }
    else if (str_cmp(entry, input_toggle_map_entry_str))
    {
        strcpy(config_current.input_toggle_map_str, _chr(input_none_str));
    }
}

// wait for input from user to bind a new key
void launcher_input_wait_for_binding(STRING *entry)
{
    imgui_open_popup("##Input Modal");

    // wait untill we 'unpress' all keys
    while (key_any)
    {
        wait(1);
    }

    var cooldown_time = 0.1;
    while (cooldown_time > 0)
    {
        cooldown_time -= time_frame / 16;
        wait(1);
    }

    int wait_for_input = true;

    while (wait_for_input == true)
    {
        if (key_lastpressed == 1) // pressed escape ?
        {
            wait_for_input = false;
        }

        if (key_lastpressed == 83) // pressed delete ?
        {
            launcher_input_remove_bind_key(entry);
            wait_for_input = false;
        }

        if (key_any == true)
        {
            // check for the key's not being esc or delete
            // also (sorry...) we don't support joystick buttons...
            if (key_lastpressed != 1 && key_lastpressed != 83 && key_lastpressed < 256 || key_lastpressed != 1 && key_lastpressed != 83 && key_lastpressed > 279)
            {
                launcher_input_bind_new_key(entry, keybind_return_letter_from_scancode(key_lastpressed));
                wait_for_input = false;
            }
        }
        wait(1);
    }

    is_launcher_input_popup_closing = true;
}

// add keybinding button
void launcher_input_add_keybinding(STRING *entry, STRING *input)
{
    imgui_text(_chr(entry));
    imgui_same_line();
    imgui_align_right_with_offset(INPUT_BOTTON_WIDTH);

    // fixed button label (id)
    STRING *id_str = "";
    str_cpy(id_str, input);
    str_cat(id_str, "##");
    str_cat(id_str, entry);

    if (imgui_button_withsize(_chr(id_str), INPUT_BOTTON_WIDTH, INPUT_BUTTON_HEIGHT))
    {
        launcher_input_wait_for_binding(entry);
    }
    imgui_separator();
}

// create input tab config
void launcher_create_input_tab()
{
    int tab_flags = ImGuiTabBarFlags_NoCloseWithMiddleMouseButton | ImGuiTabBarFlags_NoTabListScrollingButtons | ImGuiTabBarFlags_NoTooltip;
    if (imgui_begin_tabitem(_chr(config_input_section_str), NULL, tab_flags))
    {
        // set proper id (used for reseting to defaults)
        launcher_selected_tab_id = TAB_INPUT;

        imgui_push_font(launcher_input_font);

        // make sure 'Command' word is at the center of commands list (txt)
        VECTOR pos;
        vec_set(&pos, imgui_get_cursor_screen_pos());
        var available_width = imgui_get_content_region_avail_width();
        var offset_width = (available_width - engine_theme_scrollbar_size - engine_theme_win_padding[0] - INPUT_BOTTON_WIDTH - str_width(launcher_input_help_command_str, NULL)) / 2;
        imgui_set_cursor_screen_pos(vector(pos.x + offset_width, pos.y, pos.z));
        imgui_text(_chr(launcher_input_help_command_str));

        // make sure 'Key' word is at the center of the keybinding buttons
        imgui_same_line();
        offset_width = ((INPUT_BOTTON_WIDTH / 2) + (str_width(launcher_input_help_key_str, NULL) / 2)) + engine_theme_win_padding[0] + engine_theme_scrollbar_size;
        imgui_align_right_with_offset(offset_width);
        imgui_text(_chr(launcher_input_help_key_str));

        VECTOR pos;
        vec_set(&pos, imgui_get_cursor_screen_pos());
        var input_child_height = LAUNCHER_WINDOW_HEIGHT - (pos.y + BUTTON_HEIGHT + engine_theme_win_padding[1] * 2);
        int input_child_flags = ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings;
        imgui_begin_child("##Input Child", vector(-1, input_child_height, 0), 1, input_child_flags);

        // modal popup to change the input !
        int input_modal_flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize;
        is_launcher_input_popup_modal_on = imgui_begin_popup_modals_params("##Input Modal", NULL, input_modal_flags);

        if (is_launcher_input_popup_modal_on == true)
        {
            if (is_launcher_input_popup_closing == true)
            {
                imgui_close_current_popup();
                is_launcher_input_popup_closing = false;
            }

            imgui_text(_chr(launcher_input_bind_str));
            imgui_end_popup();
        }

        // input keys here
        // we could use array of chars in the config structure
        // and that way it would be easier to manipulate key binding/removing
        // but it would be less 'readable' code in my oppinion
        // so I'd decided to leave it as it is
        launcher_input_add_keybinding(input_forward_entry_str, config_current.input_forward_str);
        launcher_input_add_keybinding(input_backward_entry_str, config_current.input_backward_str);
        launcher_input_add_keybinding(input_left_entry_str, config_current.input_left_str);
        launcher_input_add_keybinding(input_right_entry_str, config_current.input_right_str);
        launcher_input_add_keybinding(input_toggle_map_entry_str, config_current.input_toggle_map_str);

        imgui_end_child();
        imgui_pop_font();
        imgui_end_tabitem();
    }
}