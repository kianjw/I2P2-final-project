#ifndef LOVE_H_INCLUDED
#define LOVE_H_INCLUDED

#include "Tower.h"
#include "global.h"

class Love : public Tower
{
public:
    Love(int mouse_x = 0, int mouse_y = 0) : Tower(mouse_x, mouse_y)
    {
		type = LOVE;
        /*circle->r = 80;
        attack_frequency = 15;
        attack_velocity = 8;
        attack_harm_point = 7;
        img = al_load_bitmap("./Tower/Archer.png");
        attack_img = al_load_bitmap("./Tower/Archer_Beam.png");*/
    }

    int getWidth() override { return TowerWidth[LOVE]; }
    int getHeight() override { return TowerHeight[LOVE]; }
};

#endif // LOVE_H_INCLUDED
