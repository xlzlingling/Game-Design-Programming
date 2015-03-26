//
//  Entity.h
//  NYUCodebase
//
//  Created by Edwin Li on 2/16/15.
//  Copyright (c) 2015 Edwin Li. All rights reserved.
//
#ifndef NYUCodebase_Entity_h
#define NYUCodebase_Entity_h
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <string>
#define FIXED_TIMESTEP 0.0166666f

typedef struct {
    float x;
    float y;
    float r;
    float g;
    float b;
} Vertex2D;

class Entity {
private:
GLuint LoadTexture(const char* image_path);
public:
    Entity();
    Entity(float set_x, float set_y, float set_u, float set_v, float set_w, float set_h, bool set_isStatic,float set_scale,  unsigned int ssTexture, bool set_visiable);
	void Draw();
    void Draw(GLint texture, float x, float y, float rotation);
    
	float x;
	float y;
    float u;
    float v;
    float angle;
	float width;
	float height;
	float rotation;
    float scale;
    float lerp(float v0, float v1, float t);
    
    GLint textureID;
    std::string photo_path;
  //  SheetSpriteEntity sprite;
  //  SheetSpriteEntity* sprite_ptr;

    float movement_speed;
    int *gridX;
    int *gridY;
    int facing;
    int score;
    int hp;
	

    void Update(float elapsed);
    void Render();
    void FixedUpdate();
    void resetCollision();
    
    float velocity_x;
    float velocity_y;
    float acceleration_x;
    float acceleration_y;
    float friction_x;
    float friction_y;
    float mass;
    float top();
    float bottom();
    float left();
    float right();
    
    bool alive;
    bool visiable;
    bool isStatic;
    bool enableCollisions;
    bool collidedTop;
    bool collidedBottom;
    bool collidedLeft;
    bool collidedRight;
    bool collidedWithX(Entity* object);
    bool collidedWithY(Entity* object);
    bool interactTop;
    bool interactBottom;
    bool interactLeft;
    bool interactRight;
    bool interactWithX(Entity* object);
    bool interactWithY(Entity* object);
};

#endif
