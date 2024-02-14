#include "scene.h"
#include "global.h"
#include <iostream>

ALLEGRO_BITMAP *endbg = NULL;
ALLEGRO_FONT *end_Font_1 = NULL;
ALLEGRO_FONT *end_Font_2 = NULL;
//ALLEGRO_FONT *end_Font_3 = NULL;

void end_scene_intit()
{
    endbg = al_load_bitmap("./endbg-1.png");
    end_Font_1 = al_load_ttf_font("./font/BloodyTerror-GOW9Z.ttf",50,0);
    end_Font_2 = al_load_ttf_font("./font/pirulen.ttf",30,0);
    //end_Font_3 = al_load_ttf_font("./font/Dancing.ttf",20,0);
}
void end_scene_draw(int score,int best)
{ char buffer[50];
    al_draw_bitmap(endbg, 0, 0, 0);
     sprintf(buffer, "%d", score);
    //al_draw_rectangle(window_width-325, 350, window_width-225, 400, al_map_rgb(0, 0, 0), 5);
    al_draw_text(end_Font_1, al_map_rgb(255, 15, 15), window_width/2, window_height/2-250 , ALLEGRO_ALIGN_CENTRE, " CHICKEN DINNER ");
    al_draw_text(end_Font_2, al_map_rgb(255, 87, 51), window_width/2-200, window_height/2-100 , ALLEGRO_ALIGN_CENTRE, "Best score : ");
    al_draw_text(end_Font_2, al_map_rgb(255, 87, 51), window_width/2-200, window_height/2-10 , ALLEGRO_ALIGN_CENTRE, "Your score : ");
      al_draw_text(end_Font_2, al_map_rgb(255, 87, 51), window_width/2, window_height/2-10 , ALLEGRO_ALIGN_CENTRE, buffer);
      sprintf(buffer, "%d", best);
       al_draw_text(end_Font_2, al_map_rgb(255, 87, 51), window_width/2, window_height/2-100 , ALLEGRO_ALIGN_CENTRE, buffer);

}
void end_scene_destory()
{
    al_destroy_bitmap(endbg);
    al_destroy_font(end_Font_1);
    al_destroy_font(end_Font_2);
}
