//
//  Entity.cpp
//  NYUCodebase
//
//  Created by Edwin Li on 2/19/15.
//  Copyright (c) 2015  Edwin Li. All rights reserved.
//

#include "Entity.h"
#include <iostream>
Entity::Entity(){}
Entity::Entity(float set_x, float set_y, float set_u, float set_v, float set_w, float set_h, bool set_isStatic, float set_scale, unsigned int ssTexture , bool set_visiable)
:x(set_x),y(set_y),u(set_u),v(set_v),width(set_w),height(set_h),isStatic(set_isStatic),scale(set_scale),textureID(ssTexture),visiable(set_visiable){
    alive = false;
    velocity_x = 0.0f;
    velocity_y = 0.0f;
    acceleration_x = 0.0f;
    acceleration_y = 0.0f;
    friction_x = 0.0f;
    friction_y = 0.0f;
    facing = 1;
    collidedTop = false;
    collidedTop = false;
    collidedLeft = false;
    collidedRight = false;
    
    interactTop = false;
    interactBottom = false;
    interactLeft = false;
    interactRight =false;
}

void Entity:: Draw() {
    if(!textureID ){
       textureID = LoadTexture(photo_path.c_str() );
    }    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);
        
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glTranslatef(x, y, 0.0);
    
    //counter clockwise listing of vertices
    GLfloat quad[] = {  scale*facing*width*-1.0f, scale*height* 1.0f,
                        scale*facing*width*-1.0f, scale*height*-1.0f,
                        scale*facing*width*1.0f,  scale*height*-1.0f,
                        scale*facing*width*1.0f,  scale*height* 1.0f};
    glVertexPointer(2, GL_FLOAT, 0, quad);
    glEnableClientState(GL_VERTEX_ARRAY);
    
    GLfloat quadUVs[] = {u      , v,
                         u      , v+height,
                         u+width, v+height,
                         u+width, v
                        };
    glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glDrawArrays(GL_QUADS, 0, 4);
    glDisable(GL_TEXTURE_2D);
    
}

void Entity:: Draw(GLint texture, float x, float y, float rotation) {
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

GLuint Entity:: LoadTexture(const char *image_path) {
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

void Entity::FixedUpdate(){
    resetCollision();
    if(velocity_x > 0) facing = 1;
    else if  (velocity_x < 0)   facing = -1;
    velocity_x = lerp(velocity_x, 0.0f, FIXED_TIMESTEP * friction_x);
	velocity_x += acceleration_x * FIXED_TIMESTEP;
	velocity_y += acceleration_y * FIXED_TIMESTEP;
}

bool Entity::collidedWithX(Entity* object){
    collidedLeft = false;
    collidedRight = false;
    //for some reason the image on screen get stretch to double, so i have to times 3 of height, and double the width
    float obot = object->y - (object->height/2) * 3 * object->scale;
    float otop = object->y + (object->height/2) * 3 * object->scale;
    float oleft = object->x - (object->width/2) * 2 * object->scale;
    float oright = object->x + (object->width/2) * 2* object->scale;
    
    if ((left() < oright && left() > oleft) &&
        ((top() < otop && top() > obot)||(bottom() < otop && bottom() > obot)||(top()>otop && bottom()<obot)))
        collidedLeft = true;
    if ((right() > oleft && right() < oright)&&
        ((top() < otop && top() > obot)||(bottom() < otop && bottom() > obot)||(top()>otop && bottom()<obot)))
        collidedRight = true;
    return (collidedLeft || collidedRight);
}

bool Entity::collidedWithY(Entity* object){
    collidedBottom = false;
    collidedTop = false;
    //for some reason the image on screen get stretch to double, so i have to times 3 of height, and double the width
    float obot = object->y - (object->height/2) * 3 * object->scale;
    float otop = object->y + (object->height/2) * 3 * object->scale;
    float oleft = object->x - (object->width/2) * 2 * object->scale;
    float oright = object->x + (object->width/2) * 2 * object->scale;
    
    if((top() > obot && bottom() < obot) &&
       ((left() > oleft && left() < oright)||(right() < oright && right() > oleft)))
        collidedTop = true;
    if ((bottom() < otop && bottom() > obot) &&
        ((left() > oleft && left()< oright)||(right() < oright && right() > oleft)))
        collidedBottom = true;
    return (collidedTop || collidedBottom );
}

bool Entity::interactWithX(Entity* object){
    interactLeft = false;
    interactRight =false;
    //for some reason the image on screen get stretch to double, so i have to times 3 of height, and double the width
    
    float obot = object->y - (object->height/2) * 3 * object->scale;
    float otop = object->y + (object->height/2) * 3 * object->scale;
    float oleft = object->x - (object->width/2) * 2 * object->scale;
    float oright = object->x + (object->width/2) * 2 * object->scale;
    
    if(interactBottom == false){
    if ((left() < oright && left() > oleft) &&
        ((top() < otop && top() > obot)||(bottom() < otop && bottom() > obot)))
       return interactLeft = true;
    if ((right() > oleft && right() < oright)&&
        ((top() < otop && top() > obot)||(bottom() < otop && bottom() > obot)))
       return  interactLeft = true;
    }
    return (interactLeft || interactLeft );
}

bool Entity::interactWithY(Entity* object){
    interactTop = false;
    interactBottom = false;
    
    //for some reason the image on screen get stretch to double, so i have to times 3 of height, and double the width
    float obot = object->y - (object->height/2) * 3 * object->scale;
    float otop = object->y + (object->height/2) * 3 * object->scale;
    float oleft = object->x - (object->width/2) * 1 * object->scale;
    float oright = object->x + (object->width/2) * 1 * object->scale;
    
    if ((bottom() < otop && bottom() > obot) &&
        ((left() > oleft && left()< oright)||(right() < oright && right() > oleft)))
        return interactBottom = true;
    if((top() > obot && bottom() < obot) &&
       ((left() > oleft && left() < oright)||(right() < oright && right() > oleft)))
        return interactTop = true;
    
    return (interactTop|| interactBottom);
}



void Entity::resetCollision(){
    collidedTop = false;
    collidedBottom = false;
    collidedLeft = false;
    collidedRight = false;
}

float Entity::lerp(float v0, float v1, float t) {
	return (1.0 - t)*v0 + t*v1;
}

float Entity::top(){ return  y + (height /2);}
float Entity::bottom(){ return  y - (height/2);}
float Entity::left(){ return  x - (width /2);}
float Entity::right(){ return  x + (width /2);}


