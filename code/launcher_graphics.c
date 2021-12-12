
// initialize all graphics tab config
void launcher_graphics_tab_initialize()
{
    int i = 0;
    STRING *temp_resolution = "";

    // resolution
    for (i = 0; i < screen_resolutions_total; i++)
    {
        str_cpy(temp_resolution, str_for_num(NULL, screen_resolution_available_list[SCREEN_RESOLUTION_WIDTH][i]));
        str_cat(temp_resolution, "x");
        str_cat(temp_resolution, str_for_num(NULL, screen_resolution_available_list[SCREEN_RESOLUTION_HEIGHT][i]));

        if (!launcher_graphics_resolution_available_list_str[i])
        {
            launcher_graphics_resolution_available_list_str[i] = str_create("");
            str_cpy(launcher_graphics_resolution_available_list_str[i], temp_resolution);
        }
    }

    // display modes
    for (i = 0; i < DISPLAY_MODES_MAX; i++)
    {
        if (!launcher_graphics_display_mode_list_str[i])
        {
            launcher_graphics_display_mode_list_str[i] = str_create("");
            switch (i)
            {
            case DISPLAY_MODE_WINDOWED:
                str_cpy(launcher_graphics_display_mode_list_str[i], launcher_graphics_display_windowed_str);
                break;

            case DISPLAY_MODE_WINDOWED_FULLSCREEN:
                str_cpy(launcher_graphics_display_mode_list_str[i], launcher_graphics_display_windowed_fullscreen_str);
                break;

            case DISPLAY_MODE_FULLSCREEN:
                str_cpy(launcher_graphics_display_mode_list_str[i], launcher_graphics_display_fullscreen_str);
                break;
            }
        }
    }

    // quality
    for (i = 0; i < MAX_QUALITY_OPTIONS; i++)
    {
        if (!launcher_graphics_quality_list_str[i])
        {
            launcher_graphics_quality_list_str[i] = str_create("");
            switch (i)
            {
            case QUALITY_LOW:
                str_cpy(launcher_graphics_quality_list_str[i], launcher_graphics_config_quality_low_str);
                break;

            case QUALITY_MEDIUM:
                str_cpy(launcher_graphics_quality_list_str[i], launcher_graphics_config_quality_medium_str);
                break;

            case QUALITY_HIGH:
                str_cpy(launcher_graphics_quality_list_str[i], launcher_graphics_config_quality_high_str);
                break;

            case QUALITY_ULTRA:
                str_cpy(launcher_graphics_quality_list_str[i], launcher_graphics_config_quality_ultra_str);
                break;
            }
        }
    }

    launcher_graphics_tab_refresh();
}

// refresh graphics config from the settings
void launcher_graphics_tab_refresh()
{
    int i = 0;
    STRING *temp_resolution = "";

    // resolution
    for (i = 0; i < screen_resolutions_total; i++)
    {
        str_cpy(temp_resolution, str_for_num(NULL, screen_resolution_available_list[SCREEN_RESOLUTION_WIDTH][i]));
        str_cat(temp_resolution, "x");
        str_cat(temp_resolution, str_for_num(NULL, screen_resolution_available_list[SCREEN_RESOLUTION_HEIGHT][i]));

        // updated selected one
        if (config_current.graphics_video_res_id == i)
        {
            str_cpy(launcher_graphics_resolution_currently_used_str, temp_resolution);
        }
    }

    // display modes
    for (i = 0; i < DISPLAY_MODES_MAX; i++)
    {
        // update selected one
        if (config_current.graphics_display_mode == i)
        {
            str_cpy(launcher_graphics_display_currently_used_str, launcher_graphics_display_mode_list_str[i]);
        }
    }

    // quality
    for (i = 0; i < MAX_QUALITY_OPTIONS; i++)
    {
        // update selected one
        if (config_current.graphics_quality_mode == i)
        {
            str_cpy(launcher_graphics_quality_list_current_str, launcher_graphics_quality_list_str[i]);
        }
    }
}

