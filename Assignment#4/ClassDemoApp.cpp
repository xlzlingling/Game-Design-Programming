//
//  ClassDemoApp.cpp
//  NYUCodebase
//
//  Created by Edwin Li on 2/19/15.
//  Copyright (c) 2015  Edwin Li. All rights reserved.
//

#include "ClassDemoApp.h"
#include <ctime>
#include <iostream>

ClassDemoApp:: ClassDemoApp() {
    Init();
    done = false;
    lastFrameTicks = 0.0f;
}

void ClassDemoApp::Init() {
    SDL_Init(SDL_INIT_VIDEO);
    displayWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED,
                                     SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);
    
    glViewport(0, 0, 800, 600);
    glMatrixMode(GL_PROJECTION);
    glOrtho(-1.33, 1.33, -1.0, 1.0, -1.0, 1.0);
    
    spriteSheetTexture = LoadTexture("sprites.png");
    //example in the main menu page
    Entity* example_player = new Entity(-0.7, -0.7, 8.0f / 128.0f, 94.0f / 256.0f, 4.0f / 128.0f, 16.0f / 256.0f, false, 1.0f, spriteSheetTexture, true);
    example_player->acceleration_y = Gravity;
    example_player->velocity_x = 0.55;
    example_player->velocity_y = 2;
    Entity* example_enemy = new Entity( 0, -0.7f, 0.0f / 128.0f, 78.0f / 256.0f, 4.0f / 128.0f, 16.0f / 256.0f, false, 1.0f, spriteSheetTexture, true);
    example.push_back(example_player);
    example.push_back(example_enemy);
    //player
            Entity* player = new Entity(0.3f, -0.35f, 8.0f / 128.0f, 94.0f / 256.0f, 4.0f / 128.0f, 16.0f / 256.0f, false, 1.0f, spriteSheetTexture, true);
    player->enableCollisions = true;
    player->velocity_x = 0;
    player->velocity_y = 0;
    player->friction_x = 1.8;
    player->friction_y = 0;
    player->acceleration_y = Gravity;
    entities.push_back(player);
    
    //wall entities
        //bottom floor
            Entity* wall_f1_1 = new Entity(-1.25f, -0.85f, 0.0f / 128.0f, 16.0f / 256.0f, 16.0f / 128.0f, 16.0f / 256.0f, true, 1.0f, spriteSheetTexture, true);
            Entity* wall_f1_2 = new Entity(-1.0f, -0.85f, 0.0f / 128.0f, 16.0f / 256.0f, 16.0f / 128.0f, 16.0f / 256.0f, true, 1.0f, spriteSheetTexture, true);
            Entity* wall_f1_3 = new Entity(-0.75f, -0.85f, 0.0f / 128.0f, 16.0f / 256.0f, 16.0f / 128.0f, 16.0f / 256.0f, true, 1.0f, spriteSheetTexture, true);
            Entity* wall_f1_4 = new Entity(-0.5f, -0.85f, 0.0f / 128.0f, 16.0f / 256.0f, 16.0f / 128.0f, 16.0f / 256.0f, true, 1.0f, spriteSheetTexture, true);
            Entity* wall_f1_5 = new Entity(-0.25f, -0.85f, 0.0f / 128.0f, 16.0f / 256.0f, 16.0f / 128.0f, 16.0f / 256.0f, true, 1.0f, spriteSheetTexture, true);
            Entity* wall_f1_6 = new Entity( 0.5f, -0.85f, 0.0f / 128.0f, 16.0f / 256.0f, 16.0f / 128.0f, 16.0f / 256.0f, true, 1.0f, spriteSheetTexture, true);
            Entity* wall_f1_7 = new Entity( 0.75f, -0.85f, 0.0f / 128.0f, 16.0f / 256.0f, 16.0f / 128.0f, 16.0f / 256.0f, true, 1.0f, spriteSheetTexture, true);
            Entity* wall_f1_8 = new Entity( 1.0f, -0.85f, 0.0f / 128.0f, 16.0f / 256.0f, 16.0f / 128.0f, 16.0f / 256.0f, true, 1.0f, spriteSheetTexture, true);
            Entity* wall_f1_9 = new Entity( 1.25f, -0.85f, 0.0f / 128.0f, 16.0f / 256.0f, 16.0f / 128.0f, 16.0f / 256.0f, true, 1.0f, spriteSheetTexture, true);
            Entity* wall_f1_10 = new Entity( 0.25f, -0.85f, 0.0f / 128.0f, 16.0f / 256.0f, 16.0f / 128.0f, 16.0f / 256.0f, true, 1.0f, spriteSheetTexture, true);
        //second floor
            Entity* wall_f2_1 = new Entity(-0.8f, -0.35f, 0.0f / 128.0f, 16.0f / 256.0f, 16.0f / 128.0f, 16.0f / 256.0f, true, 1.0f, spriteSheetTexture, true);
            Entity* wall_f2_2 = new Entity(-0.55f, -0.35f, 0.0f / 128.0f, 16.0f / 256.0f, 16.0f / 128.0f, 16.0f / 256.0f, true, 1.0f, spriteSheetTexture, true);
            Entity* wall_f2_3 = new Entity(-0.3f, -0.35f, 0.0f / 128.0f, 16.0f / 256.0f, 16.0f / 128.0f, 16.0f / 256.0f, true, 1.0f, spriteSheetTexture, true);
            Entity* wall_f2_4 = new Entity(-0.05f, -0.35f, 0.0f / 128.0f, 16.0f / 256.0f, 16.0f / 128.0f, 16.0f / 256.0f, true, 1.0f, spriteSheetTexture, true);
            Entity* wall_f2_5 = new Entity(0.2f, -0.35f, 0.0f / 128.0f, 16.0f / 256.0f, 16.0f / 128.0f, 16.0f / 256.0f, true, 1.0f, spriteSheetTexture, true);
            Entity* wall_f2_6 = new Entity(0.45f, -0.35f, 0.0f / 128.0f, 16.0f / 256.0f, 16.0f / 128.0f, 16.0f / 256.0f, true, 1.0f, spriteSheetTexture, true);
            Entity* wall_f2_7 = new Entity(0.6f, -0.35f, 0.0f / 128.0f, 16.0f / 256.0f, 16.0f / 128.0f, 16.0f / 256.0f, true, 1.0f, spriteSheetTexture, true);
        //third floor
            Entity* wall_f3_1 = new Entity(-1.25f, 0.15f, 0.0f / 128.0f, 16.0f / 256.0f, 16.0f / 128.0f, 16.0f / 256.0f, true, 1.0f, spriteSheetTexture, true);
            Entity* wall_f3_2 = new Entity(-1.0f, 0.15f, 0.0f / 128.0f, 16.0f / 256.0f, 16.0f / 128.0f, 16.0f / 256.0f, true, 1.0f, spriteSheetTexture, true);
            Entity* wall_f3_3 = new Entity(-0.75f, 0.15f, 0.0f / 128.0f, 16.0f / 256.0f, 16.0f / 128.0f, 16.0f / 256.0f, true, 1.0f, spriteSheetTexture, true);
            Entity* wall_f3_4 = new Entity(-0.5f, 0.15f, 0.0f / 128.0f, 16.0f / 256.0f, 16.0f / 128.0f, 16.0f / 256.0f, true, 1.0f, spriteSheetTexture, true);
            Entity* wall_f3_5 = new Entity( 0.5f, 0.15f, 0.0f / 128.0f, 16.0f / 256.0f, 16.0f / 128.0f, 16.0f / 256.0f, true, 1.0f, spriteSheetTexture, true);
            Entity* wall_f3_6 = new Entity( 0.75f, 0.15f, 0.0f / 128.0f, 16.0f / 256.0f, 16.0f / 128.0f, 16.0f / 256.0f, true, 1.0f, spriteSheetTexture, true);
            Entity* wall_f3_7 = new Entity( 1.0f, 0.15f, 0.0f / 128.0f, 16.0f / 256.0f, 16.0f / 128.0f, 16.0f / 256.0f, true, 1.0f, spriteSheetTexture, true);
            Entity* wall_f3_8 = new Entity( 1.25f, 0.15f, 0.0f / 128.0f, 16.0f / 256.0f, 16.0f / 128.0f, 16.0f / 256.0f, true, 1.0f, spriteSheetTexture, true);
    //fourth floor
        Entity* wall_f4_1 = new Entity(-0.625f, 0.65f, 0.0f / 128.0f, 16.0f / 256.0f, 16.0f / 128.0f, 16.0f / 256.0f, true, 1.0f, spriteSheetTexture, true);
        Entity* wall_f4_2 = new Entity(-0.375f, 0.65f, 0.0f / 128.0f, 16.0f / 256.0f, 16.0f / 128.0f, 16.0f / 256.0f, true, 1.0f, spriteSheetTexture, true);
        Entity* wall_f4_3 = new Entity(-0.125f, 0.65f, 0.0f / 128.0f, 16.0f / 256.0f, 16.0f / 128.0f, 16.0f / 256.0f, true, 1.0f, spriteSheetTexture, true);
        Entity* wall_f4_4 = new Entity( 0.125f, 0.65f, 0.0f / 128.0f, 16.0f / 256.0f, 16.0f / 128.0f, 16.0f / 256.0f, true, 1.0f, spriteSheetTexture, true);
        Entity* wall_f4_5 = new Entity( 0.375f, 0.65f, 0.0f / 128.0f, 16.0f / 256.0f, 16.0f / 128.0f, 16.0f / 256.0f, true, 1.0f, spriteSheetTexture, true);
        Entity* wall_f4_6 = new Entity( 0.625f, 0.65f, 0.0f / 128.0f, 16.0f / 256.0f, 16.0f / 128.0f, 16.0f / 256.0f, true, 1.0f, spriteSheetTexture, true);
    
    walls.push_back(wall_f1_1);
    walls.push_back(wall_f1_2);
    walls.push_back(wall_f1_3);
    walls.push_back(wall_f1_4);
    walls.push_back(wall_f1_5);
    walls.push_back(wall_f1_6);
    walls.push_back(wall_f1_7);
    walls.push_back(wall_f1_8);
    walls.push_back(wall_f1_9);
    walls.push_back(wall_f1_10);

    //second floor
    walls.push_back(wall_f2_1);
    walls.push_back(wall_f2_2);
    walls.push_back(wall_f2_3);
    walls.push_back(wall_f2_4);
    walls.push_back(wall_f2_5);
    walls.push_back(wall_f2_6);
    walls.push_back(wall_f2_7);
    //third floor
    walls.push_back(wall_f3_1);
    walls.push_back(wall_f3_2);
    walls.push_back(wall_f3_3);
    walls.push_back(wall_f3_4);
    walls.push_back(wall_f3_5);
    walls.push_back(wall_f3_6);
    walls.push_back(wall_f3_7);
    walls.push_back(wall_f3_8);
    //fourth floor
    walls.push_back(wall_f4_1);
    walls.push_back(wall_f4_2);
    walls.push_back(wall_f4_3);
    walls.push_back(wall_f4_4);
    walls.push_back(wall_f4_5);
    walls.push_back(wall_f4_6);
    
    //side
    float w = 4.0f / 128.0f,
          h = 16.0f / 256.0f, //width and height
          u = 12.0f / 128.0f,
          v = 0.0f / 256.0f;
    
    for (int i = 0; i<16; ++i) {
        Entity* side_l = new Entity(-1.3f, 0.95f+(2*h*-i), u, v, w, h, true, 1.0f, spriteSheetTexture, true);
         walls.push_back(side_l);
         Entity* side_r = new Entity(1.3f, 0.95f-(2*h*+i), u, v, w, h, true, 1.0f, spriteSheetTexture, true);
        walls.push_back(side_r);
    }
    //top
    for(int i = 0; i<18; ++i){
        Entity* top_l = new Entity(-1.3f+(2*w*i), 0.95f, u, v, w, h, true, 1.0f, spriteSheetTexture, true);
        Entity* top_r = new Entity(1.3f-(2*w*i), 0.95f, u, v, w, h, true, 1.0f, spriteSheetTexture, true);
        walls.push_back(top_l);
        walls.push_back(top_r);

    }
    
    Entity* example = new Entity(0, -0.33f+h*2, u, v, w, h, true, 1.0f, spriteSheetTexture, true);
    walls.push_back(example);


    start.set_photo_path ="font1.png";
    start.a = 1.0;
	start.r = 1.0;
	start.g = 1.0;
	start.b = 1.0;
	start.y = 0.0;
	start.x = -0.8;
    start.size = 0.1f;
	start.spacing = -0.05;
    start.text = "Let's Play! Enter any Direction Key";
    
    start2.set_photo_path ="font1.png";
    start2.a = 1.0;
	start2.r = 1.0;
	start2.g = 1.0;
	start2.b = 1.0;
	start2.y = -0.2;
	start2.x = -0.9;
    start2.size = 0.1f;
	start2.spacing = -0.05;
    start2.text = "Jump and Step on the enemy to kill";

    
    end.set_photo_path ="font1.png";
    end.a = 1.0;
	end.r = 1.0;
	end.g = 1.0;
	end.b = 1.0;
	end.y = 0.0;
	end.x = -0.7;
    end.size = 0.1f;
	end.spacing = -0.05;
    end.text = "Game OVER! Press ESC to quit.";
    
    end2.set_photo_path ="font1.png";
    end2.a = 1.0;
	end2.r = 1.0;
	end2.g = 1.0;
	end2.b = 1.0;
	end2.y = 0.5;
	end2.x = -0.7;
    end2.size = 0.1f;
	end2.spacing = -0.05;
    end2.text = "";
}

