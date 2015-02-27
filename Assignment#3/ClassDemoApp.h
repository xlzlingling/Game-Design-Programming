//
//  ClassDemoApp.h
//  NYUCodebase
//
//  Created by Edwin Li on 2/19/15.
//  Copyright (c) 2015 Edwin Li. All rights reserved.
//

#ifndef NYUCodebase_ClassDemoApp_h
#define NYUCodebase_ClassDemoApp_h
#include "Entity.h"
#include "SheetSpriteEntity.h"
#include "Bullet.h"
#include <string>
#include <iostream>
#include <vector>
#include "TextEntity.h"

#define MAX_BULLETS 30
#define MAX_ENEMY 20
#define MAX_ENEMY_BULLETS 10
#define MAX_BOSS_BULLETS 50
#define PI 3.14159265339


enum GameState { STATE_MAIN_MENU, STATE_GAME_LEVEL,STATE_GAME_OVER };
class ClassDemoApp {
public:
    ClassDemoApp();
    ~ClassDemoApp();
    void Init();
    bool UpdateAndRender();
    void Render();
    void Update(float elapsed);
    void shootBullet( float x, float y , int max);
    void enemyBullet( float x, float y , int max);
    void bossBullet( float x, float y , int max);
    
    void mainMenuRender();
    void gameRender();
    void overRender();
    
    void mainMenuUpdate(float elapsed);
    void gameUpdate(float elapsed);
    void overUpdate(float elapsed);
    
    bool boundarycheck(Entity& ship);
    bool pbulletcollision(float ex, float ey, float ew, float eh);
    bool ebulletcollision(float px, float py, float pw, float ph);
    bool bbulletcollision(float px, float py, float pw, float ph);
    bool shipCollision(float ex, float ey, float ew, float eh);
    void checkAllcollision();
    void DrawText(int fontTexture,std:: string text, float size, float spacing, float r, float g, float b, float a,float x, float y) ;
    void explore(float elapsed);
private:
    GLuint LoadTexture(const char *image_path);
    bool done;
    float lastFrameTicks;
    SDL_Window* displayWindow;
    
    GLuint  ssTexture[MAX_ENEMY],
            ssTexture2[MAX_ENEMY*2],
            ssTextureBoss,
            ttexture;
    
    SheetSpriteEntity enemylist1[MAX_ENEMY];
    SheetSpriteEntity enemylist2[MAX_ENEMY*2];
    SheetSpriteEntity boss;
    
    Entity background;
    Entity  pship;
    Entity  hit_effect;
    TextEntity score,
                end,
                start,
                hp,
                some_useless;
    int score_point;
    int state;

    int bulletIndex ,bIndex , ebIndex;
    float pb_time , eb_time, total ;
   
};


#endif
