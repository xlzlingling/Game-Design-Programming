//
//  ClassDemoApp.cpp
//  NYUCodebase
//
//  Created by Edwin Li on 2/19/15.
//  Copyright (c) 2015  Edwin Li. All rights reserved.
//

#include "ClassDemoApp.h"
#include <ctime>
#include <iostream>


Bullet  bullets[MAX_BULLETS];//player bullet
Bullet  ebullets[MAX_ENEMY_BULLETS];// enemy bullet
Bullet  bbullets[MAX_BOSS_BULLETS]; // boss bullet

ClassDemoApp:: ClassDemoApp() {
    Init();
    done = false;
    lastFrameTicks = 0.0f;
}

void ClassDemoApp::Init() {
    SDL_Init(SDL_INIT_VIDEO);
    displayWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED,
                                     SDL_WINDOWPOS_CENTERED, 320, 568, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);
    
    glViewport(0, 0, 320, 568);
    glMatrixMode(GL_PROJECTION_MATRIX);
    glOrtho(-1.0, 1.0, -1.775, 1.775, -1.0, 1.0);
    
    background.photo_path = "background.png";
    background.x = 0;
    background.y = 0;
    background.width = 1.0;
    background.height = 1.0;

    pship.photo_path = "pShip_blue.png";
    pship.x = 0;
    pship.y = -0.8f;
    pship.width = 0.1f;
    pship.height = 0.05f;
    pship.movement_speed = 0.75f;
    pship.hp = 3;
    
    hit_effect.photo_path = "laserBlue10.png";
    hit_effect.x = 2;
    hit_effect.y = -1.8f;
    hit_effect.width = 0.03f;
    hit_effect.height = 0.02f;
    
    for(int i=0; i < MAX_BULLETS; i++){
        bullets[i].photo_path = "laserBlue13.png";
        bullets[i].width = 0.02f;
        bullets[i].height = 0.02f;
        bullets[i].speed = 0.1f;
    }
   
    for(int i=0; i < MAX_ENEMY_BULLETS; i++){
        ebullets[i].photo_path = "laserRed12.png";
        ebullets[i].width = 0.02f;
        ebullets[i].height = 0.02f;
        ebullets[i].speed = 0.05f;
        ebullets[i].x = 2.0f;
    }
    
    for(int i=0; i < MAX_BOSS_BULLETS; i++){
        bbullets[i].photo_path = "laserRed12.png";
        bbullets[i].width = 0.03f;
        bbullets[i].height = 0.03f;
        bbullets[i].speed = 0.075f;
        bbullets[i].x = 2.0f;
    }
    
    
    //list 1 enemy
    for(int i =0 ; i< MAX_ENEMY ; i++){
         ssTexture[i]= LoadTexture("sheet.png");
        srand(unsigned (time(0)));
        if(i%5 != 0){
            enemylist1[i] =  SheetSpriteEntity(ssTexture[i], 222.0f/1024.0f, 0.0f/1024.0f, 103.0f/1024.0f, 84.0f/1024.0f);
            enemylist1[i].speed = 0.15f;
            enemylist1[i].hp = 5;
            enemylist1[i].worth = 50; //score point
        }
        else{
            enemylist1[i] =  SheetSpriteEntity(ssTexture[i], 518.0f/1024.0f, 409.0f/1024.0f, 82.0f/1024.0f, 84.0f/1024.0f);
            enemylist1[i].speed = 0.2f;
            enemylist1[i].hp = 2;
            enemylist1[i].worth = 100; //score point
        }
        if (i <=1)
            enemylist1[i].y = 2.5;
        else
            enemylist1[i].y = i+1.5;
        
            enemylist1[i].x = (random() % 16 -8)* 0.1;
            enemylist1[i].scale =0.7f;
    }
    //list 2 enemy
    for(int i =0 ; i< MAX_ENEMY*2 ; i++){
        ssTexture2[i]= LoadTexture("sheet.png");
        srand(unsigned (time(0)));
        if(i%5 != 0){
            enemylist2[i] =  SheetSpriteEntity(ssTexture2[i], 425.0f/1024.0f, 384.0f/1024.0f, 93.0f/1024.0f, 84.0f/1024.0f);
            enemylist2[i].speed = 0.1f;
            enemylist2[i].hp = 1;
            enemylist2[i].worth = 10;
        }
        else{
            enemylist2[i] =  SheetSpriteEntity(ssTexture2[i], 120.0f/1024.0f, 520.0f/1024.0f, 104.0f/1024.0f, 84.0f/1024.0f);
            enemylist2[i].speed = 0.15f;
            enemylist2[i].hp = 5;
            enemylist2[i].worth = 30;
        }
        enemylist2[i].y = (i/5)+1.8;
        enemylist2[i].x = (random() % 16 -8) * 0.1;
        enemylist2[i].scale = 0.7f;
    }
    
    // boss
    ssTextureBoss = LoadTexture("sheet.png");
    boss = SheetSpriteEntity(ssTextureBoss, 505.0f/1024.0f, 898.0f/1024.0f, 91.0f/1024.0f, 91.0f/1024.0f);
    boss.speed = 0.2f;
    boss.y = MAX_ENEMY*1.25f;
    boss.x = 0;
    boss.hp = 50;
    boss.worth = 5000;
    boss.scale = 4.0f;
   
    score.set_photo_path= "font1.png";
	score.a = 1.0;
	score.r = 1.0;
	score.g = 1.0;
	score.b = 1.0;
	score.y = 0.9;
	score.x = 0.0;
	score.size = 0.1f;
	score.spacing = -0.05;
    score.text = "score:"+std::to_string(pship.score);
    //text_contant = "one";
    //score.text = "Start!";
    
    hp.set_photo_path= "font1.png";
	hp.a = 1.0;
	hp.r = 1.0;
	hp.g = 1.0;
	hp.b = 1.0;
	hp.y = 0.9;
	hp.x = -0.9;
	hp.size = 0.1f;
	hp.spacing = -0.05;
    hp.text = "HP:"+std::to_string(pship.hp);
    
    
    end.set_photo_path ="font1.png";
    end.a = 1.0;
	end.r = 1.0;
	end.g = 1.0;
	end.b = 1.0;
	end.y = 0.0;
	end.x = -0.7;
    end.size = 0.1f;
	end.spacing = -0.05;
    end.text = "Game OVER! Press ESC to quit.";
    
    start.set_photo_path ="font1.png";
    start.a = 1.0;
	start.r = 1.0;
	start.g = 1.0;
	start.b = 1.0;
	start.y = 0.0;
	start.x = -0.8;
    start.size = 0.1f;
	start.spacing = -0.05;
    start.text = "Let's Play! Enter any Direction Key";
    
}

