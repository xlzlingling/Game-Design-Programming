//
//  SheetSpriteEntity.h
//  NYUCodebase
//
//  Created by Edwin Li on 2/19/15.
//  Copyright (c) 2015 Edwin Li. All rights reserved.
//

#ifndef NYUCodebase_SheetSpriteEntity_h
#define NYUCodebase_SheetSpriteEntity_h
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <string>

class SheetSpriteEntity {
private:
	GLuint LoadTexture(const char* image_path);
public:
    SheetSpriteEntity();
    SheetSpriteEntity(const char * image_path);
    SheetSpriteEntity(unsigned int textureID, float set_u, float set_v, float width, float height);
    void Draw(float scale);
    float x;
    float y;
	float u;
	float v;
    float scale;
	float rotation;
    unsigned int textureID;
    std::string set_photo_path;
    
	float angle;
	float width;
	float height;
    float speed;
    
    int spriteTexture;
    int index;
    int spriteCountX;
    int spriteCountY;
    int hp;         
    int worth;    //score point
};



#endif
