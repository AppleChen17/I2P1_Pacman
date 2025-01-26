#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <math.h>
#include "scene_menu_object.h"
#include "scene_settings.h"
#include "scene_game.h"
#include "scene_menu.h"
#include "utility.h"
#include "shared.h"
#include "game.h"

/* Internal Variables*/
static ALLEGRO_BITMAP* gameTitle = NULL;
static ALLEGRO_SAMPLE_ID menuBGM;
static int gameTitleW ;
static int gameTitleH ;
static bool popup = false;
static bool pop_name = false;
//extern Score player[10];//to update the value when game over or game done(if > 10 then need to ask name)

//static ALLEGRO_DISPLAY* display;
//static int popup_size = 600;
static drawpopup(void);
//static drawpopname(void);
//static bool pop_exit = false;
//static ALLEGRO_EVENT_QUEUE* eventQueue;

// [HACKATHON 3]
// TARGET : use a clickable button to enter setting scene.
// For `Button` struct(object) is defined in `scene_menu_object.h` and `scene_menu_object.c`
// STRONGLY recommend you trace both of them first. 

// TODO-HACKATHON 3-1: Declare variable for button
// Uncomment and fill the code below
static Button btnSettings;
static Button score_record;
static Button name;

static void init() 
{
	// TODO-HACKATHON 3-2: Create button to settings
	// Uncomment and fill the code below
	btnSettings = button_create(730, 20, 50, 50, "Assets/settings.png", "Assets/settings2.png");
	score_record = button_create(50, 20, 75, 75, "Assets/record.png", "Assets/document.png");
	name = button_create(50, 100, 75, 125, "Assets/name_1.png", "Assets/name_2.png");

	gameTitle = load_bitmap("Assets/title.png");
	gameTitleW = al_get_bitmap_width(gameTitle);
	gameTitleH = al_get_bitmap_height(gameTitle);
	stop_bgm(menuBGM);
	menuBGM = play_bgm(themeMusic, music_volume);

}


static void draw(){

	al_clear_to_color(al_map_rgb(0, 0, 0));

	const float scale = 0.7;
	const float offset_w = (SCREEN_W >> 1) - 0.5 * scale * gameTitleW;
	const float offset_h = (SCREEN_H >> 1) - 0.5 * scale * gameTitleH;

	//draw title image
	al_draw_scaled_bitmap(
		gameTitle,
		0, 0,
		gameTitleW, gameTitleH,
		offset_w, offset_h,
		gameTitleW * scale, gameTitleH * scale,
		0
	);
	al_draw_text(
		menuFont,
		al_map_rgb(255, 255, 255),
		SCREEN_W/2,
		SCREEN_H - 150,
		ALLEGRO_ALIGN_CENTER,
		"PRESS <ENTER>"
	);

		// TODO-HACKATHON 3-3: Draw button
		// Uncomment and fill the code below
		drawButton(btnSettings);
		drawButton(score_record);
		drawButton(name);
		//drawButton();
		if (popup)
		{
			drawpopup();
		}
		/*
		else if (pop_name)
		{
			drawpopname();
		}
		*/
}

static void on_mouse_move(int a, int mouse_x, int mouse_y, int f) {
	//	TODO-HACKATHON 3-7: Update button's status(hovered), and utilize the function `pnt_in_rect`, which you just implemented
	//	Uncomment and fill the code below
		 btnSettings.hovered = pnt_in_rect(mouse_x, mouse_y,btnSettings.body);
		 score_record.hovered = pnt_in_rect(mouse_x, mouse_y, score_record.body);
		 name.hovered = pnt_in_rect(mouse_x,mouse_y,name.body);
}


//	TODO-HACKATHON 3-8: When btnSettings clicked, switch to settings scene
//  `game_change_scene` is defined in `game.h`.
//  You can check line 121 `scene_menu.c` to see how to use this function.
//  And find the corresponding function for `scene_setting`
// 	Utilize the member defined in struct `Button`.
//  The logic here is 
//  `if clicked the mouse` && `mouse position is in the area of button`
// 	      `Enter the setting scene`
//	Uncomment and fill the code below

