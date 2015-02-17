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
	void Draw();
	float set_x;
	float set_y;
	float set_rotation;
	GLint textureID;
    char *photo_path;
    
	float angle;
	float width;
	float height;
	float movement_speed;
    
};

void Entity:: Draw() {
    if(!textureID)
        textureID = LoadTexture(photo_path);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glTranslatef(set_x, set_y, 0.0);
    glRotatef(set_rotation, 0.0, 0.0, 1.0);
    
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


GLuint Entity:: LoadTexture(const char *image_path) {
    SDL_Surface *surface = IMG_Load(image_path);
    
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, surface->w, surface->h, 0, GL_BGRA, GL_UNSIGNED_BYTE,surface->pixels);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    SDL_FreeSurface(surface);
    return textureID;
}

#endif
