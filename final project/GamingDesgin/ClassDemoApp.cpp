//
//  ClassDemoApp.cpp
//  NYUCodebase
//
//  Created by Edwin Li on 3/19/15.
//  Copyright (c) 2015  Edwin Li. All rights reserved.
//

#include "ClassDemoApp.h"
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
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    
    sound_crash = Mix_LoadWAV("crash_sound.wav");
    sound_jump = Mix_LoadWAV("crash_jump.wav");

    music = Mix_LoadMUS("10 Epic Song.mp3");
    Mix_PlayMusic(music, -1);
    blue_score = 0;
    red_score = 0;
    
    screenShakeValue = 0.0f;
	screenShakeSpeed = 30.0f;
    
    spriteSheetTexture1 = LoadTexture("sheet.png");

     levelFile = "/Users/EDL_MacPC/Documents/Study/Computer Science/CS 3113/final project/level_1.txt";
    
	ifstream infile(levelFile);
    string line;
	bool flag = true;
	while (getline(infile, line) && flag == true) {
		if (line == "[header]") {
			if (!readHeader(infile)) {
				flag = false;
			}
		}
		else if (line == "[layer]") {
			readLayerData(infile);
		}
		else if (line == "[player 1]") {
			readEntityData(infile);
		}
        else if (line == "[player 2]" ) {
			readEntityData(infile);
		}
        else if (line == "[key]" ) {
			readEntityData(infile);
		}
	}
    
   
    textSheet = LoadTexture("font1.png");
    start.set_photo_path ="font1.png";
    start.a = 1.0;
	start.r = 1.0;
	start.g = 1.0;
	start.b = 1.0;
	start.y = 0;
	start.x = -1.2;
    start.size = 0.1f;
	start.spacing = -0.05;
    start.text = "Let's Play! Enter SPACE to play. ESC to end";
    
    start2.set_photo_path ="font1.png";
    start2.a = 1.0;
	start2.r = 1.0;
	start2.g = 1.0;
	start2.b = 1.0;
	start2.y = -0.3;
	start2.x = -0.7;
    start2.size = 0.1f;
	start2.spacing = -0.05;
    start2.text = "Go up and down to avoid boxes";

    counter.set_photo_path ="font1.png";
    counter.a = 1.0;
	counter.r = 1.0;
	counter.g = 1.0;
	counter.b = 1.0;
	counter.y = 0;
	counter.x = 0;
    counter.size = 0.5f;
	counter.spacing = -0.05;
    counter.text = "3";
    
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
    Mix_FreeChunk(sound_crash);
    Mix_FreeChunk(sound_jump);
    Mix_FreeMusic(music);
    SDL_Quit();
}

