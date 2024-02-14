#include "Hero.h"
#include "Bullet.h"


//const char direction_name[][10] = {"left", "right", "front", "back"};
int draw_frequency = 15;
ALLEGRO_BITMAP *img;
ALLEGRO_BITMAP *img1;
ALLEGRO_BITMAP *img2;
ALLEGRO_BITMAP *img3;
ALLEGRO_BITMAP *imgguard;
void Hero::Init(){

    char buffer[50];

//    ALLEGRO_BITMAP *img;
    sprintf(buffer, "./Chicken/roast_chicken_%d.png", 1);
    img = al_load_bitmap(buffer);
    img1 = al_load_bitmap("./Chicken/roast_chicken_2.png");
    img2 = al_load_bitmap("./Chicken/roast_chicken_3.png");
    img3 = al_load_bitmap("./Chicken/roast_chicken_4.png");

    /*sample = al_load_sample("./Sound/collision-2 (2).wav");
    guardSound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(guardSound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(guardSound, al_get_default_mixer());*/

    imgguard = al_load_bitmap("./guard5.png");
    chick_x = al_get_bitmap_width(img);
    chick_y = al_get_bitmap_height(img);

    x = 10;
    y = window_height/2;
    firing = false;
}



void Hero::Update(){
    counter = (counter + 1) % draw_frequency;
    if(counter == 0){
        //sprite_pos = (sprite_pos + 1) % imgCount[direction];
        firing = true;

    }else firing = false;

    if( key_state[ALLEGRO_KEY_W] ){
        if(y >= 0) y -= speed;
        else y = y;
    }else if( key_state[ALLEGRO_KEY_A] ){
        if(x >= 0) x -= speed;
        else x = x;
    }else if( key_state[ALLEGRO_KEY_S] ){
        if(y <= window_height/5*4) y += speed;
        else y = y;
    }else if( key_state[ALLEGRO_KEY_D] ){
        if(x <= window_width/3) x += speed;
        else x = x;
    }

    if(firing){
        fireBullets();
    }

    //update bullet list
    for(auto& bullet : bullets){
        bullet->Update();
    }

    //remove dead bullets
    for(auto bullet = bullets.begin(); bullet != bullets.end(); bullet++){
        if((*bullet)->remove_bullet()){
            bullets.erase(bullet);
            bullet--;
        }
    }

}
int Hero::Remove(int chaX, int chaY, int chaWidth, int chaHeight,bool check, int*bullet_mode)
{
  for(auto bullet = bullets.begin(); bullet != bullets.end(); bullet++){
        if((*bullet)->checkCollisionWithCharacter(chaX, chaY, chaWidth, chaHeight, bullet_mode)){
            bullets.erase(bullet);
            bullet--;
            check = true;

        }
}
return check;

}
int Hero::checkChick(int chaX, int chaY, int chaWidth, int chaHeight,bool check1)
{
    if (x < chaX + chaWidth &&
          x + chick_x > chaX &&
          y < chaY + chaHeight &&
          y + chick_y > chaY)
        check1 = true;


return check1;

}


void Hero::fireBullets(){
    bullets.emplace_back(new Bullet(0, x+chick_x, y+chick_y/2));
}
float rotation = 0;

void Hero::Draw(bool guard, int health, int*bullet_mode){


    if(health >= 9 && health <= 12){
        al_draw_bitmap(img, x, y, 0);
    }else if(health <= 8 && health >= 5){
        al_draw_bitmap(img1, x, y, 0);
    }else if(health <= 4 && health >= 1){
        al_draw_bitmap(img2, x, y, 0);}
    //}else{
    //    al_draw_bitmap(img3, x, y, 0);
    //}
/*
    if(health >=9 && health<=12)
    al_draw_bitmap(img, x, y, 0);
    if(health<=8 && health >=5)
     al_draw_bitmap(img1, x, y, 0);
    if(health >=2 && health <=4)
     al_draw_bitmap(img2, x, y, 0);
    if(health == 1);
     al_draw_bitmap(img3, x, y, 0);*/
    if(guard)  //al_draw_circle(x+chick_x/2, y+chick_y/2, chick_x/2, al_map_rgb(255, 0, 0), 2);
    //al_draw_scaled_bitmap(imgguard, 0, 0, al_get_bitmap_width(imgguard), al_get_bitmap_height(imgguard), x-20, y, chick_x+50, chick_y+15, 0);
    {    rotation += 0.02;

al_draw_rotated_bitmap(imgguard,
                       al_get_bitmap_width(imgguard) / 2, // Center of rotation along the x-axis
                       al_get_bitmap_height(imgguard) / 2, // Center of rotation along the y-axis
                       x+50, y+40,                               // Destination position (center of rotation)
                       rotation, 0); }
    for(auto& bullet : bullets){
        bullet->Draw(bullet_mode);
    }
}

void Hero::Destroy(){
    for(auto& bullet : bullets){
        delete bullet;
    }
    bullets.clear();
    x = 10;
    y = window_height/2;
    firing = false;
    //al_destroy_sample_instance(guardSound);
    /*al_destroy_bitmap(img);
    al_destroy_bitmap(img1);
    al_destroy_bitmap(img2);
    al_destroy_bitmap(img3);
    al_destroy_bitmap(imgguard);*/
    //al_destroy_sample_instance(subtract);

}
