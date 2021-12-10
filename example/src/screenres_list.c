
// sort list of resolutions in ascending order
void screen_resolutions_sort_ascending()
{
    int i = 0, j = 0;

    for (i = 0; i < screen_resolutions_total; ++i)
    {
        for (j = i + 1; j < screen_resolutions_total; ++j)
        {
            if (screen_resolution_available_list[SCREEN_RESOLUTION_WIDTH][i] > screen_resolution_available_list[SCREEN_RESOLUTION_WIDTH][j])
            {
                int width = screen_resolution_available_list[SCREEN_RESOLUTION_WIDTH][i];
                int height = screen_resolution_available_list[SCREEN_RESOLUTION_HEIGHT][i];

                screen_resolution_available_list[SCREEN_RESOLUTION_WIDTH][i] = screen_resolution_available_list[SCREEN_RESOLUTION_WIDTH][j];
                screen_resolution_available_list[SCREEN_RESOLUTION_HEIGHT][i] = screen_resolution_available_list[SCREEN_RESOLUTION_HEIGHT][j];

                screen_resolution_available_list[SCREEN_RESOLUTION_WIDTH][j] = width;
                screen_resolution_available_list[SCREEN_RESOLUTION_HEIGHT][j] = height;
            }
        }
    }
}

// check if given resolution was already added into the list or not
int is_screen_resolution_added(int width, int height)
{
    int i = 0;
    for (i = 0; i < screen_resolutions_total; i++)
    {
        if (screen_resolution_available_list[SCREEN_RESOLUTION_WIDTH][i] == width && screen_resolution_available_list[SCREEN_RESOLUTION_HEIGHT][i] == height)
        {
            return true;
        }
    }

    return false;
}

// add given resolution into the list
void screen_resolution_add_to_list(int width, int height)
{
    screen_resolution_available_list[SCREEN_RESOLUTION_WIDTH][screen_resolutions_total] = width;
    screen_resolution_available_list[SCREEN_RESOLUTION_HEIGHT][screen_resolutions_total] = height;
    screen_resolutions_total++;
}

// find all available resolutions
void screen_resolutions_find_all()
{
    // find desktop resolution
    desktop_size_x = sys_metrics(SM_CXSCREEN);
    desktop_size_y = sys_metrics(SM_CYSCREEN);

    int i = 0;
    screen_resolution_struct.dmSize = sizeof(SCRMODE);
    for (i = 1; EnumDisplaySettings(NULL, i, &screen_resolution_struct) != 0; ++i)
    {
        int width = screen_resolution_struct.dmPelsWidth;
        int height = screen_resolution_struct.dmPelsHeight;

        if (width < SCREEN_RESOLUTION_MIN_X || height < SCREEN_RESOLUTION_MIN_Y)
        {
            continue;
        }

        if (is_screen_resolution_added(width, height) == 0)
        {
            screen_resolution_add_to_list(width, height);
        }
    }

    screen_resolutions_sort_ascending();

    // find id of the desktop resolution
    for (i = 0; i < screen_resolutions_total; i++)
    {
        int width = screen_resolution_available_list[SCREEN_RESOLUTION_WIDTH][i];
        int height = screen_resolution_available_list[SCREEN_RESOLUTION_HEIGHT][i];
        if (desktop_size_x == width && desktop_size_y == height)
        {
            desktop_resolution_id = i;
        }
    }

#ifdef DEBUG_SCREEN_RESOLUTION
    diag("\n\nPrimary monitor resolutions:\n");
    for (i = 0; i < screen_resolutions_total; i++)
    {
        STRING *temp_str = "";
        str_cpy(temp_str, str_for_num(NULL, screen_resolution_available_list[SCREEN_RESOLUTION_WIDTH][i]));
        str_cat(temp_str, "x");
        str_cat(temp_str, str_for_num(NULL, screen_resolution_available_list[SCREEN_RESOLUTION_HEIGHT][i]));
        diag(temp_str);
        diag("\n");
    }
#endif
}