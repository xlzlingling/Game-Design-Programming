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
#include <vector>
#include "TextEntity.h"
#include <SDL_mixer.h>
#include <ctime>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;


#define MAX_ENEMY 20
#define Gravity (-1.0f)
#define PI 3.14159265339
//60 FPS (1.0f/60.0f)
#define FIXED_TIMESTEP 0.0166666f
#define MAX_TIMESTEPS 6
#define TILE_SIZE 0.075f
#define SPRITE_COUNT_X 16
#define SPRITE_COUNT_Y 8
#define WORLD_OFFSET_X 0.0f
#define WORLD_OFFSET_Y 0.0f
#define MAX_BULLETS 30

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
    
    // tiled
    bool readHeader(std::ifstream &stream);
    bool readLayerData(std::ifstream &stream);
    bool readEntityData(std::ifstream &stream);
    void placeEntity(string type, float x, float y);
    void drawTileMap();
    
    bool isSolid(unsigned char tile);
    
    void worldToTileCoordinates(float worldX, float worldY, int* gridX, int* gridY);
    float checkGridCollisionY(float x, float y);
    float checkGridCollisionX(float x, float y);
    void LevelCollisionY(Entity* entity);
    void LevelCollisionX(Entity* entity);
    
    void DrawText(int fontTexture,std:: string text, float size, float spacing, float r, float g, float b, float a,float x, float y) ;
    void explore(float elapsed);
    
    float mapValue(float value, float srcMin, float srcMax, float dstMin, float dstMax);
    float easeOut(float from, float to, float time);
    float easeOutElastic(float from, float to, float time);
private:
    GLuint LoadTexture(const char *image_path);
    bool done;
    float lastFrameTicks;
    float timer,menu_timer,timer_tweening;
    float timeLeft;
    SDL_Window* displayWindow;
    
    
    std::vector<Entity*> entities;
    std::vector<Entity*> walls;
    std::vector<Bullet*> bullets;
    TextEntity end, end2, start, start2, some_useless;
    
    
    Mix_Chunk *sound_crash;
    Mix_Chunk *sound_jump;
    
    Mix_Music *music;
    
    float translateX;
    float translateY;
    float tweening_time;
    //float tweening_value;
    float tweening_Start;
    float tweening_End;
    
    int mapWidth;
	int mapHeight;
    unsigned char** levelData;
    int gridX, gridY;
   // int score_point;
    int state, enemy_counter;
    unsigned int spriteSheetTexture;
    unsigned int textSheet;
    //for screen shake effect
    float screenShakeValue ;
	float screenShakeSpeed ;
    float screenShakeIntensity;
    float shakeStart;
	float shakeEnd;
    
  };


#endif
