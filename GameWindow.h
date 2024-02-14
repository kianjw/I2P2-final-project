#ifndef MAINWINDOW_H_INCLUDED
#define MAINWINDOW_H_INCLUDED

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <vector>
#include <list>
#include <time.h>
#include "Menu.h"
#include "Level.h"
#include "WolfKnight.h"
#include "CaveMan.h"
#include "Wolf.h"
#include "DemonNijia.h"
#include "Arcane.h"
#include "Archer.h"
#include "Canon.h"
#include "Poison.h"
#include "Storm.h"
#include "Attack.h"
#include "Slider.h"
#include "DataCenter.h"
#include "Love.h"
#include "Bullet.h"
#include "Hero.h"
#include "scene.h"

#define GAME_INIT -1
#define GAME_SETTING 0
#define GAME_SELECT 1
#define GAME_BEGIN 2
#define GAME_CONTINUE 3
#define GAME_FAIL 4
#define GAME_TERMINATE 5
#define GAME_NEXT_LEVEL 6
#define GAME_EXIT 7

// clock rate
const float FPS = 60;

// total number of level
const int LevelNum = 4;

// 1 coin every 2 seconds
const int CoinSpeed = FPS ;
const int Coin_Time_Gain = 1;



class GameWindow
{
public:
    // constructor
    GameWindow();

    // each process of scene
    void game_init();
    void game_reset();
    void game_play();
    void game_begin();

    int game_run();
    int game_update();
     void game_draw();
    void show_err_msg(int msg);
    void game_destroy();

    // each drawing scene function
    void draw_running_map();

    // process of updated event
    int process_event();
    // detect if mouse hovers over a rectangle
    bool mouse_hover(int, int, int, int);
    // detect if a tower will be constructed on road
    bool isOnRoad();
    void cha_init();
    Tower* create_tower(int);
    Monster* create_monster();
    void cha_draw();
    void cha_update(int);
   void background_update();
   void updateBullets();
public:
    bool initial = true;

private:
    ALLEGRO_BITMAP *icon;
    ALLEGRO_BITMAP *tower[Num_TowerType];
    ALLEGRO_BITMAP *background = NULL;
     ALLEGRO_BITMAP *start_background = NULL;
    ALLEGRO_BITMAP *end_background = NULL;
    ALLEGRO_BITMAP *instructionbg = NULL;

    ALLEGRO_DISPLAY* display = NULL;
    ALLEGRO_FONT *font = NULL;
    ALLEGRO_FONT *Medium_font = NULL;
    ALLEGRO_FONT *Large_font = NULL;

    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_EVENT event;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_TIMER *monster_pro = NULL;

    ALLEGRO_SAMPLE *sample = NULL;
    ALLEGRO_SAMPLE_INSTANCE *startSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *clearSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *failSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *backgroundSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *endSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *getMoney = NULL;
    ALLEGRO_SAMPLE_INSTANCE *purchase = NULL;
    ALLEGRO_SAMPLE_INSTANCE *endgame = NULL;

    LEVEL *level = NULL;
    Menu *menu = NULL;
    std::vector<Monster*> &monsterSet = DC->get_Monster();
    std::list<Tower*> &towerSet = DC->get_Tower();
    Bullet *bullet = NULL;

    int Monster_Pro_Count = 0;
    int Coin_Inc_Count = 0;
    int mouse_x, mouse_y;
    int selectedTower = -1, lastClicked = -1;
    int speed = 0;
    int speed_count= -1;
    int boomdelay[cha_max];
   int cha_width;
   int cha_height;
    bool redraw = false;
    bool mute = false;
    int chax[cha_max],chay[cha_max];
    int chahealth[cha_max];
    bool instruction_dec = false;
    int counting = 0;

};


#endif // MAINWINDOW_H_INCLUDED