// create graphics tab config
void launcher_create_graphics_tab()
{
    int tab_flags = ImGuiTabBarFlags_NoCloseWithMiddleMouseButton | ImGuiTabBarFlags_NoTabListScrollingButtons | ImGuiTabBarFlags_NoTooltip;
    if (imgui_begin_tabitem(_chr(config_graphics_section_str), NULL, tab_flags))
    {
        // set proper id (used for reseting to defaults)
        launcher_selected_tab_id = TAB_GRAPHICS;

        // use desktop resolution checkbox
        if (config_current.is_desktop_res == true)
        {
            // set to fullscreen mode
            config_current.graphics_display_mode = DISPLAY_MODE_FULLSCREEN;
            str_cpy(launcher_graphics_display_currently_used_str, launcher_graphics_display_mode_list_str[DISPLAY_MODE_FULLSCREEN]);
            imgui_text(_chr(launcher_graphics_monitor_res_str));

            // set proper screen resolution id !
            str_cpy(launcher_graphics_resolution_currently_used_str, launcher_graphics_resolution_available_list_str[desktop_resolution_id]);
            config_current.graphics_video_res_id = desktop_resolution_id;

            launcher_create_tooltip(launcher_graphics_tooltip_use_desktop_res_str);
        }
        else
        {
            imgui_text_disabled(_chr(launcher_graphics_monitor_res_str));
            launcher_create_tooltip(launcher_graphics_tooltip_use_desktop_res_str);
        }
        imgui_same_line();
        imgui_align_right_with_offset(CHECKBOX_OFFSET);
        imgui_checkbox("##Use desktop resolution", &config_current.is_desktop_res);
        launcher_create_tooltip(launcher_graphics_tooltip_use_desktop_res_str);

        // not in desktop resolution ?
        // then allow tweaking everything by hand
        if (config_current.is_desktop_res == false)
        {
            // resolution part
            imgui_text(_chr(launcher_graphics_res_str));
            imgui_same_line();
            imgui_align_right_with_offset(COMBOBOX_WIDTH);
            imgui_push_item_width(COMBOBOX_WIDTH - 1);
            if (imgui_begin_combo("##Resolution Combo", _chr(launcher_graphics_resolution_currently_used_str), ImGuiComboFlags_HeightSmall))
            {
                int n = 0;
                for (n = 0; n < screen_resolutions_total; n++)
                {
                    // if in windowed mode then make sure to clip resolutions equal or higher than the desktop resolutions
                    if (config_current.graphics_display_mode == DISPLAY_MODE_WINDOWED)
                    {
                        if (n >= desktop_resolution_id)
                        {
                            continue;
                        }
                    }

                    // if in windowed fullscreen (borderless) then make sure to clip resolutions higher than the desktop resolution
                    if (config_current.graphics_display_mode == DISPLAY_MODE_WINDOWED_FULLSCREEN)
                    {
                        if (n > desktop_resolution_id)
                        {
                            continue;
                        }
                    }

                    BOOL is_selected = str_cmp(launcher_graphics_resolution_currently_used_str, launcher_graphics_resolution_available_list_str[n]);
                    if (imgui_selectable(_chr(launcher_graphics_resolution_available_list_str[n]), &is_selected, 0))
                    {
                        config_current.graphics_video_res_id = n; // currently used resolution ID
                        str_cpy(launcher_graphics_resolution_currently_used_str, launcher_graphics_resolution_available_list_str[n]);
                    }
                    if (is_selected)
                    {
                        imgui_set_item_default_focus();
                    }
                }
                imgui_end_combo();
            }
            imgui_pop_item_width();

            // display mode here
            imgui_text(_chr(launcher_graphics_display_mode_str));
            imgui_same_line();
            imgui_align_right_with_offset(COMBOBOX_WIDTH);
            imgui_push_item_width(COMBOBOX_WIDTH - 1);
            if (imgui_begin_combo("##Display mode Combo", _chr(launcher_graphics_display_currently_used_str), ImGuiComboFlags_HeightSmall))
            {
                int n = 0;
                for (n = 0; n < DISPLAY_MODES_MAX; n++)
                {
                    BOOL is_selected = str_cmp(launcher_graphics_display_currently_used_str, launcher_graphics_display_mode_list_str[n]);
                    if (imgui_selectable(_chr(launcher_graphics_display_mode_list_str[n]), &is_selected, 0))
                    {
                        config_current.graphics_display_mode = n; // currently used display mode setting
                        str_cpy(launcher_graphics_display_currently_used_str, launcher_graphics_display_mode_list_str[n]);

                        // reset screen resolution to the first one from the list
                        str_cpy(launcher_graphics_resolution_currently_used_str, launcher_graphics_resolution_available_list_str[0]);
                        config_current.graphics_video_res_id = 0;
                    }
                    if (is_selected)
                    {
                        imgui_set_item_default_focus();
                    }
                }
                imgui_end_combo();
            }
            imgui_pop_item_width();

            /*
            // if we are in window mode ?
            // then show warning message, that video resolution should be higher than desktop resolution
            if (config_current.graphics_display_mode != DISPLAY_MODE_FULLSCREEN)
            {
                imgui_push_font(launcher_graphics_tooltip_font);
                imgui_text_disabled(_chr(launcher_graphics_less_than_desktop_str));
                imgui_pop_font();
            }
            */
        }

// fps cap (only in windowed or borderless) and v-sync (only in fullscreen)
#ifdef USE_GRAPHICS_FPSCAP_N_VSYNC
        if (config_current.graphics_display_mode == DISPLAY_MODE_FULLSCREEN)
        {
            imgui_text(_chr(launcher_graphics_vsync_str));
            imgui_same_line();
            imgui_align_right_with_offset(COMBOBOX_WIDTH);
            imgui_radiobutton(_chr(launcher_graphics_vsync_double_str), &config_current.is_vsync_on, 0);
            imgui_same_line();
            imgui_radiobutton(_chr(launcher_graphics_vsync_triple_str), &config_current.is_vsync_on, 1);
        }
        else
        {
            imgui_text(_chr(launcher_graphics_fps_cap_str));
            imgui_same_line();
            imgui_align_right_with_offset(COMBOBOX_WIDTH);
            imgui_push_item_width(COMBOBOX_WIDTH - 1);
            imgui_slider_int("##FPS Cap", &config_current.graphics_fps_cap, FPS_MIN, FPS_MAX);
            imgui_pop_item_width();
        }
#endif

// quality options here
#ifdef USE_GRAPHICS_QUALITY
        imgui_text(_chr(launcher_graphics_config_quality_str));
        imgui_same_line();
        imgui_align_right_with_offset(COMBOBOX_WIDTH);
        imgui_push_item_width(COMBOBOX_WIDTH - 1);
        if (imgui_begin_combo("##Quality Combo", _chr(launcher_graphics_quality_list_current_str), ImGuiComboFlags_HeightSmall))
        {
            int n = 0;
            for (n = 0; n < MAX_QUALITY_OPTIONS; n++)
            {
                BOOL is_selected = str_cmp(launcher_graphics_quality_list_current_str, launcher_graphics_quality_list_str[n]);
                if (imgui_selectable(_chr(launcher_graphics_quality_list_str[n]), &is_selected, 0))
                {
                    config_current.graphics_quality_mode = n; // currently used quality setting
                    str_cpy(launcher_graphics_quality_list_current_str, launcher_graphics_quality_list_str[n]);
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
        imgui_end_tabitem();
        imgui_separator();
    }
}