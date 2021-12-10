
// initialize the engine
void engine_initialize()
{
	engine_mouse_enable(true); // enable mouse and center it in the game window's center
}

// lock mouse inside of the game window
void engine_mouse_lock_in_window()
{
	if (window_focus)
	{
		if (autolock_mouse_locked == false)
		{
			RECT rect;
			rect.top = 0;
			rect.bottom = screen_size.y;
			rect.left = 0;
			rect.right = screen_size.x;

			ClientToScreen(hWnd, &rect);
			ClientToScreen(hWnd, &rect.right);
			ClipCursor(&rect);

			engine_mouse_set_position(vector(screen_size.x - 64, screen_size.y - 64, 0));
			autolock_mouse_locked = true;
		}
	}
	else
	{
		if (autolock_mouse_locked == true)
		{
			ClipCursor(NULL);
			autolock_mouse_locked = false;
		}
	}
}

// set mouse cursor at the given screen position (from the upper left corner)
void engine_mouse_set_position(VECTOR *pos)
{
	VECTOR offset;
	vec_set(&offset, pos);
	RECT rect;
	GetClientRect(hWnd, &rect);
	ClientToScreen(hWnd, &rect);
	ClientToScreen(hWnd, &rect.right);
	SetCursorPos(rect.left + offset.x, rect.top + offset.y);
}

// return mouse position
VECTOR *engine_mouse_get_position()
{
	POINT cp;
	GetCursorPos(&cp);
	VECTOR pos;
	vec_set(&pos, vector(cp.x, cp.y, 0));
	return &pos;
}

// enable the mouse
void engine_mouse_enable(int is_mouse_centered)
{
	if (mouse_mode != 4)
	{
		mouse_sync = 0;
		mouse_mode = 4;
		mouse_map = mouse_tga;
		mouse_pointer = 1;

		if (is_mouse_centered == true)
		{
			engine_mouse_set_position(vector(screen_size.x / 2, screen_size.y / 2, 0));
		}
	}
}

// disable the mouse
void engine_mouse_disable()
{
	if (mouse_mode != 0)
	{
		mouse_sync = 0;
		mouse_mode = 0;
		mouse_map = NULL;
		mouse_pointer = 0;
	}
}

// same as above, but resolution is taken from the list by it's id
void engine_set_resolution_from_id(int id, int display_mode)
{
	// cycle the id and keep in the range
	id = cycle(id, 0, screen_resolutions_total);

	var prop_x = camera->size_x / screen_size.x;
	var prop_y = camera->size_y / screen_size.y;

	int width = screen_resolution_available_list[SCREEN_RESOLUTION_WIDTH][id];
	int height = screen_resolution_available_list[SCREEN_RESOLUTION_HEIGHT][id];

	// because on some computers screen_size doesn't get updated by itself...
	screen_size.x = width;
	screen_size.y = height;

	camera->pos_x = floor(camera->pos_x * prop_x);
	camera->pos_y = floor(camera->pos_y * prop_y);
	camera->size_x = floor(screen_size.x * prop_x);
	camera->size_y = floor(screen_size.y * prop_y);

	// windowed or fullscreen
	if (display_mode == DISPLAY_MODE_WINDOWED)
	{
		video_window(NULL, NULL, 16 + 32, project_name_str);
	}
	
	if (video_set(width, height, 0, 0) == 0)
	{
		engine_set_resolution_from_id(id - 1, display_mode);
		diag("\nERROR in engine_set_resolution_from_id! Can't set to selected resolution... Lowering resolution!");
		return;
	}
	
	// fullscreen boarderless windows
	if (display_mode == DISPLAY_MODE_WINDOWED_FULLSCREEN)
	{
		video_window(vector(0.001, 0.001, 0), vector(desktop_size_x, desktop_size_y, 0), 1, project_name_str);
	}

	wait(1);

	int is_fullscreen = false;
	if (display_mode == DISPLAY_MODE_FULLSCREEN)
	{
		is_fullscreen = true;
	}

	video_set(0, 0, 0, (2 - is_fullscreen));
}