ClassDemoApp::~ClassDemoApp() {
    SDL_Quit();
}

void ClassDemoApp::Render() {
    
    switch(state) {
            case STATE_MAIN_MENU:
            mainMenuRender();
            break;
        case STATE_GAME_LEVEL:
            gameRender();
            break;
        case STATE_GAME_OVER:
            overRender();
    }
    
   
    
    SDL_GL_SwapWindow(displayWindow);
}

void ClassDemoApp::mainMenuRender(){
    
    // render stuff
    glClearColor(1.0f, 1.0f, 1.0f, 0.5f); //set backgound to white
    glClear(GL_COLOR_BUFFER_BIT);//Makes background default color
    //draw stuff
    background.Draw();
    start.DrawText();

}

void ClassDemoApp::gameRender(){
    
    // render stuff
    glClearColor(1.0f, 1.0f, 1.0f, 0.5f); //set backgound to white
    glClear(GL_COLOR_BUFFER_BIT);//Makes background default color
    //draw stuff
    background.Draw();
    score.text = "score:"+ std::to_string(pship.score);
    hp.text = "HP:"+std::to_string(pship.hp);
    score.DrawText();
    hp.DrawText();
    
    boss.Draw(4.0f);
    for(int i =0; i< MAX_ENEMY ; i++)
        enemylist1[i].Draw(0.7f);
    for(int i =0; i< MAX_ENEMY*2 ; i++)
        enemylist2[i].Draw(0.7f);
    
    for(int i=0; i < MAX_BULLETS; i++){
        bullets[i].Draw();
    }
    for(int i=0; i <MAX_ENEMY_BULLETS; i++){
        ebullets[i].Draw();
    }
    for(int i=0; i <MAX_BOSS_BULLETS; i++){
        bbullets[i].Draw();
    }
    pship.Draw();
    hit_effect.Draw();
}

