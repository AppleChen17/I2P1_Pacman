// [shared.h]
// you should put shared variables between files in this header.

#ifndef SCENE_SHARED_H
#define SCENE_SHARED_H
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <stdio.h>

// TODO-IF: Shared constant variable (without initializing value).

// TODO-IF: More shared resources or data that needed to be accessed
// across different scenes. initialize the value in 'shared.c'.;
;
extern ALLEGRO_FONT* font_pirulen_32;
extern ALLEGRO_FONT* font_pirulen_24;
extern ALLEGRO_SAMPLE* themeMusic;
extern ALLEGRO_SAMPLE* anothertheme;
extern ALLEGRO_SAMPLE* original;
extern ALLEGRO_SAMPLE* PACMAN_MOVESOUND;
extern ALLEGRO_SAMPLE* PACMAN_DEATH_SOUND;
extern ALLEGRO_SAMPLE*  PACMAN_POWERSOUND;
extern ALLEGRO_SAMPLE_ID PACMAN_POWERSOUND_ID;
extern ALLEGRO_SAMPLE* test_music;
extern ALLEGRO_SAMPLE_ID test_id;
extern ALLEGRO_FONT* menuFont;

extern FILE* record_file;
extern int total_records;
extern int now_theme;
extern int fontSize;
extern int mouse_x;
extern int mouse_y;
extern int eatghost;
extern float music_volume;
extern float effect_volume;
extern bool gameDone;
extern bool mouse_down;
extern bool pacman_wall;
extern bool stop_ghost;
extern bool catched[4];
typedef struct Score
{
	char name[1000];
	int score;
} Score;
extern Score player[10];
// Initialize shared variables and resources.
// Allows the game to perform any initialization it needs before
// starting to run.
void shared_init(void);
// Free shared variables and resources.
void shared_destroy(void);

#endif
