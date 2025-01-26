// TODO-HACKATHON 3-9: Create scene_settings.h and scene_settings.c.
// No need to do anything for this part. We've already done it for
// you, so this 2 files is like the default scene template.
#include "scene_settings.h"
#include "scene_menu_object.h"
#include "game.h"


// Variables and functions with 'static' prefix at the top level of a
// source file is only accessible in that file ("file scope", also
// known as "internal linkage"). If other files has the same variable
// name, they'll be different variables.

/* Define your static vars / function prototypes below. */

// TODO-IF: More variables and functions that will only be accessed
// inside this scene. They should all have the 'static' prefix.
static float slider_width = 350;
static float slider_hight = 10;
static int CHECKBOX_SIZE = 50;
static slider music = {50,0,100};
static slider effect = {50,0,100};
static knob music_k = {0 ,65, 375 ,15};
static knob effect_k = {0 ,115, 375 ,15};
static checkbox theme1 = {0,50,250};//original
static checkbox theme2 = {0,50,350};

static char m_str[1000];
static char e_str[1000];
static int click = 0;


static int is_hovered(knob a, int mouse_x, int mouse_y)
{
	float dis_x = mouse_x - a.place;
	float dis_y = mouse_y - a.y;
	if (dis_x * dis_x + dis_y * dis_y <= 225)
	{
		//game_log("in hovered\n");
		return 1;
	}
	return 0;
}


static int hovered(checkbox c,int mouse_x,int mouse_y)
{
	float x = c.x;
	float y = c.y;
	if (mouse_x>=x && mouse_x<=x+50 && mouse_y >= y && mouse_y<=y+50)
	{
		return 1;
	}
	return 0;
}


//choose theme music
static void theme(void)
{
	al_draw_text(
		menuFont,
		al_map_rgb(255, 255, 255),
		50,
		175,
		ALLEGRO_ALIGN_LEFT,
		"Theme music"
	);
	al_draw_text(
		menuFont,
		al_map_rgb(255, 255, 255),
		125,
		260,
		ALLEGRO_ALIGN_LEFT,
		"original theme"
	);
	al_draw_text(
		menuFont,
		al_map_rgb(255, 255, 255),
		125,
		360,
		ALLEGRO_ALIGN_LEFT,
		"Happy Potato :D"
	);
	theme1.hovered = hovered(theme1,mouse_x,mouse_y);
	theme2.hovered = hovered(theme2,mouse_x,mouse_y);
	if (theme1.hovered && mouse_state[1])//have click
	{
		al_destroy_sample(themeMusic);
		themeMusic = load_audio("Assets/Music/original_theme.ogg");
		now_theme = 1;
	}
	if (theme2.hovered && mouse_state[1])
	{
		al_destroy_sample(themeMusic);
		themeMusic = load_audio("Assets/Music/theme_potato.mp3");
		now_theme = 2;
	}
	al_draw_rectangle(50, 250, 100, 300, al_map_rgb(255, 255, 255), 5);
	al_draw_rectangle(50, 350, 100, 400, al_map_rgb(255, 255, 255), 5);
	if (now_theme == 1)
	{
		al_draw_filled_rectangle(50, 250, 100, 300, al_map_rgb(255, 255, 255));
	}
	else if (now_theme == 2)
	{
		al_draw_filled_rectangle(50, 350, 100, 400, al_map_rgb(255, 255, 255));
	}
}

