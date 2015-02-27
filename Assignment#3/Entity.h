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
    Entity(float x,float y,float width,float height,float movement_speed, std::string photo_path);
	void Draw();
    void Draw(GLint texture, float x, float y, float rotation);
	float x;
	float y;
	float rotation;
	GLint textureID;
    std::string photo_path;
    
	float angle;
	float width;
	float height;
	float movement_speed;
    
    int score;
    int hp;
};

#endif
