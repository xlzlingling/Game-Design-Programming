//
//  TextEntity.h
//  GamingDesgin
//
//  Created by Edwin Li on 2/23/15.
//  Copyright (c) 2015 Edwin Li. All rights reserved.
//

#ifndef __GamingDesgin__TextEntity__
#define __GamingDesgin__TextEntity__
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

class TextEntity {
private:
	GLuint LoadTexture(const char* image_path);
    GLuint fontTexture;
public:
    TextEntity();
    TextEntity(unsigned int tID, float set_x, float set_y, float w, float h);
    
	void DrawText();
    void DrawText(int fontTexture, std::string text, float size, float spacing, float r, float g, float b, float a);
	float x;
	float y;
    float r, g, b, a;
    std:: string text;
    float size;
    float spacing;
    
	float set_rotation;
	GLint textureID;
    std::string set_photo_path;
    
	float width;
	float height;
    
};

#endif /* defined(__GamingDesgin__TextEntity__) */
