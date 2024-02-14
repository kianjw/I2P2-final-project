#ifndef HERO_H_INCLUDED
#define HERO_H_INCLUDED
#include <map>
#include <vector>

#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "global.h"
#include "Bullet.h"
enum class ChickState{
    RARE,
    MEDIUM,
    WELL,
    DEAD
};

class Hero{

public:
    void Init(); // put in GameWindow init
    void Update(); // put in GameWindow game_update
    void fireBullets();
    void Draw(bool,int, int*); // put in GameWindow draw running map
   // bool checkCollisionWithCharacter(int, int ,int,int);
    int Remove(int , int, int , int, bool, int*);
    int checkChick(int, int, int, int, bool);
     void Destroy();
     void reset();
private:
    int x, y;
    int counter = 0;
    int sprite_pos = 0;
    int speed = 5;
    int chick_x;
    int chick_y;
    bool firing = false;
 ChickState Cooked = ChickState::RARE;

    ALLEGRO_SAMPLE *sample = NULL;
    //ALLEGRO_SAMPLE_INSTANCE *shootingSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *guardSound = NULL;



    std::map<ChickState, ALLEGRO_BITMAP*> ImgData;
    std::vector<Bullet*> bullets;
};


#endif
