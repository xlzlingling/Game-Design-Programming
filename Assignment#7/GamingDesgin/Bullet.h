//
//  Bullet.h
//  GamingDesgin
//
//  Created by Edwin Li on 2/22/15.
//  Copyright (c) 2015 Edwin Li. All rights reserved.
//

#ifndef __GamingDesgin__Bullet__
#define __GamingDesgin__Bullet__

#include <iostream>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <string>

class Bullet {
private:
	GLuint LoadTexture(const char* image_path);
public:
    Bullet();
    Bullet(float set_x, float set_y,  float set_w, float set_h,float set_speed, unsigned int ssTexture);
	void Draw();
    void Draw(GLint texture, float x, float y, float rotation);
    void Draw(float scale);
    
    void shootBullet() ;
    bool shouldRemoveBullet(Bullet bullet);
    void Update(float elapsed);
    void Updateup(float elapsed);
    void Updatedown(float elapsed);
    void UpdateHorizontal(float elapsed, int direction);
	float x;
	float y;
	float rotation;
	GLint textureID;
    std::string photo_path;
    
    bool visible;
    float direction;
	float angle;
	float width;
	float height;
	float speed;//movement_speed
    
    
    
};

#endif /* defined(__GamingDesgin__Bullet__) */
