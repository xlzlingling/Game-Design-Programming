//
//  SheetSpriteEntity.cpp
//  NYUCodebase
//
//  Created by Edwin Li on 2/19/15.
//  Copyright (c) 2015  Edwin Li. All rights reserved.
//

#include "SheetSpriteEntity.h"

SheetSpriteEntity::SheetSpriteEntity(){}
SheetSpriteEntity::SheetSpriteEntity(const char * image_path): set_photo_path(image_path),textureID(LoadTexture(image_path)) {
}
SheetSpriteEntity::SheetSpriteEntity(unsigned int tID, float set_u, float set_v, float w, float h){
    textureID = tID;
    u = set_u;
    v = set_v;
    width = w;
    height = h;
}


void SheetSpriteEntity::Draw(float scale) {
    if(!textureID)
       textureID = LoadTexture(set_photo_path.c_str());
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); // use to reset, to saperate each draw
    
    GLfloat quad[] = {-width * scale , height * scale,
                       -width * scale,-height * scale,
                        width * scale,-height * scale,
                        width * scale, height * scale};
    glVertexPointer(2, GL_FLOAT, 0, quad);
    glEnableClientState(GL_VERTEX_ARRAY);
    
    GLfloat quadUVs[] = {u, v,
                         u, v+height,
                         u+width, v+height,
                         u+width, v};
    
    glTranslatef(x, y, 0.0);
    glRotatef(rotation, 0.0, 0.0, 1.0);
    //draw array
    glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glDrawArrays(GL_QUADS, 0, 4);
    glDisable(GL_TEXTURE_2D);
}

GLuint SheetSpriteEntity:: LoadTexture(const char *image_path) {
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
