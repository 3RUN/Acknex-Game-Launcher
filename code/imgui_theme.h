#ifndef _IMGUI_THEME_H_
#define _IMGUI_THEME_H_

// style parameters
var engine_theme_win_padding[2] = {8, 8};
var engine_theme_win_rounding = 0;
var engine_theme_win_bordersize = 2;
var engine_theme_win_minsize[2] = {16, 16};
var engine_theme_win_title_alignment[2] = {0.5, 0.5};
var engine_theme_child_rounding = 0;
var engine_theme_child_bordersize = 2;
var engine_theme_popup_rounding = 0;
var engine_theme_popup_bordersize = 2;
var engine_theme_frame_padding[2] = {2, 2};
var engine_theme_frame_rounding = 0;
var engine_theme_frame_bordersize = 0; // anything more than 0 causes a slider grab centration bug (on Y)
var engine_theme_item_spacing[2] = {4, 4};
var engine_theme_item_inner_spacing[2] = {4, 4};
var engine_theme_indent_spacing = 4;
var engine_theme_scrollbar_size = 20;
var engine_theme_scrollbar_rounding = 0;
var engine_theme_grab_minsize = 20;
var engine_theme_grab_rounding = 0;
var engine_theme_tab_rounding = 0;
var engine_theme_button_textalign[2] = {0.5, 0.5};
var engine_theme_selectable_textalign[2] = {0.5, 0.5};

// theme colors
COLOR4* imgui_theme_bg_color = { red = 33; green = 33; blue = 33; alpha = 255; }
COLOR4* imgui_theme_light_bg_color = { red = 66; green = 66; blue = 66; alpha = 255; }
COLOR4* imgui_theme_very_light_bg_color = { red = 99; green = 99; blue = 99; alpha = 255; }

COLOR4* imgui_theme_panel_color = { red = 51; green = 51; blue = 51; alpha = 255; }
COLOR4* imgui_theme_panel_hover_color = { red = 20; green = 151; blue = 236; alpha = 255; }
COLOR4* imgui_theme_panel_active_color = { red = 0; green = 119; blue = 200; alpha = 255; }

COLOR4* imgui_theme_text_color = { red = 255; green = 255; blue = 255; alpha = 255; }
COLOR4* imgui_theme_text_disabled_color = { red = 151; green = 151; blue = 151; alpha = 255; }
COLOR4* imgui_theme_border_color = { red = 78; green = 78; blue = 78; alpha = 255; }

// simple colors
COLOR4* color4_image = { red = 1; green = 1; blue = 1; alpha = 100; }
COLOR4* color4_clear = { red = 0; green = 0; blue = 0; alpha = 0; }
COLOR4* color4_black = { red = 0; green = 0; blue = 0; alpha = 255; }
COLOR4* color4_white = { red = 255; green = 255; blue = 255; alpha = 255; }
COLOR4* color4_gray = { red = 80; green = 80; blue = 80; alpha = 255; }
COLOR4* color4_grey = { red = 80; green = 80; blue = 80; alpha = 255; }
COLOR4* color4_red = { red = 255; green = 0; blue = 0; alpha = 255; }
COLOR4* color4_green = { red = 0; green = 255; blue = 0; alpha = 255; }
COLOR4* color4_blue = { red = 0; green = 0; blue = 255; alpha = 255; }

// change the theme of the imgui
void imgui_change_theme();

#endif