ClassDemoApp::~ClassDemoApp() {
    SDL_Quit();
}

void ClassDemoApp::Render() {
    
    switch(state) {
            case STATE_MAIN_MENU:
            mainMenuRender();
            break;
        case STATE_GAME_LEVEL:
            gameRender();
            break;
        case STATE_GAME_OVER:
            GameoverRender();
    }
    
   
    
    SDL_GL_SwapWindow(displayWindow);
}

void ClassDemoApp::mainMenuRender(){
    // render stuff
    glClearColor(0.1f, 0.8f, 1.0f, 0.5f); //set backgound to blue
    glClear(GL_COLOR_BUFFER_BIT);//Makes background default color
    //draw stuff
    start.DrawText();
    start2.DrawText();
    for (int i =0; i< example.size(); i++){
        if(example[i]->visiable)
            example[i]->Draw();
    }

}

void ClassDemoApp::gameRender(){
    
    // render stuff
    glClearColor(1.0f, 1.0f, 1.0f, 0.5f); //set backgound to white
    glClear(GL_COLOR_BUFFER_BIT);//Makes background default color
    //draw stuff
    for (int i =0; i< walls.size(); i++)
        walls[i]->Draw();
    for (int i =0; i< entities.size(); i++){
        if(entities[i]->visiable)
            entities[i]->Draw();
    }
}

