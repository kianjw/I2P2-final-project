#include "GameWindow.h"
#include "global.h"
#include <iostream>

#define WHITE al_map_rgb(255, 255, 255)
#define BLACK al_map_rgb(0, 0, 0)
#define ORANGE_LIGHT al_map_rgb(255, 196, 87)
#define ORANGE_DARK al_map_rgb(255, 142, 71)
#define PURPLE al_map_rgb(149, 128, 255)
#define BLUE al_map_rgb(77, 129, 179)
/*
#define min(a, b) ((a) < (b)? (a) : (b))
#define max(a, b) ((a) > (b)? (a) : (b))*/
ALLEGRO_BITMAP *chaimage = NULL;
ALLEGRO_BITMAP *boomimage = NULL;
//int score = 0;
char score_string[3];
FILE *best_score_file = NULL;
int best_score = 0;
char best_score_string[5];
int best_score_was_updated = 0;
int bullet_mode = 0;

//int draw = 200;
#include <fstream>

// Function to read the best score from a file
int readBestScore() {
    std::ifstream file("best_score.txt");
    int bestScore = 0;
    if (file.is_open()) {
        file >> bestScore;
        file.close();
    }
    return bestScore;
}

// Function to write the best score to a file
void writeBestScore(int bestScore) {
    std::ofstream file("best_score.txt");
    if (file.is_open()) {
        file << bestScore;
        file.close();
    }
}
void
GameWindow::updateBullets(){
     static int cooldown = 0;
     if (cooldown > 0) {
        cooldown--;
        //return;
    }
    for(int i = 1;i<cha_max;i++){
        bool check = false; bool check_chick1 = false; bool check_guard = false;
        if(chax[i] + 250>0 && chax[i] < 1020 && chay[i] < 450 ){
        check =  DC->get_Hero().Remove(chax[i], chay[i], cha_width,cha_height, check, &bullet_mode);}
        if(check&& chahealth[i] && chax[i] + 250>0 && chax[i] < 1020 && chay[i] < 450){
            if(bullet_mode == 1) chahealth[i] -=2;
            else if(bullet_mode == 2) chahealth[i] -=5;
            else if(bullet_mode == 0) chahealth[i] -=2;
            if(chahealth[i] <= 0) menu->Change_Coin(1);
            check = false;
        }


        check_chick1 =DC->get_Hero().checkChick(chax[i], chay[i], cha_width,cha_height, check_chick1);
        if(check_chick1 && chahealth[i] && chax[i] + 250>0 && chax[i] < 1020 && chay[i] < 450 ){
            if(menu->checkGuard()) {
                menu->removeGuard();
                cooldown = 60;
                chahealth[i] = 0;
                continue;
            }
           // menu->upHealth(-0);
            chahealth[i] = 0;
            menu->upHealth(-1);
            check_chick1 = false;
            cooldown = 60;
        }


    }
}
void
GameWindow::cha_init(){
srand(time(NULL));

chax[0] =  1250;
chay[0] = (rand() % 500);
chahealth[0] = 3;
for(int i = 1; i<cha_max;i++){
    chax[i] = chax[i - 1] + 200;
    chay[i] = (rand() % 500) ;
    chahealth[i] = 3;
}}

void
GameWindow::cha_draw(){
    for(int i = 1 ; i< cha_max;i++){ //1020
        if(chax[i] + 250>0 && chax[i] < 1020 && chay[i] < 450 ){  //450

        if(chahealth[i] <=0) {

            al_play_sample_instance(getMoney);
     // al_draw_bitmap(boomimage, chax[i], chay[i], 0);
                   // boomdelay[i]--;
                   chax[i] = -2000;
                    chay[i] = -2000;
                    chax[i] = chax[i-1] + 200;
                   chay[i] = (rand() % 500);
              //al_draw_bitmap(chaimage, chax[i], chay[i], 0);
                //chahealth[i]= 1;
                    }
          else
               al_draw_bitmap(chaimage, chax[i], chay[i], 0);
                //chahealth[i]= 1;

        }
    }
}