void ClassDemoApp::overRender(){
    
    // render stuff
    glClearColor(1.0f, 1.0f, 1.0f, 0.5f); //set backgound to white
    glClear(GL_COLOR_BUFFER_BIT);//Makes background default color
    //draw stuff
    score.text = "score:"+ std::to_string(pship.score);
    hp.text = "HP:"+std::to_string(pship.hp);
    background.Draw();
    end.DrawText();
    score.DrawText();
}

void ClassDemoApp::Update(float elapsed) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
            done = true; }
        //else if (event.type == SDL_KEYDOWN){
        //IF(event.key.keysym.scancode == SDL_SCANCODE_SPACE)){ // do something}
        //}
    }
    switch(state) {
        case STATE_MAIN_MENU:
            mainMenuUpdate(elapsed);
            break;
        case STATE_GAME_LEVEL:
            gameUpdate(elapsed);
            break;
        case STATE_GAME_OVER:
            overUpdate(elapsed);
    }
}
void ClassDemoApp::mainMenuUpdate(float elapsed) {
    const Uint8 *keys = SDL_GetKeyboardState(NULL);

    if(keys[SDL_SCANCODE_DOWN] || keys[SDL_SCANCODE_UP] ||keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_RIGHT]){
        state = 1; //exit the program
        Update(elapsed);
    }

}
void ClassDemoApp::overUpdate(float elapsed) {
    
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    
    if(keys[SDL_SCANCODE_ESCAPE])
        done = true; //exit the program
    

}

