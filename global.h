#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include <allegro5/allegro_font.h>

#define font_size 12
#define grid_width 40
#define grid_height 40

#define window_width 1400
#define window_height 600
#define field_width 1200
#define field_height 600

#define cha_max 99999
#define Num_TowerType 6
#define Num_MonsterType 4
#define NumOfGrid (field_width / grid_width) * (field_height / grid_height)

extern int TowerRadius[];
extern char TowerClass[][20];
extern int TowerWidth[];
extern int TowerHeight[];
extern bool key_state[ALLEGRO_KEY_MAX];
extern int window;
extern bool next_window;
extern bool losegame;

enum {ARCANE = 0, ARCHER, CANON, POISON, STORM, LOVE};
enum {WOLF = 0, WOLFKNIGHT, DEMONNIJIA, CAVEMAN};

#endif // GLOBAL_H_INCLUDED
