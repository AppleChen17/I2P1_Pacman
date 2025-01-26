#ifndef SCENE_SETTINGS_H
#define SCENE_SETTINGS_H
#include "game.h"
#include "shared.h"
#include "scene_menu.h"

typedef struct slider
{
	float position;
	float min;
	float max;

} slider;
typedef struct knob
{
	bool hovered;
	float y;
	float place;
	int r;//radius
} knob;
typedef struct checkbox
{
	bool hovered;
	float x;
	float y;
} checkbox;

Scene scene_settings_create(void);
int is_hovered(knob x, int mouse_x, int mouse_y);
//void in_setting();

#endif