void ClassDemoApp::GameoverRender(){
    
    // render stuff
    glClearColor(1.0f, 1.0f, 1.0f, 0.5f); //set backgound to white
    glClear(GL_COLOR_BUFFER_BIT);//Makes background default color
    //draw stuff
    for (int i =0; i< walls.size(); i++)
        walls[i]->Draw();
    
    
    for (int i =0; i< entities.size(); i++){
        if(entities[i]->visiable)
            entities[i]->Draw();
    }
    end.DrawText();
    end2.DrawText();
}

void ClassDemoApp::Update(float elapsed) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
            done = true; }
        else if (event.type == SDL_KEYDOWN){
            if(event.key.keysym.scancode == SDL_SCANCODE_UP || event.key.keysym.scancode == SDL_SCANCODE_SPACE){
                // do something
                if(entities[0]->collidedBottom)//only jump when bottom collids
                    entities[0]->velocity_y = 2.0f;
            }
            if(event.key.keysym.scancode == SDL_SCANCODE_F){
                // do something
                entities[0]->velocity_y = 0.15f;
            }
        }
    }
    switch(state) {
        case STATE_MAIN_MENU:
            mainMenuUpdate(elapsed);
            break;
        case STATE_GAME_LEVEL:
            gameUpdate(elapsed);
            break;
        case STATE_GAME_OVER:
            GameoverUpdate(elapsed);
    }
}
void ClassDemoApp::mainMenuUpdate(float elapsed) {
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    if(keys[SDL_SCANCODE_ESCAPE])
        done = true; //exit the program
    menu_timer += elapsed;
    if (menu_timer >3) {
        if(keys[SDL_SCANCODE_DOWN] || keys[SDL_SCANCODE_UP] ||keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_RIGHT]|| keys[SDL_SCANCODE_KP_ENTER]){
            state = 1; //go the game level
            Update(elapsed);
        }
        
        float current_y = example[0]->y;
        float current_x = example[0]->x;
        
        example[0]->FixedUpdate();
        example[0]->x += example[0]->velocity_x * FIXED_TIMESTEP;
        example[0]->y += example[0]->velocity_y * FIXED_TIMESTEP;
        
        if(example[0]->x >=0){
            example[0]->x = current_x;
            example[0]->velocity_x = 0;
        }
        if(example[0]->y-(example[0]->height/2) <= -0.7 && example[0]->x > -0.1){
            example[0]->y = current_y;
            example[1]->visiable = false;
        }
    }

}
void ClassDemoApp::GameoverUpdate(float elapsed) {
    
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    
    if(keys[SDL_SCANCODE_ESCAPE])
        done = true; //exit the program
}

