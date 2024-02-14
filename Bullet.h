#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED
#include <stdio.h>
#include <vector>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "global.h"

class Bullet
{
public:
    Bullet(float angle, int x, int y);
    void Init(); // put in GameWindow init
    void Update(); // put in GameWindow game_update
    void Draw(int*); // put in GameWindow draw running map

    bool remove_bullet(){
        return (x >= field_width -30  || x < 0 || y >= field_height || y < 0);
    }
    bool checkCollisionWithCharacter(int, int ,int,int, int*);

private:
    int x;
    int y;
    float radius;
    int bulletWidth;
    int bulletHeight;
    float angle;
    float dx;
    float dy;
    float speed;

    //std::vector<ALLEGRO_BITMAP*> img;
};


#endif // BULLET_H_INCLUDED