static void on_mouse_down()
{
	if (btnSettings.hovered)
	{
		game_change_scene(scene_settings_create());
	}
	else if (score_record.hovered)//show pop up box
	{
		popup = !popup;
		/*
		ALLEGRO_MENU* pop=al_create_popup_menu();
		game_log("created menu\n");
		ALLEGRO_MENU* show=al_get_display_menu(pop);
		game_log("show created!\n");
		al_flip_disply();
		*/
		/*
		display = al_create_display(popup_size,popup_size);
		eventQueue = al_create_event_queue();
		al_register_event_source(eventQueue, al_get_display_event_source(display));
		while (!pop_exit)
		{
			static ALLEGRO_EVENT ev;
			al_wait_for_event(eventQueue, &ev);
			if (ev.type== ALLEGRO_EVENT_DISPLAY_CLOSE)
				pop_exit = true;
			if (ev.type == ALLEGRO_EVENT_KEY_DOWN) 
			{
				if(key_state[ALLEGRO_KEY_ENTER])
					pop_exit = true;
			}
			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
		}
		//add
		game_log("close score board");
		al_destroy_display(display);
		//al_destroy_event_queue(eventQueue);
		*/
	}
	else if (name.hovered)
	{
		pop_name = !pop_name;
	}
}



static void destroy() {
	stop_bgm(menuBGM);
	al_destroy_bitmap(gameTitle);
	//	TODO-HACKATHON 3-10: Destroy button images
	//	Uncomment and fill the code below
	
	al_destroy_bitmap(btnSettings.default_img);
	al_destroy_bitmap(btnSettings.hovered_img);
	al_destroy_bitmap(score_record.default_img);
	al_destroy_bitmap(score_record.hovered_img);
	al_destroy_bitmap(name.default_img);
	al_destroy_bitmap(name.hovered_img);
	
}

static void on_key_down(int keycode) 
{

	switch (keycode) {
		case ALLEGRO_KEY_ENTER:
			game_change_scene(scene_main_create());
			break;
		default:
			break;
	}
}

// TODO-IF: Add more event callback functions such as update, ...
static drawpopup(void)
{
	//game_log("into draw\n");
	al_draw_filled_rectangle(150, 100, 600, 700, al_map_rgb(0, 0, 0));
	al_draw_rectangle(150, 100, 600, 700, al_map_rgb(255, 255, 255), 5);//畫外緣的線
	al_draw_text(menuFont,
		al_map_rgb(255, 255, 255),
		350, 110,
		ALLEGRO_ALIGN_CENTER, "Score Board!");
	al_draw_text(menuFont,
		al_map_rgb(255, 255, 255),
		350, 670,
		ALLEGRO_ALIGN_CENTER, "press again to close");
	//game_log("read number=%d\n",total_records);
	for (int i = 0; i < total_records; i++)
	{
		fscanf_s (record_file, "%100s", player[i].name, _countof(player[i].name));
		fscanf_s (record_file, "%d", &player[i].score);
	}
	/*
	while (fscanf_s(record_file, "%100s %d", player[total_records].name, &player[total_records].score) == 2) 
	{
		total_records++;
	}
	*/
	/*
	for (int i = 0; i < total_records; i++)
	{
		fscanf_s(record_file, "%100s %d", player[i].name, &player[i].score);
	}
	*/
	static int draw_x = 152;
	static int draw_y = 120;
	if (total_records == 0)
	{
		al_draw_text(menuFont,
			al_map_rgb(255, 255, 255),
			210,150 ,
			ALLEGRO_ALIGN_LEFT, "THERE IS NO RECORD");
	}
	
	else
	{
		for (int i = 0; i < total_records; i++)
		{
			static char output[1000];
			sprintf_s(output,1000,"%02d. %-20s %05d\n",i+1,player[i].name,player[i].score);
			al_draw_text(menuFont,
				al_map_rgb(255, 255, 255),
				210, 150+i*50,
				ALLEGRO_ALIGN_LEFT, output);
		}
	}
}


// Functions without 'static', 'extern' prefixes is just a normal
// function, they can be accessed by other files using 'extern'.
// Define your normal function prototypes below.

// The only function that is shared across files.
Scene scene_menu_create(void) {

	Scene scene;
	memset(&scene, 0, sizeof(Scene));
	scene.name = "Menu";
	scene.initialize = &init;
	scene.draw = &draw;
	scene.destroy = &destroy;
	scene.on_key_down = &on_key_down;
	scene.on_mouse_move = &on_mouse_move;
	// TODO-HACKATHON 3-9: Register on_mouse_down.
	// Uncomment the code below.
	
	scene.on_mouse_down = &on_mouse_down;
	//music= button_create(730, 20, 50, 50, "Assets/settings.png", "Assets/settings2.png");

	// -------------------------------------



	// TODO-IF: Register more event callback functions such as keyboard, mouse, ...
	game_log("Menu scene created");
	return scene;
}