void ClassDemoApp::gameUpdate(float elapsed) {
   
    //create keyboard input keys for user
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    timer += elapsed;
    if (timer > 5) {
        creatMoreEnemy(spriteSheetTexture);
        timer = 0;
    }
    
    float current_x = entities[0]->x;
    
    
    if(keys[SDL_SCANCODE_LEFT]  ) {
        entities[0]->acceleration_x =-2.0f;
    }
    else if( keys[SDL_SCANCODE_RIGHT] ) {
        entities[0]->acceleration_x = 2.0f;
    }
    else{
        entities[0]->acceleration_x = 0.0;
    }
     for (int j =0; j< entities.size(); j++)
         entities[j]->FixedUpdate();
    
    //check y
    for (int j =0; j< entities.size(); j++){
        if(entities[j]->enableCollisions){
            entities[j]->y += entities[j]->velocity_y * FIXED_TIMESTEP;
            for(int i=0; i < walls.size(); ++i){
                entities[j]->collidedWithY(walls[i]);
                float penetration_y = fabs(fabs(entities[j]->y - walls[i]->y) - entities[j]->height - walls[i]->height);
                if(entities[j]->collidedBottom){
                    entities[j]->y += penetration_y +0.00001;
                    entities[j]->velocity_y = 0;
                    break;
                }
                else if(entities[j]->collidedTop){
                    entities[j]->y -= penetration_y +0.00001;
                    entities[j]->velocity_y = 0;
                    break;
                }
            }
        }
    }
    //check x
    for (int j =0; j< entities.size(); j++){
        entities[j]->x += entities[j]->velocity_x * FIXED_TIMESTEP;
       
            for(int i=0; i < walls.size(); ++i){
                entities[j]->collidedWithX(walls[i]);
                float penetration_x = fabs(fabs(entities[j]->x - walls[i]->x) - entities[j]->width - walls[i]->width);
                if( j ==0){ //if is player
                    if(entities[j]->collidedRight){

                        entities[j]->x -= penetration_x ;
                        entities[j]->velocity_x = 0;
                        break;
                    }
                    else if(entities[j]->collidedLeft){
                        entities[j]->x += penetration_x ;
                        entities[j]->velocity_x = 0;
                        break;
                    }
                }
                else{
                    if(entities[j]->collidedRight){
                        entities[j]->facing = -1;
                        entities[j]->velocity_x = -0.4;
                    }
                    if(entities[j]->collidedLeft){
                        entities[j]->facing = 1;
                        entities[j]->velocity_x = 0.4;
                    }
               }
            }
    }
    
    //check collision between entities, start 1 since 0 is the player
    //check Y
    for (int j =1; j< entities.size(); j++){
        if(entities[j]->enableCollisions){
            
            entities[0]->interactWithY(entities[j]);
            if(entities[0]->interactBottom){
                entities[j]->x = 2;
                entities[j]->visiable = false;
                enemy_counter--;
                break;
            }
            if (entities[0]->interactTop){
                end2.text = "Your player is killed!";
                state = STATE_GAME_OVER;
                break;
            }
        }
    }
    //check X
    if(!entities[0]->interactBottom)
        for (int j =1; j< entities.size(); j++){
            if(entities[j]->enableCollisions && entities[0]->interactWithX(entities[j]) ){
                end2.text = "Your player is killed!";
                state = STATE_GAME_OVER;
                break;
            }
        }
    
    if(keys[SDL_SCANCODE_ESCAPE])
        done = true; //exit the program
    if(!boundarycheck_x(*entities[0]))
        entities[0]->x = current_x;
    
    for (int j =0; j< entities.size(); j++){
        if (!boundarycheck_y(*entities[j]))
        {
            if (j == 0){
                end2.text = "Your player falls and dies!";
                state = STATE_GAME_OVER;
            }
            else if(entities[j]->y < 0.5)
                entities[j]->y = 1.33f;
        }
    }
    if (enemy_counter == 0) {
        end2.text = "Win! All enemies are killed!";
    }
    
}

