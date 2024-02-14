#include "Bullet.h"
#include <cmath>
ALLEGRO_BITMAP* img_bullet;
double start_time;
Bullet::Bullet(float _angle, int _x, int _y) : angle(_angle), x(_x), y(_y){
    Init();
 };


void Bullet::Init()
{
    char buffer[50];


    sprintf(buffer, "./Bullet/drumstick_%d.png", 1);
    img_bullet = al_load_bitmap(buffer);
    bulletWidth =  al_get_bitmap_width(img_bullet);
    bulletHeight =  al_get_bitmap_width(img_bullet);
    speed = 8;
    dx = cos(angle)* speed;
    dy = sin(angle)* speed;
}

void Bullet::Update()
{
    x += dx;
    y += dy;
}
int speedy = 25;
void Bullet::Draw(int* bullet_mode){
    double current_time = al_get_time();

    // Check if the bullet is in "special" mode (bullet_mode == 1)
    if (*bullet_mode == 1) {
        // Draw the scaled bitmap for 10 seconds
        if (current_time - start_time <= 10.0) {
            al_draw_scaled_bitmap(
                img_bullet, 0, 0, al_get_bitmap_width(img_bullet), al_get_bitmap_height(img_bullet),
                x, y -speedy-30, al_get_bitmap_width(img_bullet) , al_get_bitmap_height(img_bullet) , 0
            );
            al_draw_scaled_bitmap(
                img_bullet, 0, 0, al_get_bitmap_width(img_bullet), al_get_bitmap_height(img_bullet),
                x, y  , al_get_bitmap_width(img_bullet) , al_get_bitmap_height(img_bullet) , 0
            );
            al_draw_scaled_bitmap(
                img_bullet, 0, 0, al_get_bitmap_width(img_bullet), al_get_bitmap_height(img_bullet),
                x, speedy+y +30, al_get_bitmap_width(img_bullet) , al_get_bitmap_height(img_bullet) , 0
            );
        }
         else {
            // After 10 seconds, set bullet_mode back to 0
            *bullet_mode = 0;
            start_time = current_time;  // Reset the start time for the next shot
        }}
        else if (*bullet_mode == 2) {
        // Draw the scaled bitmap for 10 seconds
        if (current_time - start_time <= 10.0) {
           al_draw_scaled_bitmap(
                img_bullet, 0, 0, al_get_bitmap_width(img_bullet), al_get_bitmap_height(img_bullet),
                x, y - 25, al_get_bitmap_width(img_bullet) * 2, al_get_bitmap_height(img_bullet) * 2, 0
            );


        }
        else {
            // After 10 seconds, set bullet_mode back to 0
            *bullet_mode = 0;
            start_time = current_time;  // Reset the start time for the next shot
        }
    }
   else al_draw_bitmap(img_bullet, x, y, 0);
}
bool Bullet::checkCollisionWithCharacter(int chaX, int chaY, int chaWidth, int chaHeight, int* bullet_mode){
    if(*bullet_mode == 0 ) {
     if ((x < chaX + chaWidth &&
            x + bulletWidth > chaX &&
            y < chaY + chaHeight &&
            y  + bulletHeight > chaY)
            ) {

            return true;
        }
        return false;
        }
    if(*bullet_mode == 1){  if ((x < chaX + chaWidth &&
            x + bulletWidth > chaX &&
            y < chaY + chaHeight &&
            y  + bulletHeight > chaY)
            || (x < chaX + chaWidth &&
            x + bulletWidth > chaX &&
            y -speedy-30 < chaY + chaHeight &&
           y -speedy-30 + bulletHeight > chaY)
           || (x < chaX + chaWidth &&
            x + bulletWidth > chaX &&
           speedy+y +30< chaY + chaHeight &&
          speedy+y +30 + bulletHeight > chaY)
            ) {

            return true;
        }
        return false;
        }
    else if(*bullet_mode == 2){
     if (x < chaX + chaWidth &&
            x + bulletWidth * 2 > chaX &&
            y -25< chaY + chaHeight &&
            y -25 + bulletHeight * 2 > chaY) {

            return true;
        }
        return false;
    }
}
