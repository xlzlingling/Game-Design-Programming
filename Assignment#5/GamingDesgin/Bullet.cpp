//
//  Bullet.cpp
//  GamingDesgin
//
//  Created by Edwin Li on 2/22/15.
//  Copyright (c) 2015 Edwin Li. All rights reserved.
//

#include "Bullet.h"

Bullet::Bullet(){}
Bullet::Bullet(float set_x, float set_y,  float set_w, float set_h,float set_speed, unsigned int ssTexture):x(set_x),y(set_y), width(set_w), height(set_h), speed(set_speed),textureID(ssTexture) {}

void Bullet::Draw(float scale) {
    if(!textureID)
        textureID = LoadTexture(photo_path.c_str());
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); // use to reset, to saperate each draw
    
    GLfloat quad[] = {-width * scale , height * scale,
        -width * scale,-height * scale,
        width * scale,-height * scale,
        width * scale, height * scale};
    
    GLfloat quadUVs[] = {x, y,
        x, y+height,
        x+width, y+height,
        x+width, y};
    
    //draw array
    glVertexPointer(2, GL_FLOAT, 0, quad);
    glEnableClientState(GL_VERTEX_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glDrawArrays(GL_QUADS, 0, 4);
    glDisable(GL_TEXTURE_2D);
}
void Bullet:: Draw() {
    
    if(!textureID)
        textureID = LoadTexture(photo_path.c_str());
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glTranslatef(x, y, 0.0);
    glRotatef(rotation, 0.0, 0.0, 1.0);
    
    //counter clockwise listing of vertices
    GLfloat quad[] = {  width*-1.0f, height* 1.0f,
        width*-1.0f, height*-1.0f,
        width*1.0f,  height*-1.0f,
        width*1.0f,  height* 1.0f};
    glVertexPointer(2, GL_FLOAT, 0, quad);
    glEnableClientState(GL_VERTEX_ARRAY);
    
    GLfloat quadUVs[] = {0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0};
    glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glDrawArrays(GL_QUADS, 0, 4);
    glDisable(GL_TEXTURE_2D);
    
}

void Bullet:: Draw(GLint texture, float x, float y, float rotation) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();
    glTranslatef(x, y, 0.0);
    glRotatef(rotation, 0.0, 0.0, 1.0);
    
    GLfloat quad[] = {-0.2f, 0.2f, -0.2f, -0.2f, 0.2f, -0.2f, 0.2f, 0.2f};
    glVertexPointer(2, GL_FLOAT, 0, quad);
    glEnableClientState(GL_VERTEX_ARRAY);
    
    GLfloat quadUVs[] = {0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0};
    glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glDrawArrays(GL_QUADS, 0, 4);
    glDisable(GL_TEXTURE_2D);
    
}
GLuint Bullet:: LoadTexture(const char *image_path) {
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

void Bullet:: Updateup(float elapsed){
    y += 10 * elapsed * speed;
}
void Bullet:: Updatedown(float elapsed){
    y -= 5 * elapsed * speed;
}

void Bullet:: UpdateHorizontal(float elapsed, int direction){
    x = x + direction* 5 * elapsed * speed;
}