bool ClassDemoApp::UpdateAndRender() {
    float ticks = (float)SDL_GetTicks()/1000.0f;
    float elapsed = ticks - lastFrameTicks;
    lastFrameTicks = ticks;
    
    Update(elapsed);
    Render();
    return done;
}


GLuint ClassDemoApp:: LoadTexture(const char *image_path) {
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

bool ClassDemoApp:: boundarycheck_x(Entity& p){
    if ((p.x+(p.width/2) >= 1.32) || (p.x-(p.width/2)) <= -1.32) {
        return false; //hit the side
    }
    return true;
}

bool ClassDemoApp:: boundarycheck_y(Entity& p){
    if (p.y+(p.height/2) >= 1.0 || p.y-(p.height/2) <= -1.0) {
        return false;// hit the top/bottom
    }
    return true;
}

float ClassDemoApp::lerp(float v0, float v1, float t) {
    return (1.0-t)*v0 + t*v1;
}

void ClassDemoApp::creatMoreEnemy(unsigned int& spriteSheetTexture){
    if (enemy_counter < MAX_ENEMY) {
        srand(unsigned (time(0)));
        int face = rand()%2-1;
        //enemy
        Entity* enemy = new Entity(0.0f, 1.3f, 0.0f / 128.0f, 78.0f / 256.0f, 4.0f / 128.0f, 16.0f / 256.0f, false, 1.0f, spriteSheetTexture, true);
        enemy->enableCollisions = true;
        if (face == 0)
            enemy->velocity_x = -0.4;
        else
            enemy->velocity_x = 0.4;
        enemy->velocity_y = 0;
        enemy->friction_x = 0;
        enemy->friction_y = 0;
        enemy->acceleration_y = Gravity;
        enemy_counter++;
        entities.push_back(enemy);
    }
}