void
GameWindow::cha_update(int speed){
    for(int i = 1; i<cha_max;i++){
       // if(chax[i] + 250>0 && chax[i] < 1020 && chay[i] < 450 ){
        //if (chahealth[i] <= 0 && boomdelay[i] <= 0) {
            //boomdelay[i] = 60; // Set the delay to 60 frames (adjust as needed)
        //}
   //if(speed>=10) {  speed = 10;}
        chax[i] = chax[i] - 1 - speed;


                //chahealth[i]= 1;

        }

    // Increment the timer

   //}
}
//}


float Attack::volume = 1.0;

void set_attack_volume(float volume)
{
    Attack::volume = volume;
}

bool compare(Tower *t1, Tower *t2)
{
    return (t1->getY() <= t2->getY());
}

void
GameWindow::game_init()
{
    char buffer[50];

    icon = al_load_bitmap("./icon.png");
    background = al_load_bitmap("./game_background.png");
    chaimage = al_load_bitmap("./cha2.png");
    cha_width = al_get_bitmap_width(chaimage);
    cha_height = al_get_bitmap_height(chaimage);
    boomimage = al_load_bitmap("./boom.png");
    start_background = al_load_bitmap("./startbg.png");
    instructionbg = al_load_bitmap("./instruction.png");
    for(int i = 0; i < Num_TowerType; i++)
    {
        sprintf(buffer, "./Tower/%s.png", TowerClass[i]);
        tower[i] = al_load_bitmap(buffer);
    }

    al_set_display_icon(display, icon);
    al_reserve_samples(7);

    sample = al_load_sample("./Sound/starting.wav");
    startSound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(startSound, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(startSound, al_get_default_mixer());

    sample = al_load_sample("./Sound/background.wav");
    backgroundSound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(backgroundSound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(backgroundSound, al_get_default_mixer());

    sample = al_load_sample("./Sound/deadmusic-2.wav");
    failSound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(failSound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(failSound, al_get_default_mixer());

    sample = al_load_sample("./Sound/ending.wav");
    endSound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(endSound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(endSound, al_get_default_mixer());

    sample = al_load_sample("./Sound/coin-1.wav");
    getMoney = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(getMoney, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(getMoney, al_get_default_mixer());

    sample = al_load_sample("./Sound/coin.wav");
    purchase = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(purchase, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(purchase, al_get_default_mixer());

    sample = al_load_sample("./Sound/endgame.wav");
    endgame = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(endgame, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(endgame, al_get_default_mixer());

    DC->get_Hero().Init();
    level = new LEVEL(1);
    menu = new Menu();
}

bool
GameWindow::mouse_hover(int startx, int starty, int width, int height)
{
    if(mouse_x >= startx && mouse_x <= startx + width)
        if(mouse_y >= starty && mouse_y <= starty + height)
            return true;

    return false;
}

bool
GameWindow::isOnRoad()
{
    /*int startx, starty;
    int widthOfTower;

    widthOfTower = TowerWidth[selectedTower];

    for(int i=0; i < NumOfGrid; i++)
    {
        startx = (i % 15) * 40;
        starty = (i / 15) * 40;

        if(level->isRoad(i)) {
            if((mouse_x + (widthOfTower/2) < startx) || (mouse_x - (widthOfTower/2) > startx + grid_width))
                continue;
            else if((mouse_y + (widthOfTower/2) < starty) || (mouse_y > starty + grid_height))
                continue;
            else
                return true;
        }
    }
    return false;*/
}

Tower*
GameWindow::create_tower(int type)
{
    Tower *t = NULL;

    if(isOnRoad())
        return t;

    switch(type)
    {
    case ARCANE:
        t = new Arcane(mouse_x, mouse_y);
        break;
    case ARCHER:
        t = new Archer(mouse_x, mouse_y);
        break;
    case CANON:
        t = new Canon(mouse_x, mouse_y);
        break;
    case POISON:
        t = new Poison(mouse_x, mouse_y);
        break;
    case STORM:
        t = new Storm(mouse_x, mouse_y);
        break;
    case LOVE:
        //t = new Love(mouse_x,mouse_y);
        //menu->upHealth();
        break;
    default:
        break;
    }


    return t;
}

Monster*
GameWindow::create_monster()
{/*
    Monster *m = NULL;

    if(level->MonsterNum[WOLF])
    {
        level->MonsterNum[WOLF]--;
        m = new Wolf(level->ReturnPath());
    }
    else if(level->MonsterNum[WOLFKNIGHT])
    {
        level->MonsterNum[WOLFKNIGHT]--;
        m = new WolfKnight(level->ReturnPath());
    }
    else if(level->MonsterNum[DEMONNIJIA])
    {
        level->MonsterNum[DEMONNIJIA]--;
        m = new DemonNijia(level->ReturnPath());
    }
    else if(level->MonsterNum[CAVEMAN])
    {
        level->MonsterNum[CAVEMAN]--;
        m = new CaveMan(level->ReturnPath());
    }
    else
    {
        al_stop_timer(monster_pro);
    }

    return m;*/
}

void
GameWindow::game_play()
{
    int msg;

    srand(time(NULL));

    msg = -1;
     //DC->get_Hero().Init();
    game_reset();
    game_begin();

    while(msg != GAME_EXIT)
    {
        msg = game_run();
    }

    show_err_msg(msg);
}

void
GameWindow::show_err_msg(int msg)
{
    if(msg == GAME_TERMINATE)
        fprintf(stderr, "Game Terminated...");
    else
        fprintf(stderr, "unexpected msg: %d", msg);

    game_destroy();
    exit(9);
}

GameWindow::GameWindow()
{
    if (!al_init())
        show_err_msg(-1);
    printf("Game Initializing...\n");
    display = al_create_display(window_width, window_height);
    event_queue = al_create_event_queue();

    timer = al_create_timer(1 / FPS);
    monster_pro = al_create_timer(1.0 / FPS);

    if(timer == NULL || monster_pro == NULL)
        show_err_msg(-1);

    if (display == NULL || event_queue == NULL)
        show_err_msg(-1);

    al_init_primitives_addon();
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon(); // initialize the ttf (True Type Font) addon
    al_init_image_addon(); // initialize the image addon
    al_init_acodec_addon(); // initialize acodec addon

    al_install_keyboard(); // install keyboard event
    al_install_mouse();    // install mouse event
    al_install_audio();    // install audio event

    font = al_load_ttf_font("./font/Caviar_Dreams_Bold.ttf",12,0); // load small font
    Medium_font = al_load_ttf_font("./font/Caviar_Dreams_Bold.ttf",24,0); //load medium font
    Large_font = al_load_ttf_font("./font/Caviar_Dreams_Bold.ttf",36,0); //load large font

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_timer_event_source(monster_pro));
    cha_init();
    game_init();
}

void
GameWindow::game_begin()
{
    printf(">>> Start Level[%d]\n", level->getLevel());
    //draw_running_map();
    game_draw();
    //al_play_sample_instance(startSound);
    //while(al_get_sample_instance_playing(startSound));
    //al_play_sample_instance(backgroundSound);

    al_start_timer(timer);
    al_start_timer(monster_pro);
}
void GameWindow::game_draw()
{
    if(window == 0){
        al_draw_bitmap(instructionbg, 0, 0, 0);
    }
    else if(window == 1){
        al_draw_bitmap(start_background, 0, 0, 0);
        //al_draw_rectangle(240, 260, 450, 320, al_map_rgb(0, 0, 0), 5);
    }
    else if(window == 2){
        draw_running_map();
    }
    else if(window == 3){
        int bestScore = readBestScore();
        if (menu->getScore() > bestScore) {
            bestScore = menu->getScore();

            // Update the best score in the file
            writeBestScore(bestScore);
        }
        end_scene_draw(menu->getScore(),bestScore);
        //game_reset();
    }

    al_flip_display();
}
int
GameWindow::game_run()
{
    int error = GAME_CONTINUE;

    if (!al_is_event_queue_empty(event_queue)) {

        error = process_event();
    }
    return error;
}

int
GameWindow::game_update()
{
    if(window == 1 || window == 0){
        al_play_sample_instance(startSound);
    }

    if(window == 2 && !losegame){
        al_play_sample_instance(backgroundSound);
        DC->get_Hero().Update();
        return GAME_CONTINUE;
    }
    if(window == 3){
        //al_play_sample_instance(failSound);
        if(!al_get_sample_instance_playing(failSound)){
            al_play_sample_instance(endSound);
        }
    }

    if(instruction_dec){
        window = 0;
        instruction_dec = false;
    }

    if(next_window){
        if(window == 1){
            //al_destroy_bitmap(start_background);
            //game_init();
            //al_destroy_bitmap(background);
            window = 2;
            next_window = false;
            al_stop_sample_instance(startSound);
        }
        else if(window == 3){
            al_stop_sample_instance(failSound);
            al_stop_sample_instance(endSound);
            end_scene_destory();
            window = 1;
            next_window = false;
            game_play();
        }else if(window == 0){
            window = 1;
            next_window = false;
        }
    }
    if(window == 2 && losegame){
        end_scene_intit();
        cha_init();
        window = 3;
        losegame = false;
        al_stop_sample_instance(backgroundSound);
        al_play_sample_instance(failSound);
    }
}

void
GameWindow::game_reset()
{
    // reset game and begin
    for(auto&& child : towerSet) {
        delete child;
    }
    towerSet.clear();
    monsterSet.clear();

    selectedTower = -1;
    lastClicked = -1;
    Coin_Inc_Count = 0;
    Monster_Pro_Count = 0;
    mute = false;
    redraw = false;
    menu->Reset();
    DC->get_Hero().Destroy();

    // stop sample instance
    al_stop_sample_instance(backgroundSound);
    al_stop_sample_instance(startSound);

    // stop timer
    al_stop_timer(timer);
    al_stop_timer(monster_pro);
}

void
GameWindow::game_destroy()
{
    game_reset();

    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_font(font);
    al_destroy_font(Medium_font);
    al_destroy_font(Large_font);

    al_destroy_timer(timer);
    al_destroy_timer(monster_pro);

    for(int i=0;i<5; i++)
        al_destroy_bitmap(tower[i]);

    al_destroy_bitmap(icon);
    al_destroy_bitmap(background);
    al_destroy_bitmap(start_background);
    al_destroy_bitmap(instructionbg);
    end_scene_destory();

    al_destroy_sample(sample);
    al_destroy_sample_instance(startSound);
    al_destroy_sample_instance(backgroundSound);
    al_destroy_sample_instance(failSound);
    al_destroy_sample_instance(endSound);
    al_destroy_sample_instance(getMoney);
    al_destroy_sample_instance(purchase);
    al_destroy_sample_instance(endgame);

    delete level;
    delete menu;
}

int
GameWindow::process_event()
{

    int instruction = GAME_CONTINUE;


    al_wait_for_event(event_queue, &event);
     if(window == 0){
        if(event.type == ALLEGRO_EVENT_TIMER) {
            if(event.timer.source == timer) {
                redraw = true;
            }
        }
        else if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN ){
            if( event.mouse.button & 1){
                if(mouse_x > window_width-150 && mouse_x < window_width-20 && mouse_y > 500 && mouse_y < 560){
                    next_window = true;
                    printf("back\n");
                }
            }
        }
        else if(event.type == ALLEGRO_EVENT_MOUSE_AXES){
            mouse_x = event.mouse.x;
            mouse_y = event.mouse.y;
        }
    }
    if(window == 1){

        if(event.type == ALLEGRO_EVENT_TIMER) {
            if(event.timer.source == timer) {
                redraw = true;
            }
        }
        else if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN ){
            if( event.mouse.button & 1){
                if(mouse_x > window_width/2-90 && mouse_x < window_width/2+180 && mouse_y > 250 && mouse_y < 350){
                    next_window = true;
                }else if(mouse_x > window_width-330 && mouse_x < window_width-245 && mouse_y > 260 && mouse_y < 330){
                    return GAME_EXIT;
                }else if(mouse_x > 240 && mouse_x < 450 && mouse_y > 260 && mouse_y < 320){
                    instruction_dec = true;
                    printf("instruction!\n");
                }
            }
        }
        else if(event.type == ALLEGRO_EVENT_MOUSE_AXES){
            mouse_x = event.mouse.x;
            mouse_y = event.mouse.y;
        }
    }


if(window == 2){
     int i;
    //xint up = 1;
     int up = 1;
      int instruction = GAME_CONTINUE;
    // offset for pause window
    int offsetX = field_width/2-200;
    int offsetY = field_height/2 - 200;
     redraw = false;
    if(event.type == ALLEGRO_EVENT_TIMER) {


        if(event.timer.source == timer) {
            redraw = true;
            updateBullets();
            if(Coin_Inc_Count == 0) {
                menu->Change_Score(Coin_Time_Gain);

            }
            Coin_Inc_Count = (Coin_Inc_Count + 1)% CoinSpeed;
            if(speed_count == 0){
                cha_update(speed++);
            }
            else cha_update(speed);
            speed_count = (speed_count +  1)%(CoinSpeed*10); //10 seconds update speed one time



        }

    }
        if(menu->check_Health() <= 0) {
            /*counting = (counting + 1);
            printf("%d ", counting);
            if(counting <= draw){
                al_play_sample_instance(endgame);

                if(al_get_timer_started(monster_pro)){
                    al_stop_timer(monster_pro);
                }else{
                    al_start_timer(monster_pro);
                }
                if(al_get_timer_started(timer)){
                    al_stop_timer(timer);
                }else{
                    al_start_timer(timer);
                }
            }else{*/
                //al_stop_sample_instance(endgame);
                speed= 0;
                losegame= true;
                //counting = 0;
            //}

       }

    else if(event.type == ALLEGRO_EVENT_KEY_DOWN) {
        switch(event.keyboard.keycode) {

            case ALLEGRO_KEY_P:
                /*TODO: handle pause event here*/
                if(al_get_timer_started(monster_pro)){
                    al_stop_timer(monster_pro);
                }else{
                    al_start_timer(monster_pro);
                }
                if(al_get_timer_started(timer)){
                    al_stop_timer(timer);
                }else{
                    al_start_timer(timer);
                }
                break;
            case ALLEGRO_KEY_M:
                mute = !mute;
                if(mute)
                    al_stop_sample_instance(backgroundSound);
                else
                    al_play_sample_instance(backgroundSound);
                break;
             case ALLEGRO_KEY_ENTER:
                    losegame = true;
                    break;
        }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        if(event.mouse.button == 1) {

            selectedTower = menu->MouseIn(mouse_x, mouse_y);
            if(selectedTower != -1)
                al_play_sample_instance(purchase);

           if(selectedTower== 0 ){
                menu->upHealth(1);
                menu->Change_Coin(-5);
                }
          else  if(selectedTower ==  1){
                menu->Change_Coin(-5);
                menu->changeGuard();
            }
           else if(selectedTower == 2){
                bullet_mode = 1;
                menu->Change_Coin(-5);
            }
        else if(selectedTower == 3){
                bullet_mode = 2;
                menu->Change_Coin(-5);
            }

        }
    }
       else if(event.type == ALLEGRO_EVENT_MOUSE_AXES){
            mouse_x = event.mouse.x;
            mouse_y = event.mouse.y;

            menu->MouseIn(mouse_x, mouse_y);

        }
         if( event.type == ALLEGRO_EVENT_KEY_DOWN ){
            key_state[event.keyboard.keycode] = true;

        }else if( event.type == ALLEGRO_EVENT_KEY_UP ){
            key_state[event.keyboard.keycode] = false;
        }
        }
//    else if(event.type == ALLEGRO_EVENT_MOUSE_AXES){
//        mouse_x = event.mouse.x;
//        mouse_y = event.mouse.y;
//
//        menu->MouseIn(mouse_x, mouse_y);
//
//    }

    if(window == 3){
       // DC->get_Hero().Update();
        if(event.type == ALLEGRO_EVENT_TIMER) {
            if(event.timer.source == timer) {
                redraw = true;
            }
        }
        else if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN ){
            if( event.mouse.button & 1){
                if(mouse_x > window_width-325 && mouse_x < window_width-225 && mouse_y > 350&& mouse_y < 400){
                    return GAME_EXIT;
                }else if(mouse_x > window_width-320 && mouse_x < window_width-10 && mouse_y > 290&& mouse_y < 330){
                    next_window = true;
                }
            }
        }
        else if(event.type == ALLEGRO_EVENT_MOUSE_AXES){
            mouse_x = event.mouse.x;
            mouse_y = event.mouse.y;
        }
    }
//     if( event.type == ALLEGRO_EVENT_KEY_DOWN ){
//        key_state[event.keyboard.keycode] = true;
//
//    }else if( event.type == ALLEGRO_EVENT_KEY_UP ){
//        key_state[event.keyboard.keycode] = false;
//    }
//}
if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {

        return GAME_EXIT;
    }
    if(redraw) {
        // update each object in game
        instruction = game_update();

        // Re-draw map
       // draw_running_map();
        game_draw();
        redraw = false;
    }

    return instruction;
}

void
GameWindow::draw_running_map()
{
    unsigned int i, j;
    //float scroll_speed = 0.1;
   // static float background_offset = 0.0;
     //background_offset += scroll_speed;
    al_clear_to_color(al_map_rgb(100, 100, 100));
    //al_draw_bitmap(background, field_width, field_height, 0);
     //background_offset += scroll_speed;
   al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background), 0, 0, 1200, 600, 0);
  // al_draw_filled_rectangle(1200, 600, 1400, 600, al_map_rgb(255, 140, 0));
   /*al_draw_scaled_bitmap(
        background,  // Bitmap to draw
        background_offset, 0,  // Source rectangle (x, y)
        al_get_bitmap_width(background) - background_offset, al_get_bitmap_height(background),  // Source width and height
        0, 0,  // Destination position (x, y)
        1200, 600,  // Destination width and height
        0  // Flags
    );*/
    cha_draw();
    DC->get_Hero().Draw(menu->checkGuard(),menu->check_Health(),&bullet_mode);
 // menu->upHealth();
    /*for(i = 0; i < field_height/40; i++)
    {
        for(j = 0; j < field_width/40; j++)
        {
            //char buffer[50];
            //sprintf(buffer, "%d", i*15 + j);
            if(level->isRoad(i*15 + j)) {
                al_draw_filled_rectangle(j*40, i*40, j*40+40, i*40+40, al_map_rgb(255, 244, 173));
            }
            //al_draw_text(font, al_map_rgb(0, 0, 0), j*40, i*40, ALLEGRO_ALIGN_CENTER, buffer);
        }
    }*/

    /*for(i=0; i<monsterSet.size(); i++)
    {
        monsterSet[i]->Draw();
    }
    /*for(std::list<Tower*>::iterator it = towerSet.begin(); it != towerSet.end(); it++)
        (*it)->Draw();*/

   /* if(selectedTower != -1){
        Tower::SelectedTower(mouse_x, mouse_y, selectedTower);
    }*/

  //  al_draw_filled_rectangle(field_width, 0, window_width, window_height, al_map_rgb(100, 100, 100));
    menu->Draw();
   // al_flip_display();
}
