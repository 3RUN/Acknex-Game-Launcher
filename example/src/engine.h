#ifndef _ENGINE_H_
#define _ENGINE_H_

// mouse bmap
BMAP *mouse_tga = "mouse.tga";

// other settings
int autolock_mouse_locked = false; // true - when mouse is locked, otherwise - false

// initialize the engine
void engine_initialize();

// lock mouse inside of the game window
void engine_mouse_lock_in_window();

// set mouse cursor at the given screen position (from the upper left corner)
void engine_mouse_set_position(VECTOR *pos);

// return mouse position
void engine_mouse_get_position(VECTOR *out);

// enable the mouse
void engine_mouse_enable(int is_mouse_centered);

// disable the mouse
void engine_mouse_disable();

// same as above, but resolution is taken from the list by it's id
void engine_set_resolution_from_id(int id, int display_mode);

#endif