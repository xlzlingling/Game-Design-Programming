//
//  Entity.h
//  NYUCodebase
//  Assignment# 2
//  Created by Edwin Li on 2/16/15.
//  Copyright (c) 2015 Edwin Li. All rights reserved.
//

#include "Entity.h"
#include <string>
#include <iostream>
SDL_Window* displayWindow;
const double pi = 3.14159265339;
float current_score_height = 0.85f;
Entity LHS,RHS,ball,winner,LS0,RS0,LS1,RS1,LS2,RS2,LS3,RS3;

void setup(){
    SDL_Init(SDL_INIT_VIDEO);
	displayWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
	SDL_GL_MakeCurrent(displayWindow, context);
    
	glViewport(0, 0, 800, 600);
    glMatrixMode(GL_PROJECTION_MATRIX);
    glOrtho(-1.33, 1.33, -1.0, 1.0, -1.0, 1.0);
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f); //set backgound to white

    LHS.photo_path =(char*) "happy.png";
    LHS.height = 0.3f;
    LHS.width = 0.08f;
    LHS.set_x = -0.85f;
    LHS.set_y = 0.0f;

    
    RHS.photo_path =(char*) "sad.png";
    RHS.height = 0.3f;
    RHS.width = 0.08f;
    RHS.set_x = 0.85f;
    RHS.set_y = 0.0f;

    ball.photo_path =(char*) "ball.png";
    ball.height = 0.05f;
    ball.width = 0.05f;
    ball.set_x = 0;
    ball.set_y = 0;
    ball.angle = rand() % 360;
    
    winner.photo_path = (char*) "win.png";
    winner.height = 0.2f;
    winner.width = 0.2f;
    winner.set_x = 2;
    winner.set_y = 0;
    
    LS0.photo_path =(char*) "0.png";
    LS0.height = 0.05f;
    LS0.width = 0.05f;
    LS0.set_x = -0.1F;
    LS0.set_y = 0.85F;
    
    RS0.photo_path =(char*) "0.png";
    RS0.height = 0.05f;
    RS0.width = 0.05f;
    RS0.set_x = 0.1F;
    RS0.set_y = 0.85F;
    
    LS1.photo_path =(char*) "1.png";
    LS1.height = 0.05f;
    LS1.width = 0.05f;
    LS1.set_x = -0.1F;
    LS1.set_y = 2;
    
    RS1.photo_path =(char*) "1.png";
    RS1.height = 0.05f;
    RS1.width = 0.05f;
    RS1.set_x = 0.1F;
    RS1.set_y = 2;
    
    LS2.photo_path =(char*) "2.png";
    LS2.height = 0.05f;
    LS2.width = 0.05f;
    LS2.set_x = -0.1F;
    LS2.set_y = 2;
    
    RS2.photo_path =(char*) "2.png";
    RS2.height = 0.05f;
    RS2.width = 0.05f;
    RS2.set_x = 0.1F;
    RS2.set_y = 2;
    
    LS3.photo_path =(char*) "3.png";
    LS3.height = 0.05f;
    LS3.width = 0.05f;
    LS3.set_x = -0.1F;
    LS3.set_y = 2;
    
    RS3.photo_path =(char*) "3.png";
    RS3.height = 0.05f;
    RS3.width = 0.05f;
    RS3.set_x = 0.1F;
    RS3.set_y = 2;
}
bool ProcessEvents(SDL_Event& event){
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE)
            return false;
    }
    return true;
};

void print_score(int LHS, int RHS){
    switch (LHS) {
        case 1:
            LS0.set_y = 2;
            LS1.set_y = 0.85f;
            break;
        case 2:
            LS1.set_y = 2;
            LS2.set_y = 0.85f;
            break;
        case 3:
            LS2.set_y = 2;
            LS3.set_y = 0.85f;
            break;
        default:
            break;
    }
    switch (RHS) {
        case 1:
            RS0.set_y = 2;
            RS1.set_y = 0.85f;
            break;
        case 2:
            RS1.set_y = 2;
            RS2.set_y = 0.85f;
            break;
        case 3:
            RS2.set_y = 2;
            RS3.set_y = 0.85f;
            break;
        default:
            break;
    }
}