void ClassDemoApp::gameUpdate(float elapsed) {
   
        //create timer for player and enemy
    if (pb_time < 0.2f)
        pb_time += elapsed;
    else
        pb_time =0.0f;
    if (eb_time < 2.9f)
        eb_time += elapsed;
    else
        eb_time =0.0f;
    total += elapsed;
    std::cout << "Time " << total << std::endl;

    if(eb_time<1.8f){
    hit_effect.x = -2;
    hit_effect.y = -2;
    }
    
    
    
    //create keyboard input keys for user
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    float current_x = pship.x;
    float current_y = pship.y;
    
    if(keys[SDL_SCANCODE_UP] && keys[SDL_SCANCODE_LEFT]) {
            pship.y += elapsed  * pship.movement_speed;
            pship.x -= elapsed  * pship.movement_speed*1.75;
        }
        else if(keys[SDL_SCANCODE_UP] && keys[SDL_SCANCODE_RIGHT]) {
            pship.y += elapsed  * pship.movement_speed;
            pship.x += elapsed  * pship.movement_speed*1.75;
        }
        else if(keys[SDL_SCANCODE_DOWN] && keys[SDL_SCANCODE_LEFT]) {
            pship.y -= elapsed  * pship.movement_speed;
            pship.x -= elapsed  * pship.movement_speed*1.75;
        }
        else if(keys[SDL_SCANCODE_DOWN] && keys[SDL_SCANCODE_RIGHT]) {
            pship.y -= elapsed  * pship.movement_speed;
            pship.x += elapsed  * pship.movement_speed*1.75;
        }
        else if(keys[SDL_SCANCODE_UP]) {
            pship.y += elapsed  * pship.movement_speed;
        }
        else if(keys[SDL_SCANCODE_DOWN]) {
            pship.y -= elapsed  * pship.movement_speed;
        }
        else if(keys[SDL_SCANCODE_LEFT]) {
            pship.x -= elapsed  * pship.movement_speed*1.75;
        }
        else if(keys[SDL_SCANCODE_RIGHT]) {
            pship.x += elapsed  * pship.movement_speed*1.75;
        }
        if(keys[SDL_SCANCODE_ESCAPE])
            done = true; //exit the program
    if(!boundarycheck(pship)){
        pship.x = current_x;
        pship.y = current_y;
    }
   
    //update bullets
    //player
    if(pb_time >= 0.2f)
        if(keys[SDL_SCANCODE_F] )
            shootBullet( pship.x, pship.y, MAX_BULLETS);
    for(int i=0; i < MAX_BULLETS; i++)
        bullets[i].Updateup(elapsed);
    
    //enemy bullets
    if(eb_time >= 2.9f)
        for (int i=0; i < MAX_ENEMY ; i++){
            if ( enemylist1[i].y < 0.9f)
                   enemyBullet(enemylist1[i].x, enemylist1[i].y, MAX_ENEMY_BULLETS);
        }
    for (int i=0; i < MAX_ENEMY ; i++)
        if(enemylist1[i].y < 1.0f)
                 for(int i=0; i < MAX_ENEMY_BULLETS; i++)
                     ebullets[i].Updatedown(elapsed);
    //boss bullets
    if(eb_time >= 2.9f && boss.y <= 1.0f){
        bossBullet((boss.x-0.18f), boss.y, MAX_BOSS_BULLETS);
        bossBullet((boss.x+0.18f), boss.y, MAX_BOSS_BULLETS);
    }
    for(int i=0; i < MAX_BOSS_BULLETS; i++)
        bbullets[i].Updatedown(elapsed);
    

    //update enemy
    for(int i=0; i < MAX_ENEMY; i++) {
        enemylist1[i].y -= elapsed * enemylist1[i].speed;
    }
    for(int i=0; i < MAX_ENEMY*2; i++) {
        enemylist2[i].y -= elapsed * enemylist2[i].speed;
    }
    
    //for boss movement
        boss.y -= elapsed * boss.speed;
    if(boss.y <= 0.9)
        boss.speed = 0.01f;
    if(boss.y < 0.9)
        boss.speed += elapsed * 0.5f;
    if(boss.y < 0.85 && boss.y >0.8)
        boss.x -= elapsed *boss.speed*20;
    if(boss.y < 0.8 && boss.y > 0.7)
        boss.x += elapsed *boss.speed*20;
    if(boss.y < 0.7 && boss.y > 0.6)
        boss.x -= elapsed *boss.speed*20;
    if(boss.y < 0.6 && boss.y > 0.55)
        boss.x += elapsed *boss.speed*20;
    if(boss.y < 0.55 && boss.y>-0.3){
        boss.speed = 0.2f;
        boss.x = 0.0f;
    }
    if (boss.y-(boss.height/2) < -0.7) {
        done = true;
    }
    
    checkAllcollision();
    //text_contant = std::to_string(score);
    std :: cout << "Score: " << score_point << std:: endl;
}

bool ClassDemoApp::UpdateAndRender() {
    float ticks = (float)SDL_GetTicks()/1000.0f;
    float elapsed = ticks - lastFrameTicks;
    lastFrameTicks = ticks;
    
    Update(elapsed);
    Render();
    return done;
}

void ClassDemoApp::shootBullet( float x, float y,int max) {
   
    bullets[bulletIndex].visible = true;
    bullets[bulletIndex].x = x;
    bullets[bulletIndex].y = y;
    bullets[bulletIndex].angle = (float)(45 - (rand() % 90));
    bulletIndex++;
    if(bulletIndex > max-1) {
        bulletIndex = 0;
    }
}

void ClassDemoApp::enemyBullet(float x, float y, int max ) {
   
    ebullets[ebIndex].visible = true;
    ebullets[ebIndex].x = x;
    ebullets[ebIndex].y = y;
    ebullets[ebIndex].angle = (float)(45 - (rand() % 90));
    ebIndex++;
    if(ebIndex > max-1) {
        ebIndex = 0;
    }

}
void ClassDemoApp::bossBullet( float x, float y , int max){
    bbullets[bIndex].visible = true;
    bbullets[bIndex].x = x;
    bbullets[bIndex].y = y;
    bbullets[bIndex].angle = (float)(45 - (rand() % 90));
    bIndex++;
    if(bIndex > max-1) {
        bIndex = 0;
    }
}