void ClassDemoApp::Render() {
    
    switch(state) {
            case STATE_MAIN_MENU:
            mainMenuRender();
            break;
        case STATE_GAME_LEVEL_1:
        case STATE_GAME_LEVEL_2:
        case STATE_GAME_LEVEL_3:
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
    
	
}

void ClassDemoApp::gameRender(){
    // render stuff
    glClearColor(1.0f, 1.0f, 1.0f, 0.5f); //set backgound to white
    glClear(GL_COLOR_BUFFER_BIT);//Makes background default color
    glMatrixMode(GL_MODELVIEW);
    //for red --------------------------
    float xPos_red = -entities[0]->x;
    glLoadIdentity();
   // glTranslatef(0.0f, sin(screenShakeValue * screenShakeSpeed)* screenShakeIntensity, 0.0f);
    if(xPos_red > -1.33)
        xPos_red = -1.33;
    else if(xPos_red < -mapWidth*TILE_SIZE + 1.33)
        xPos_red = -mapWidth*TILE_SIZE + 1.33;
    glTranslatef(xPos_red , -entities[0]->y+0.5, 0.0f);
     drawTileMap();
    for (int i =0; i< entities.size(); i++){
            entities[i]->Draw();
    }

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glPopMatrix();
    //----------------------------------------
    //for blue
    
    glMatrixMode(GL_MODELVIEW);
    float xPos = -entities[1]->x;
    glLoadIdentity();
   // glTranslatef(0.0f, sin(screenShakeValue * screenShakeSpeed)* screenShakeIntensity, 0.0f);
    if(xPos > -1.33)
        xPos = -1.33;
    else if(xPos < -mapWidth*TILE_SIZE + 1.33)
        xPos = -mapWidth*TILE_SIZE + 1.33;
    glTranslatef(xPos , -entities[1]->y-0.5, 0.0f);
    drawTileMap();
    for (int i =0; i< entities.size(); i++){
        if(entities[i]->visiable)
            entities[i]->Draw();
    }
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    //count to start
    if(gametimer < 1)
         counter.DrawText();
    else if(gametimer>=1 && gametimer<2){
        counter.text = "2";
        counter.DrawText();
    }
    else if(gametimer>=2 && gametimer<3){
        counter.text = "1";
        counter.DrawText();
    }
    glPopMatrix();
}

void ClassDemoApp::GameoverRender(){
    
    // render stuff
    glClearColor(1.0f, 1.0f, 1.0f, 0.5f); //set backgound to white
    glClear(GL_COLOR_BUFFER_BIT);//Makes background default color
    //draw stuff
    drawTileMap();
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
                //if(entities[0]->collidedBottom)//only jump when bottom collids
                    entities[0]->velocity_y = 0.85f;
            }
            if(event.key.keysym.scancode == SDL_SCANCODE_F){
                // do something
            }
        }
    }
    switch(state) {
        case STATE_MAIN_MENU:
            mainMenuUpdate(elapsed);
            break;
        case STATE_GAME_LEVEL_1:
        case STATE_GAME_LEVEL_2:
        case STATE_GAME_LEVEL_3:
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
    if (menu_timer >2) {
        if(keys[SDL_SCANCODE_DOWN] || keys[SDL_SCANCODE_UP] ||keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_RIGHT]|| keys[SDL_SCANCODE_KP_ENTER] || keys[SDL_SCANCODE_SPACE]){
            state = 1; //go the game level
            Update(elapsed);
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
    gametimer+=elapsed;
    if (gametimer > 3) {
        timer += elapsed;
        
        //player 1
        if(keys[SDL_SCANCODE_UP]  ) {
            entities[0]->acceleration_y = 1.0f;
            Mix_PlayChannel( 1, sound_jump, 2);
        }
        else if( keys[SDL_SCANCODE_DOWN] ) {
            entities[0]->acceleration_y = -2.0f;
        }
        else{
            entities[0]->acceleration_y = -2.0f;
        }
        if(entities[0]->velocity_x<=1.0f)
            entities[0]->acceleration_x = BASE_SPEED;
        else
            entities[0]->acceleration_x = 0;
        
        //player 2
        if(keys[SDL_SCANCODE_W]  ) {
            Mix_PlayChannel( 1, sound_jump, 2);
            entities[1]->acceleration_y = 1.0f;
        }
        else if( keys[SDL_SCANCODE_S] ) {
            entities[1]->acceleration_y = -2.0f;
        }
        else{
            entities[1]->acceleration_y = -2.0f;
        }
        if(entities[1]->velocity_x<=1.0f)
            entities[1]->acceleration_x = BASE_SPEED;
        else
            entities[1]->acceleration_x = 0;
        
        entities[0]->camX=-entities[0]->velocity_x*FIXED_TIMESTEP;
        entities[0]->camY=-entities[0]->velocity_y*FIXED_TIMESTEP;
        
		for (int i = 0; i < entities.size(); i++){
            entities[i]->FixedUpdate();
			entities[i]->resetCollision();
            if(entities[i]->enableCollisions){
                entities[i]->x += entities[i]->velocity_x * FIXED_TIMESTEP;
                entities[i]->y += entities[i]->velocity_y * FIXED_TIMESTEP;
                LevelCollisionY(entities[i]);
                LevelCollisionX(entities[i]);
            }
		}
        
        
        cout<< entities[0]->x << endl;
        cout<< entities[1]->x << endl;
        float momentum = 0;
        
        //check player 1 collided with play 2
        entities[0]->interactWithY(entities[1]);
        entities[0]->interactWithX(entities[1]);
        if (entities[0]->interactBottom || entities[0]->interactTop || entities[0]->interactRight || entities[0]->interactLeft) {
            cout << "in here";
            shakeStart = elapsed ;
            shakeEnd = shakeStart + elapsed;
            if(timer < 1)
                momentum = 0;
            else
                momentum = timer * 0.01f;
            
            float animationtime = mapValue(FIXED_TIMESTEP, shakeStart, shakeEnd, 0.0f, 1.0f);
            screenShakeIntensity = easeOut(momentum, 0.0f, animationtime);
        }
        else if (timer> 3){
            timer =0;
            screenShakeIntensity = 0;
        }
        
        string intStr_red = to_string(red_score);
        string intStr_blue = to_string(blue_score);
        string final_text = intStr_red + " : " + intStr_blue + "Red win!";
        end2.text = final_text;
        
        //if take the key
        if(entities[0]->x > 25.55f){
            red_score++;
            if(state == STATE_GAME_LEVEL_3){
                state = STATE_GAME_OVER;
            }
            else if (state == STATE_GAME_LEVEL_1){
              state = STATE_GAME_LEVEL_2 ;
                reInit();
            }
            else if (state == STATE_GAME_LEVEL_2){
                state = STATE_GAME_LEVEL_3 ;
                reInit();
            }
        }
        else if (entities[1]->x > 25.55f){
            blue_score++;
            if(state == STATE_GAME_LEVEL_3){
                state = STATE_GAME_OVER;
            }
            else if (state == STATE_GAME_LEVEL_1){
                state = STATE_GAME_LEVEL_2 ;
                reInit();
            }
            else if (state == STATE_GAME_LEVEL_2){
                state = STATE_GAME_LEVEL_3 ;
                reInit();
            }
        }
        if (red_score > blue_score){
            string final_text = intStr_red + " : " + intStr_blue +". "+ "Red win!";
            end2.text = final_text;
        }
        else
            string final_text = intStr_red + " : " + intStr_blue +". "+ "blue win!";
        
        if(keys[SDL_SCANCODE_ESCAPE])
            done = true; //exit the program
    }
}

bool ClassDemoApp::UpdateAndRender() {
    float ticks = (float)SDL_GetTicks()/1000.0f;
    float elapsed = ticks - lastFrameTicks;
    lastFrameTicks = ticks;
    
    float fixedElapsed = elapsed + timeLeft;
    if (fixedElapsed > FIXED_TIMESTEP * MAX_TIMESTEPS)
        fixedElapsed = FIXED_TIMESTEP * MAX_TIMESTEPS;
    
    while (fixedElapsed >= FIXED_TIMESTEP){
		fixedElapsed -= FIXED_TIMESTEP;
	}
    
    timeLeft = fixedElapsed;
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

bool ClassDemoApp::readHeader(std::ifstream &stream) {
	string line;
	mapWidth = -1;
	mapHeight = -1;
	while (getline(stream, line)) {
		if (line == "") { break; }
		istringstream sStream(line);
		string key, value;
		getline(sStream, key, '=');
		getline(sStream, value);
		if (key == "width")
            mapWidth = atoi(value.c_str());
		else if (key == "height")
			mapHeight = atoi(value.c_str());
	}
	if (mapWidth == -1 || mapHeight == -1) return false;
    else {
		levelData = new unsigned char*[mapHeight];
		for (int i = 0; i < mapHeight; ++i) {
			levelData[i] = new unsigned char[mapWidth];
		}
		return true;
	}
}

bool ClassDemoApp::readLayerData(std::ifstream &stream) {
	string line;
	while (getline(stream, line)) {
        if (line == "") { break; }
		istringstream sStream(line);
		string key, value;
		getline(sStream, key, '=');
		getline(sStream, value);
		if (key == "data") {
			for (int y = 0; y < mapHeight; y++) {
				getline(stream, line);
				istringstream lineStream(line);
				string tile;
				for (int x = 0; x < mapWidth; x++) {
					getline(lineStream, tile, ',');
                    unsigned char val = atoi(tile.c_str());
					if (val > 0){
						levelData[y][x] = val-1;
                    }
					else
						levelData[y][x] = 0;
				}
			}
		}
	}
	return true;
}

bool ClassDemoApp::readEntityData(std::ifstream &stream) {
    string line;
	string type;
	while (getline(stream, line)) {
		if (line == "") { break; }
		istringstream sStream(line);
		string key, value;
		getline(sStream, key, '=');
		getline(sStream, value);
		if (key == "type")
			type = value;
		 else if (key == "location") {
			istringstream lineStream(value);
            string xPosition, yPosition;
			getline(lineStream, xPosition, ',');
			getline(lineStream, yPosition, ',');
			float placeX = (float)atoi(xPosition.c_str()) / 16 * 1.0f;
			float placeY = (float)atoi(yPosition.c_str()) / 16 * -1.2f ;
			placeEntity(type, placeX, placeY);
		}
	}
	return true;
}

void ClassDemoApp::placeEntity(string type, float x, float y) {
	if (type == "player 1") {
        float u = (float)(69 % SPRITE_COUNT_X) / SPRITE_COUNT_X;
		float v = (float)(69 / SPRITE_COUNT_X) / SPRITE_COUNT_Y;
		float w = 1.0f / SPRITE_COUNT_X;
		float h = 1.0f / SPRITE_COUNT_Y;
        
        Entity* player = new Entity(x, y, u, v, w, h, false, 0.4f, spriteSheetTexture1, true);
        player->enableCollisions = true;
        player->velocity_x = BASE_SPEED;
        player->velocity_y = 0;
        player->friction_x = 0;
        player->friction_y = 0;
        player->acceleration_y = Gravity;
		entities.push_back(player);
	}
       else if (type == "player 2") {
           float u = (float)(41 % SPRITE_COUNT_X)/SPRITE_COUNT_X;
           float v = (float)(41 / SPRITE_COUNT_X)/SPRITE_COUNT_Y;
           float w = 1.0f / SPRITE_COUNT_X;
           float h = 1.0f / SPRITE_COUNT_Y;
           
           Entity* player = new Entity(x, y, u, v, w, h, false, 0.4f, spriteSheetTexture1, true);
           player->enableCollisions = true;
           player->velocity_x = BASE_SPEED;
           player->velocity_y = 0;
           player->friction_x = 0;
           player->friction_y = 0;
           player->acceleration_y = Gravity;
           entities.push_back(player);
	}
}


void ClassDemoApp::drawTileMap() {
	vector<float> vertexData;
	vector<float> texCoordData;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, spriteSheetTexture1);
	glMatrixMode(GL_MODELVIEW);
	   
	for (int y = 0; y < mapHeight; y++) {
		for (int x = 0; x < mapWidth; x++) {
			if (levelData[y][x] != 0) {
				float u = (float)(((int)levelData[y][x]) % SPRITE_COUNT_X) / (float)SPRITE_COUNT_X;
				float v = (float)(((int)levelData[y][x]) / SPRITE_COUNT_X) / (float)SPRITE_COUNT_Y;
				float spriteWidth = 1.0f / (float)SPRITE_COUNT_X;
				float spriteHeight = 1.0f / (float)SPRITE_COUNT_Y;
                vertexData.insert(vertexData.end(), {
					TILE_SIZE * x, -TILE_SIZE * y,
					TILE_SIZE * x, (-TILE_SIZE * y) - TILE_SIZE,
					(TILE_SIZE * x) + TILE_SIZE, (-TILE_SIZE * y) - TILE_SIZE,
					(TILE_SIZE * x) + TILE_SIZE, -TILE_SIZE * y
				});
				texCoordData.insert(texCoordData.end(), {
                    u, v,
					u, v + (spriteHeight),
					u + spriteWidth, v + (spriteHeight),
					u + spriteWidth, v
				});
			}
		}
	}
    glVertexPointer(2, GL_FLOAT, 0, vertexData.data());
    glEnableClientState(GL_VERTEX_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, 0, texCoordData.data());
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glDrawArrays(GL_QUADS, 0, vertexData.size()/2);
	glDisable(GL_TEXTURE_2D);
	glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

bool ClassDemoApp::isSolid(long tile){
	switch (tile){
         case 16:
         case 30:
            return true;
            break;
        default:
            return false;
            break;
	}
	return false;
}
void ClassDemoApp::worldToTileCoordinates(float worldX, float worldY, int* gridX, int* gridY) {
	*gridX = (int)((worldX + (WORLD_OFFSET_X)) / TILE_SIZE);
	*gridY = (int)((-worldY + (WORLD_OFFSET_Y)) / TILE_SIZE);
}

float ClassDemoApp::checkGridCollisionY(float x, float y){
	int gridX, gridY;
	worldToTileCoordinates(x, y, &gridX, &gridY);
		if (isSolid( long(levelData[gridY][gridX]))) {
		float yCoordinate = (gridY * TILE_SIZE);
		return -y - yCoordinate;
	}
	return 0.0f;
}

float ClassDemoApp::checkGridCollisionX(float x, float y) {
	
	worldToTileCoordinates(x, y, &gridX, &gridY);
		if (isSolid( long(levelData[gridY][gridX]))) {
		float xCoordinate = (gridX * TILE_SIZE);
		return -x - xCoordinate;
	}
	return 0.0f;
}

void ClassDemoApp::LevelCollisionY(Entity* entity){
	float adjust = checkGridCollisionY(entity->x, entity->y - entity->height*0.5f);
	if (adjust != 0.0f){
		entity->y += adjust*TILE_SIZE + 0.0000001f;
		entity->velocity_y = 0 ;
		entity->collidedBottom = true;
	}
	adjust = checkGridCollisionY(entity->x, entity->y + entity->height*0.5f);
	if (adjust != 0.0f){
		entity->y -= adjust*TILE_SIZE*0.1 - 0.0000001f;
        entity->velocity_y = 0 ;
		entity->collidedTop = true;
      
	}
}
void ClassDemoApp::LevelCollisionX(Entity* entity){
	float adjust = checkGridCollisionX(entity->x - entity->width * 0.5f, entity->y);
	if (adjust != 0.0f) {
		entity->x -= adjust * TILE_SIZE*0.001f + 0.0000001f;
		entity->velocity_x = 0;
		entity->collidedLeft = true;
        Mix_PlayChannel( -1, sound_crash, 1);
	}
	adjust = checkGridCollisionX(entity->x + entity->width * 0.5f, entity->y);
	if (adjust != 0.0f) {
        entity->x += adjust * TILE_SIZE*0.001f + 0.0000001f;
		entity->velocity_x = 0;
		entity->collidedRight = true;
        Mix_PlayChannel( -1, sound_crash, 1);
	}
}
float ClassDemoApp::easeOut(float from, float to, float time) {
    float oneMinusT = 1.0f-time;
    float tVal =  1.0f - (oneMinusT * oneMinusT * oneMinusT *
                          oneMinusT * oneMinusT);
    return (1.0f-tVal)*from + tVal*to;
}

float ClassDemoApp::mapValue(float value, float srcMin, float srcMax, float dstMin, float dstMax) {
    float retVal = dstMin + ((value - srcMin)/(srcMax-srcMin) * (dstMax-dstMin));
    if(retVal < dstMin) {
        retVal = dstMin;
    }
    if(retVal > dstMax) {
        retVal = dstMax;
    }
    return retVal;
}

void ClassDemoApp::reInit(){
    gametimer = 0;
    counter.text = "3";
    if(state == STATE_GAME_LEVEL_2)
         levelFile = "/Users/EDL_MacPC/Documents/Study/Computer Science/CS 3113/final project/level_2.txt";
    if(state == STATE_GAME_LEVEL_3)
         levelFile = "/Users/EDL_MacPC/Documents/Study/Computer Science/CS 3113/final project/level_3.txt";
    while (!entities.empty()) {
        delete entities.back(), entities.pop_back();
    }
	ifstream infile(levelFile);
    string line;
	bool flag = true;
	while (getline(infile, line) && flag == true) {
		if (line == "[header]") {
			if (!readHeader(infile)) {
				flag = false;
			}
		}
		else if (line == "[layer]") {
			readLayerData(infile);
		}
		else if (line == "[player 1]") {
			readEntityData(infile);
		}
        else if (line == "[player 2]" ) {
			readEntityData(infile);
		}
	}
}
