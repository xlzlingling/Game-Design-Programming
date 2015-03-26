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

#define MAX_ENEMY 20
#define Gravity (-3.0f)
#define PI 3.14159265339
//60 FPS (1.0f/60.0f)
#define FIXED_TIMESTEP 0.0166666f
#define MAX_TIMESTEPS 6

enum GameState { STATE_MAIN_MENU, STATE_GAME_LEVEL,STATE_GAME_OVER };
class ClassDemoApp {
public:
    ClassDemoApp();
    ~ClassDemoApp();
    void Init();
    bool UpdateAndRender();
    void Render();
    void Update(float elapsed);
    
    bool boundarycheck_x(Entity& p);
    bool boundarycheck_y(Entity& p);
   
    void resetCollision();
    void creatMoreEnemy(unsigned int& spriteSheetTexture);
    float lerp(float v0, float v1, float t);
    
    void mainMenuRender();
    void gameRender();
    void GameoverRender();
    
    void mainMenuUpdate(float elapsed);
    void gameUpdate(float elapsed);
    void GameoverUpdate(float elapsed);
    
    
    void DrawText(int fontTexture,std:: string text, float size, float spacing, float r, float g, float b, float a,float x, float y) ;
    void explore(float elapsed);
private:
    GLuint LoadTexture(const char *image_path);
    bool done;
    float lastFrameTicks;
    float timer,menu_timer;
    SDL_Window* displayWindow;
    
    
    std::vector<Entity*> entities;
    std::vector<Entity*> walls;
    std::vector<Entity*> example;
    TextEntity end, end2, start, start2, some_useless;
   // int score_point;
    int state, enemy_counter;
    unsigned int spriteSheetTexture;
  };


#endif