void ClassDemoApp::checkAllcollision(){
    //check player's bullet collision --------------------------------------------------
    for (int i=0; i< MAX_ENEMY; i++) {
        if (enemylist1[i].y < 1.0f && pbulletcollision(enemylist1[i].x, enemylist1[i].y, enemylist1[i].width, enemylist1[i].height)) {
            enemylist1[i].hp --;
            if(enemylist1[i].hp == 0){
                enemylist1[i].x = 3.0f;
                pship.score += enemylist1[i].worth;
            }
        }
        //check if enemy hit on player ship collision ---------------------------------------
        if (enemylist1[i].y < 1.0f && shipCollision(enemylist1[i].x, enemylist1[i].y, enemylist1[i].width, enemylist1[i].height)) {
            std:: cout << "we get crash" << std:: endl;
            pship.hp--;
            if (pship.hp ==0) {
                state = 2;
            }
        }
    }
    for (int i=0; i< MAX_ENEMY*2; i++) {
        if (enemylist2[i].y < 1.0f && pbulletcollision(enemylist2[i].x, enemylist2[i].y, enemylist2[i].width, enemylist2[i].height)) {
            enemylist2[i].hp --;
            if(enemylist2[i].hp == 0){
                enemylist2[i].x = 3.0f;
                pship.score += enemylist2[i].worth;
            }
        }
        //check if enemy hit on player ship collision ---------------------------------------
        if (enemylist2[i].y < 1.0f && shipCollision(enemylist2[i].x, enemylist2[i].y, enemylist2[i].width, enemylist2[i].height)) {
            std:: cout << "we get crash" << std:: endl;
            //call game over
            pship.hp--;
            if (pship.hp ==0) {
                state = 2;
            }
        }
    }
    if (boss.y < 1.0f && pbulletcollision(boss.x, boss.y, boss.width/2, boss.height/2)) {
        boss.hp --;
        if(boss.hp == 0){
            boss.speed = 0.0f;
            pship.score += boss.worth;
            //call win
                state = 2;
        }
    }
    if (boss.y < 1.0f && shipCollision(boss.x, boss.y, boss.width, boss.height)) {
        std:: cout << "we get crash" << std:: endl;
        //call game over
        pship.hp--;
        if (pship.hp ==0) {
            state = 2;
        }
    }
    //check enemy's bullet collision --------------------------------------------------
    if (ebulletcollision(pship.x, pship.y, pship.width, pship.height)) {
                std:: cout << "we get hit" <<  std:: endl;
        //call game over
        pship.hp--;
        if (pship.hp ==0) {
            state = 2;
        }
    }
    if (bbulletcollision(pship.x, pship.y, pship.width, pship.height)) {
        pship.hp--;
        if (pship.hp ==0) {
            state = 2;
        }
        std:: cout << "we get hit" <<  std:: endl;
        //call game over
    }
}


bool ClassDemoApp::pbulletcollision(float ex, float ey, float ew, float eh){
    for (int i=0; i< MAX_BULLETS; i++) {
        float bxleft = bullets[i].x - (bullets[i].width*5);//* 5 to make bullet easy to ehit
        float bxright = bullets[i].x + (bullets[i].width*5);
        float bytop = bullets[i].y + (bullets[i].height);
        
        float exleft = ex - ((ew * 0.7f)/2);
        float exright = ex + ((ew * 0.7f)/2);
        float eybot = ey - ((eh * 0.7f)/2);

        if((bxleft >= exleft && bxright <=exright) || (bxleft >= exleft && bxleft <= exright) ||(bxright <= exright && bxright >= exleft)  ||(bxleft <= exleft && bxright >=exright)){
            if (bytop <=0.95 && bytop >= eybot){
                bullets[i].x =5.0f;
                hit_effect.x = ex;
                hit_effect.y = ey;
                return true;
                std::cout << "bullet hit elist1" << std::endl;
                //call explore animation
            }
        }
    }
    return false;
}

