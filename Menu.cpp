#include "Menu.h"
#include "GameWindow.h"

const int ThumbWidth = 50;
const int ThumbHeight = 50;
const int gapX = 40, gapY = 30;
const int offsetX = 30 + field_width, offsetY = 150;
const int Initial_Health = 1;
const int Initial_Coin = 10;
 ALLEGRO_FONT *menuFont1;
    ALLEGRO_BITMAP *health[13];
      ALLEGRO_BITMAP *score;
       ALLEGRO_BITMAP *coin;

bool
Menu::isInRange(int point, int startPos, int length)
{
    if(point >= startPos && point <= startPos + length)
        return true;

    return false;
}

bool
Menu::Enough_Coin(int type)
{

    if(type < 0 || type >= 4)
        return false;

    return (Coin + need_coin[type] >= 0);
}

Menu::Menu()
{
    char filename[50];

    HealthPoint = 12;
    Coin = 0;
    Score = 0;

   /* for(int i=0;i<Num_TowerType; i++)
    {
        ALLEGRO_BITMAP *tower;
        sprintf(filename, "./Tower/%s_Menu.png", TowerClass[i]);*/
         ALLEGRO_BITMAP *tower[4];
        tower[0] = al_load_bitmap("./love_Menu.png");
        tower[1] = al_load_bitmap("./guardmenu.png");
        tower[2] = al_load_bitmap("./chicken.png");
        tower[3] = al_load_bitmap("./chicken1.png");
        menu_tower.push_back(tower[0]);
         menu_tower.push_back(tower[1]);
          menu_tower.push_back(tower[2]);
            menu_tower.push_back(tower[3]);
    //}
    coin = al_load_bitmap("./coin.png");
    score = al_load_bitmap("./score.png");
    love = al_load_bitmap("./Tower/love.png");
    menuFont = al_load_ttf_font("pirulen.ttf", 30, 10); // load font
     menuFont1 = al_load_ttf_font("pirulen.ttf", 45, 10);
     health[12] =al_load_bitmap("./12-removebg-preview.png");
    health[11] =al_load_bitmap("./11-removebg-preview.png");
     health[10] =al_load_bitmap("./10-removebg-preview.png");
    health[9] =al_load_bitmap("./9-removebg-preview.png");
     health[8] =al_load_bitmap("./8-removebg-preview.png");
     health[7] =al_load_bitmap("./7-removebg-preview.png");
     health[6] =al_load_bitmap("./6-removebg-preview.png");
     health[5] =al_load_bitmap("./5-removebg-preview.png");
     health[4] =al_load_bitmap("./4-removebg-preview.png");
     health[3] =al_load_bitmap("./3-removebg-preview.png");
     health[2] =al_load_bitmap("./2-removebg-preview.png");
     health[1] =al_load_bitmap("./1-removebg-preview.png");
     health[0] =al_load_bitmap("./0-removebg-preview.png");


    sample = al_load_sample("./Sound/collision.wav");
    subtract = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(subtract, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(subtract, al_get_default_mixer());

    sample = al_load_sample("./Sound/collision-2 (2).wav");
    guard = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(guard, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(guard, al_get_default_mixer());

    /*sample = al_load_sample("./Sound/coin.wav");
    purchase = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(purchase, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(purchase, al_get_default_mixer());*/

}

Menu::~Menu()
{
    al_destroy_bitmap(love);
    al_destroy_font(menuFont);
    al_destroy_sample_instance(subtract);
    al_destroy_sample_instance(guard);

    for(int i=0; i < Num_TowerType; i++)
        al_destroy_bitmap(menu_tower[i]);

    menu_tower.clear();
}

void
Menu::Reset()
{
    HealthPoint = 12;
    Coin = Initial_Coin;
    Score = 0;
    killedMonster = 0;
    collision = false;
}



void
Menu::Draw()
{
    char buffer[50];
    al_draw_filled_rectangle(1200, 0, 1400, 600, al_map_rgb(205, 133, 63));

    if(collision) al_play_sample_instance(subtract);
    collision = false;

    al_draw_bitmap(health[HealthPoint], 1200, 120, 0);
    //al_draw_scaled_bitmap(health[HealthPoint], 0, 0, al_get_bitmap_width(health[12]), al_get_bitmap_height(health[12]),  1200, 120, 200, 20, 0);

    /*if(HealthPoint == 12)
         al_draw_scaled_bitmap(health[12], 0, 0, al_get_bitmap_width(health[12]), al_get_bitmap_height(health[12]),  1200, 120, 200, 20, 0);
    if(HealthPoint == 11)
         al_draw_scaled_bitmap(health[11], 0, 0, al_get_bitmap_width(health[11]), al_get_bitmap_height(health[11]), 1200, 120, 200, 20, 0);
    if(HealthPoint == 10)
         al_draw_scaled_bitmap(health[10], 0, 0, al_get_bitmap_width(health[10]), al_get_bitmap_height(health[10]), 1200, 120, 200, 20, 0);
    if(HealthPoint == 9)
         al_draw_scaled_bitmap(health[9], 0, 0, al_get_bitmap_width(health[9]), al_get_bitmap_height(health[9]), 1200, 120, 200, 20, 0);
    if(HealthPoint == 8)
         al_draw_scaled_bitmap(health[8], 0, 0, al_get_bitmap_width(health[8]), al_get_bitmap_height(health[8]), 1200, 120, 200, 20, 0);
    if(HealthPoint == 7)
         al_draw_scaled_bitmap(health[7], 0, 0, al_get_bitmap_width(health[7]), al_get_bitmap_height(health[7]), 1200, 120, 200, 20, 0);
    if(HealthPoint == 6)
         al_draw_scaled_bitmap(health[6], 0, 0, al_get_bitmap_width(health[6]), al_get_bitmap_height(health[6]), 1200, 120, 200, 20, 0);
    if(HealthPoint == 5)
         al_draw_scaled_bitmap(health[5], 0, 0, al_get_bitmap_width(health[5]), al_get_bitmap_height(health[5]), 1200, 120, 200, 20, 0);
    if(HealthPoint == 4)
         al_draw_scaled_bitmap(health[4], 0, 0, al_get_bitmap_width(health[4]), al_get_bitmap_height(health[4]), 1200, 120, 200, 20, 0);
    if(HealthPoint == 3)
         al_draw_scaled_bitmap(health[3], 0, 0, al_get_bitmap_width(health[3]), al_get_bitmap_height(health[3]),1200, 120, 200, 20, 0);
    if(HealthPoint == 2)
         al_draw_scaled_bitmap(health[2], 0, 0, al_get_bitmap_width(health[2]), al_get_bitmap_height(health[2]), 1200, 120, 200, 20, 0);
    if(HealthPoint == 1)
         al_draw_scaled_bitmap(health[1], 0, 0, al_get_bitmap_width(health[1]), al_get_bitmap_height(health[1]), 1200, 120, 200, 20, 0);
    if(HealthPoint == 0)
         al_draw_scaled_bitmap(health[0], 0, 0, al_get_bitmap_width(health[0]), al_get_bitmap_height(health[0]),1200, 120, 200, 20, 0);*/

   //sprintf(buffer, "Health: %d", HealthPoint);
    //al_draw_bitmap(score, offsetX, 20 + gapY, 0);
    //al_draw_text(menuFont, al_map_rgb(255, 255, 255), 2*al_get_bitmap_width(love) + offsetX, 20 + gapY, 0, buffer);
    al_draw_scaled_bitmap(score, 0, 0, al_get_bitmap_width(score), al_get_bitmap_height(score),  1200, 0, 200, 100, 0);
    sprintf(buffer, "%d", Coin);
    al_draw_text(menuFont, al_map_rgb(0, 0, 0), 1265, 170, 0, buffer);
    al_draw_scaled_bitmap(coin, 0, 0, al_get_bitmap_width(coin), al_get_bitmap_height(coin),  1200, 160, 50, 50, 0);

    //sprintf(buffer, "Guard: %d", Guard);
    //al_draw_text(menuFont, al_map_rgb(255, 255, 255), offsetX, 20 + 3*gapY, 0, buffer);

    sprintf(buffer, "%d", Score);
    al_draw_text(menuFont1, al_map_rgb(0, 0, 0), 1300, 35, 0, buffer);
    //al_draw_scaled_text(menuFont, al_map_rgb(255, 255, 255), 1300, 50, 0, 2.0, 2.0, 0, buffer);
    for(int i=0; i < 4; i++)
    {
        int pos_x = offsetX + 30;//(ThumbWidth + gapX) * (i%2);
        int pos_y = offsetY + 100 +(ThumbHeight + gapY) * (i );

        al_draw_bitmap(menu_tower[i], pos_x, pos_y, 0);

//al_draw_scaled_bitmap(menu_tower[i], 0, 0, al_get_bitmap_width(menu_tower[i]), al_get_bitmap_height(menu_tower[i]),  pos_x, pos_y,  al_get_bitmap_width(menu_tower[i])*2,  al_get_bitmap_height(menu_tower[i])*2, 0);
        if(!Enough_Coin(i) )
            al_draw_filled_rectangle(pos_x, pos_y, pos_x + ThumbWidth, pos_y + ThumbHeight, al_map_rgba(100, 100, 100, 100));
        else if(i == selectedTower)
            al_draw_rectangle(pos_x, pos_y, pos_x + ThumbWidth, pos_y + ThumbHeight, al_map_rgb(255, 0, 0), 0);
        else
            al_draw_rectangle(pos_x, pos_y, pos_x + ThumbWidth, pos_y + ThumbHeight, al_map_rgb(0, 0, 0), 0);
    }
}

int
Menu::MouseIn(int mouse_x, int mouse_y)
{
    //bool enoughCoin;

    selectedTower = -1;

    for(int i=0; i < 4; i++)
    {
        int pos_x = offsetX +30;//+ (ThumbWidth + gapX) * (i % 2);
        int pos_y = offsetY + 100+(ThumbHeight + gapY) * (i );

        if(isInRange(mouse_x, pos_x, ThumbWidth) && isInRange(mouse_y, pos_y, ThumbHeight))
        {
            if(Enough_Coin(i))
            {
                selectedTower = i;
                break;
            }
        }
    }
    return selectedTower;
}

bool
Menu::Subtract_HP(int escapeNum)
{
    HealthPoint -= escapeNum;

    return (HealthPoint == 0);
}

void
Menu::Gain_Score(int scoreWorth)
{
    killedMonster++;
    Score += scoreWorth;
}

void
Menu::upHealth(int up){
    if(up < 0) collision = true;
    if(HealthPoint == 12 && up>0) up = 0;
    HealthPoint += up;
    //al_play_sample_instance(subtract);
}
void
Menu::removeGuard(){
    Guard = 0;
    al_play_sample_instance(guard);
}