static void volume(void)
{
	al_draw_text(
		menuFont,
		al_map_rgb(255, 255, 255),
		50,
		50,
		ALLEGRO_ALIGN_LEFT,
		"Music"
	);
	al_draw_text(
		menuFont,
		al_map_rgb(255, 255, 255),
		50,
		100,
		ALLEGRO_ALIGN_LEFT,
		"Effect"
	);
	al_draw_rectangle(200, 60, 550, 70, al_map_rgb(255, 255, 255), 5);
	al_draw_rectangle(200, 110, 550, 120, al_map_rgb(255, 255, 255), 5);

	//自己做circle knob
	music_k.place = 200 + slider_width * music.position / 100;
	effect_k.place = 200 + slider_width * effect.position / 100;
	music_k.hovered = is_hovered(music_k, mouse_x, mouse_y);
	effect_k.hovered = is_hovered(effect_k, mouse_x, mouse_y);
	if (mouse_state[1])
	{
		click = 1;
	}
	else
		click = 0;
	if (music_k.hovered && mouse_x <= 550 && mouse_x >= 200 && click)
	{
		//game_log("mouse_x=%d mouse_y=%d\n", mouse_x, mouse_y);
		//game_log("mouse_down=%d\n", mouse_down);
		music_k.place = mouse_x;
		music.position = 100 * (music_k.place - 200) / slider_width;
		music_volume = music.position / 100;
		stop_bgm(test_id);
		test_id = play_audio(test_music, music_volume);
	}
	if (effect_k.hovered && mouse_x <= 550 && mouse_x >= 200 && click)
	{
		effect_k.place = mouse_x;
		effect.position = 100 * (effect_k.place - 200) / slider_width;
		effect_volume = effect.position / 100;
		stop_bgm(test_id);
		test_id = play_audio(test_music, effect_volume);
	}
	//要播那個音量的聲音試聽 => why fail to play audio??
	//what problem?? => 一直滑 => 播很多個會打架(instances are currently used)
	/*
	Plays a sample on one of the sample instances created by al_reserve_samples. 
	Returns true on success, false on failure. 
	Playback may fail because all the reserved sample instances are currently used.
	*/

	al_draw_filled_circle(music_k.place, 65, 15, al_map_rgb(255, 255, 255));
	al_draw_filled_circle(effect_k.place, 115, 15, al_map_rgb(255, 255, 255));


	sprintf_s(m_str, 100, "%.0f", music.position);
	sprintf_s(e_str, 100, "%.0f", effect.position);

	al_draw_text(
		menuFont,
		al_map_rgb(255, 255, 255),
		600,
		50,
		ALLEGRO_ALIGN_LEFT,
		m_str
	);
	al_draw_text(
		menuFont,
		al_map_rgb(255, 255, 255),
		600,
		100,
		ALLEGRO_ALIGN_LEFT,
		e_str
	);
	//game_log("music volume=%f\n", music_volume);
	//game_log("effect volume=%f\n", effect_volume);
}


static void draw(void)
{
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_text(
		menuFont,
		al_map_rgb(255, 255, 255),
		SCREEN_W/2,
		SCREEN_H - 150,
		ALLEGRO_ALIGN_CENTER,
		"<ENTER> Back to menu"
	);
	volume();
	theme();
}

static void on_key_down(int keycode) {
	switch (keycode) {
		case ALLEGRO_KEY_ENTER:
			game_change_scene(scene_menu_create());
			break;
		default:
			break;
	}
}


// The only function that is shared across files.
Scene scene_settings_create(void)
{
	Scene scene;
	memset(&scene, 0, sizeof(Scene));
	scene.name = "Settings";
	scene.draw = &draw;
	scene.on_key_down = &on_key_down;

	// TODO-IF: Register more event callback functions such as keyboard, mouse, ...
	game_log("Settings scene created");
	return scene;
}

// TODO-Graphical_Widget
// :
// Just suggestions, you can create your own usage.
	// Selecting BGM:
	// 1. Declare global variables for storing the BGM. (see `shared.h`, `shared.c`)
	// 2. Load the BGM in `shared.c`.
	// 3. Create dropdown menu for selecting BGM in setting scene, involving `scene_settings.c` and `scene_setting.h.
	// 4. Switch and play the BGM if the corresponding option is selected.

	// Adjusting Volume:
	// 1. Declare global variables for storing the volume. (see `shared.h`, `shared.c`)
	// 2. Create a slider for adjusting volume in setting scene, involving `scene_settings.c` and `scene_setting.h.
		// 2.1. You may use checkbox to switch between mute and unmute.
	// 3. Adjust the volume and play when the button is pressed.

	// Selecting Map:
	// 1. Preload the map to `shared.c`.
	// 2. Create buttons(or dropdown menu) for selecting map in setting scene, involving `scene_settings.c` and `scene_setting.h.
		// 2.1. For player experience, you may also create another scene between menu scene and game scene for selecting map.
	// 3. Create buttons(or dropdown menu) for selecting map in setting scene, involving `scene_settings.c` and `scene_setting.h.
	// 4. Switch and draw the map if the corresponding option is selected.
		// 4.1. Suggestions: You may use `al_draw_bitmap` to draw the map for previewing. 
							// But the map is too large to be drawn in original size. 
							// You might want to modify the function to allow scaling.