bool ClassDemoApp::ebulletcollision(float px, float py, float pw, float ph){
    for (int i=0; i< MAX_ENEMY_BULLETS; i++) {
        float ebxleft = ebullets[i].x - (ebullets[i].width*2);//* 2 to make bullet easy to ehit
        float ebxright = ebullets[i].x + (ebullets[i].width*5);
        float ebytop = ebullets[i].y + (ebullets[i].height);
        float ebybot = ebullets[i].y - (ebullets[i].height);

        
        float pxleft = px - (pw /2);
        float pxright = px + (pw /2);
        float pybot = py - (ph /2);
        float pytop = py + (ph /2);
        
        if((ebxleft >= pxleft && ebxright <=pxright) || (ebxleft >= pxleft && ebxleft <= pxright) ||(ebxright <= pxright && ebxright >= pxleft)  ||(ebxleft <= pxleft && ebxright >=pxright)){
            if (ebytop <=0.95)
                if((ebybot <= pytop && ebybot >=pybot) || (ebytop <=pytop && ebytop >=pybot) ||(ebytop <= pytop && ebybot >= pybot) ){
                    ebullets[i].x = 6.0f;
                return true;
                //player is hit
            }
        }
    }
    return false;
}

bool ClassDemoApp::bbulletcollision(float px, float py, float pw, float ph){
    for (int i=0; i< MAX_ENEMY_BULLETS; i++) {
        float ebxleft = bbullets[i].x - (bbullets[i].width*2);//* 2 to make bullet easy to ehit
        float ebxright = bbullets[i].x + (bullets[i].width*5);
        float ebytop = bbullets[i].y + (bbullets[i].height);
        float ebybot = bbullets[i].y - (bbullets[i].height);
        
        
        float pxleft = px - (pw /2);
        float pxright = px + (pw /2);
        float pybot = py - (ph /2);
        float pytop = py + (ph /2);
        
        if((ebxleft >= pxleft && ebxright <=pxright) || (ebxleft >= pxleft && ebxleft <= pxright) ||(ebxright <= pxright && ebxright >= pxleft)  ||(ebxleft <= pxleft && ebxright >=pxright)){
            if (ebytop <=0.95)
                if((ebybot <= pytop && ebybot >=pybot) || (ebytop <=pytop && ebytop >=pybot) ||(ebytop <= pytop && ebybot >= pybot) ){
                    bbullets[i].x = 6.0f;
                    return true;
                    //player is hit
                }
        }
    }
    return false;
}


bool ClassDemoApp::shipCollision(float ex, float ey, float ew, float eh){
    float pxleft = pship.x - (pship.width/2);
    float pxright = pship.x + (pship.width/2);
    float pytop = pship.y + (pship.height/2) ;
    float pybot = pship.y - (pship.height/2);

    float exleft = ex - (ew /2);
    float exright = ex + (ew /2);
    float eybot = ey - (eh /2);
    float eytop = ey + (eh /2);
    
    if ((pxleft >= exleft && pxright <= exright) || (pxleft >= exleft && pxleft <= exright) || (pxright <= exright && pxright >= exleft)) {
        if ((pybot >= eybot && pytop <= eytop) || (pybot >= eybot && pybot <= eytop) || (pytop <= eytop && pytop >= eybot)) {
            return true;
        }
    }
    return false;
}


bool ClassDemoApp:: boundarycheck(Entity& ship){
    if (ship.x > 0.9 || ship.x < -0.9) {
       return false; //hit the side
    }
    if (ship.y > 0.9 || ship.y < -0.9) {
        return false;// hit the top/bottom
    }
    return true;
}

GLuint ClassDemoApp:: LoadTexture(const char *image_path) {
    SDL_Surface *surface = IMG_Load(image_path);
    
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, surface->w, surface->h, 0, GL_BGRA, GL_UNSIGNED_BYTE,surface->pixels);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    SDL_FreeSurface(surface);
    return textureID;
}
