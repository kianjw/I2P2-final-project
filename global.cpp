#include "global.h"

/*int window_width = 800;
int window_height = 600;
int field_width = 600;
int field_height = 600;
int NumOfTower = 5;*/

int TowerRadius[] = {80, 80, 70, 110, 150};
char TowerClass[][20] = {"Arcane", "Archer", "Canon", "Poison", "Storm", "love"};
int TowerWidth[] = {72, 66, 72, 59, 45};
int TowerHeight[] = {121, 108, 69, 98, 112};
bool key_state[ALLEGRO_KEY_MAX] = {0};
int window = 1;
bool next_window = false;
bool losegame = false;