bool checkCollision(Entity ball, Entity side){
    float ball_top = ball.set_y + ball.height * 0.5f;
    float ball_bottom = ball.set_y - ball.height * 0.5f;
    float ball_left = ball.set_x - ball.width * 0.5f;
    float ball_right = ball.set_x + ball.width * 0.5f;
    
    float side_top = side.set_y + side.height * 0.5f;
    float side_bottom = side.set_y - side.height * 0.5f;
    float side_left = side.set_x - side.width * 0.5f;
    float side_right = side.set_x + side.width * 0.5f;

    if ((ball_left <= side_right && ball_right >= side_left) || (ball_right >= side_left && ball_left <= side_right))
        if (ball_bottom >= side_bottom && ball_top <= side_top)
            return true;
    return false;
}

void Update(float& lastFrameTicks, int& left_score,int& right_score){
    float move_speed = 2.0f;
    float ticks = (float)SDL_GetTicks()/1000.0f;
    float elapsed = ticks - lastFrameTicks;
    lastFrameTicks = ticks;
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    
    if(left_score >2 || right_score >2){
        ball.set_x = 0;
        ball.set_y = 0;
        if (left_score == 3)
            winner.set_x = -0.5f;
        else if (right_score == 3)
            winner.set_x = 0.5f;
    }
    else{
        if(keys[SDL_SCANCODE_UP] && RHS.set_y < 0.7f){
            RHS.set_y += elapsed * move_speed;
            if (keys[SDL_SCANCODE_W] && LHS.set_y < 0.7f)
                LHS.set_y+= elapsed * move_speed;
            else if (keys[SDL_SCANCODE_S] && LHS.set_y > -0.7f)
                LHS.set_y-= elapsed * move_speed;
        }
        else if (keys[SDL_SCANCODE_DOWN] && RHS.set_y > -0.7f){
            RHS.set_y-= elapsed * move_speed;
            if (keys[SDL_SCANCODE_W] && LHS.set_y < 0.7f)
                LHS.set_y+= elapsed * move_speed;
            else if (keys[SDL_SCANCODE_S] && LHS.set_y > -0.7f)
                LHS.set_y-= elapsed * move_speed;
        }
        else if (keys[SDL_SCANCODE_W] && LHS.set_y < 0.7f)
            LHS.set_y+= elapsed * move_speed;
        else if (keys[SDL_SCANCODE_S] && LHS.set_y > -0.7f)
            LHS.set_y-= elapsed * move_speed;
        
        if (ball.set_y < -0.95f)
            ball.angle = (360-ball.angle);
        
        else if (ball.set_y >  0.95f)
            ball.angle = (360-ball.angle);
        
        else if (ball.set_x <=  -0.95f) {
            //right score
            ball.angle = (180-ball.angle);
            right_score++;
        }
        else if (ball.set_x >=  0.95f) {
            //left score
            ball.angle = (180-ball.angle);
            left_score++;
        }
        if (checkCollision(ball, LHS))
            ball.angle = (180-ball.angle);
        
        if (checkCollision(ball, RHS))
            ball.angle = (180-ball.angle);
        
        print_score(left_score,right_score);
        ball.set_x += elapsed * sin( (ball.angle+90.0) * pi/180.0) * move_speed ;
        ball.set_y += elapsed * cos( (ball.angle+90.0) * pi/180.0) * move_speed ;
    }
}

void Render(){
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f); //set backgound to white
	glClear(GL_COLOR_BUFFER_BIT);//Makes background default color
	LHS.Draw();
	RHS.Draw();
	ball.Draw();
    
    LS0.Draw();
    RS0.Draw();
    LS1.Draw();
    RS1.Draw();
    LS2.Draw();
    RS2.Draw();
    LS3.Draw();
    RS3.Draw();
    
    winner.Draw();
};

void Clear(){
	SDL_Quit();
}

int main(int argc, char *argv[])
{
	setup();
	SDL_Event event;
    //keep time
    float lastFrameTicks = 0.0f;
    //keep score
    int left_score =0, right_score = 0;

    while (ProcessEvents(event)) {
            Update(lastFrameTicks,left_score,right_score);
            Render();
            SDL_GL_SwapWindow(displayWindow);
    }
	Clear();
    return 0;
}
