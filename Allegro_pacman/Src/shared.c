// [shared.c]
// you should define the shared variable declared in the header here.

#include "shared.h"
#include "utility.h"
#include "game.h"
// #include "scene_menu.h"

ALLEGRO_FONT* font_pirulen_32;
ALLEGRO_FONT* font_pirulen_24;
ALLEGRO_SAMPLE* themeMusic = NULL;
ALLEGRO_SAMPLE* anothertheme = NULL;
ALLEGRO_SAMPLE* original = NULL;
ALLEGRO_SAMPLE* PACMAN_MOVESOUND = NULL;
ALLEGRO_SAMPLE* PACMAN_DEATH_SOUND = NULL;
ALLEGRO_SAMPLE* PACMAN_POWERSOUND=NULL;
ALLEGRO_SAMPLE* test_music=NULL;
ALLEGRO_SAMPLE_ID test_id = {0,0};
ALLEGRO_SAMPLE_ID PACMAN_POWERSOUND_ID = { 0,0 };
ALLEGRO_FONT* menuFont = NULL;
FILE* record_file = NULL;
int fontSize = 30;
float music_volume = 0.5;
float effect_volume = 0.5;
int eatghost = 0;
bool mouse_down = false;
bool gameDone = false;
bool pacman_wall = false;
bool stop_ghost = false;
bool catched[4] = { 0,0,0,0 };
int mouse_x = 0;
int mouse_y = 0;
int now_theme = 1;//original one
int total_records = 0;
Score player[10];

/*
	A way to accelerate is load assets once.
	And delete them at the end.
	This method does provide you better management of memory.
	
*/
void shared_init(void) 
{
	menuFont = load_font("Assets/Minecraft.ttf", fontSize);
	themeMusic = load_audio("Assets/Music/original_theme.ogg");
	//original = load_audio("Assets/Music/original_theme.ogg");
	//anothertheme = load_audio("Assets/Music/theme_potato.mp3");
	PACMAN_MOVESOUND = load_audio("Assets/Music/pacman-chomp.ogg");
	PACMAN_DEATH_SOUND = load_audio("Assets/Music/pacman_death.ogg");
	PACMAN_POWERSOUND = load_audio("Assets/Music/power_mode.ogg");
	test_music = load_audio("Assets/Music/test_bamboo_sound_effect.mp3");
	static errno_t error;
	error = fopen_s(&record_file,"Assets/score_record.txt", "r");
	if (error)
		game_log("open record file no!!!\n");
	fscanf_s(record_file, "%d", &total_records);
	game_log("read record success!\n");
}

void shared_destroy(void) {

	al_destroy_font(menuFont);
	al_destroy_sample(themeMusic);
	al_destroy_sample(anothertheme);
	al_destroy_sample(original);
	al_destroy_sample(PACMAN_MOVESOUND);
	al_destroy_sample(PACMAN_DEATH_SOUND);
	al_destroy_sample(PACMAN_POWERSOUND);
	al_destroy_sample(test_music);
	fclose(record_file);
	//al_destroy_file(record_file);
}