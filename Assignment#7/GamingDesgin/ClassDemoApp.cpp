//
//  ClassDemoApp.cpp
//  NYUCodebase
//  Update of Hw05
//    sound effect:
//    -- 2 sound effects are added
//    --  background music is added
//    visual effect:
//    -- screenshake when hit on wall
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
    
    music = Mix_LoadMUS("background_sound.mp3");
    Mix_PlayMusic(music, -1);

    screenShakeValue = 0.0f;
	screenShakeSpeed = 40.0f;
    
    spriteSheetTexture = LoadTexture("sprites.png");
    string levelFile = "/Users/EDL_MacPC/Documents/Study/Computer Science/CS 3113/Assignment/Assignment#5/map.txt";
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
		else if (line == "[player]") {
			readEntityData(infile);
		}
        else if (line == "[enemy]" ) {
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
    start.text = "Let's Play! Enter SPACE to play, or ESC to exit!";
    
    start2.set_photo_path ="font1.png";
    start2.a = 1.0;
	start2.r = 1.0;
	start2.g = 1.0;
	start2.b = 1.0;
	start2.y = -0.3;
	start2.x = -0.7;
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

	
}

void ClassDemoApp::gameRender(){
    // render stuff
    glClearColor(1.0f, 1.0f, 1.0f, 0.5f); //set backgound to white
    glClear(GL_COLOR_BUFFER_BIT);//Makes background default color
    glMatrixMode(GL_MODELVIEW);
    float xPos = -entities[0]->x;
    glLoadIdentity();
    glTranslatef(0.0f, sin(screenShakeValue * screenShakeSpeed)* screenShakeIntensity, 0.0f);

    if(xPos > -1.33)
        xPos = -1.33;
    else if(xPos < -mapWidth*TILE_SIZE + 1.33)
        xPos = -mapWidth*TILE_SIZE + 1.33;
    glTranslatef(xPos , -entities[0]->y, 0.0f);
     drawTileMap();
    
    for (int i =0; i< entities.size(); i++){
        if(entities[i]->visiable)
            entities[i]->Draw();
    }

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
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
                if(entities[0]->collidedBottom){//only jump when bottom collids
                    Mix_PlayChannel( -1, sound_jump, 0.5);
                    entities[0]->velocity_y = 0.85f;
                }
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
    timer += elapsed;
    timer_tweening+=elapsed;
    screenShakeValue += FIXED_TIMESTEP;
    float current_x = entities[0]->x;
    float current_y = entities[0]->y;

    
    if(keys[SDL_SCANCODE_LEFT]  ) {
        entities[0]->acceleration_x =-2.0f;
    }
    else if( keys[SDL_SCANCODE_RIGHT] ) {
        entities[0]->acceleration_x = 2.0f;
    }
    else{
        entities[0]->acceleration_x = 0.0;
    }
    
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
                if(entities[0]->collidedTop || entities[0]->collidedLeft || entities[0]->collidedRight)
                    Mix_PlayChannel( -1, sound_crash, 0.5);

                if(i>0){
                    if(entities[i]->collidedRight){
                        entities[i]->facing = -1;
                        entities[i]->velocity_x = -0.4;
                    }
                    if(entities[i]->collidedLeft){
                        entities[i]->facing = 1;
                        entities[i]->velocity_x = 0.4;
                    }
                }
            }
		}
    
    float momentum = 0;
    if(entities[0]->collidedRight || entities[0]->collidedLeft){
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
    
    //tweening when jump
    if(!entities[0]->collidedBottom){
        tweening_Start = elapsed;
        tweening_End = tweening_Start + elapsed;
        tweening_time  += FIXED_TIMESTEP;
        float tweening_value = mapValue(tweening_time, tweening_Start, tweening_End, 0.0, 1.0);
        entities[0]->Draw(lerp(0.0, 1.0, tweening_value), 0.0);
    }
    else{
        tweening_time = 0;
    }
   
    
    //check collision between entities, start 1 since 0 is the player
    //check Y
    for (int j =1; j< entities.size(); j++){
            entities[0]->interactWithY(entities[j]);
        if(j == 10){
            entities[j]->visiable = false;
            end2.text = "You pass level!";
            break;
        }
        else{
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
                if(j == 10){
                    entities[j]->visiable = false;
                    end2.text = "You pass level!";
                    break;
                }
                end2.text = "Your player is killed!";
                state = STATE_GAME_OVER;
                break;
            }
        }
    //if take the key
    if(entities[0]->x > 4.65f){
        end2.text = "You pass level!";
       state = STATE_GAME_OVER;
    }
    
    if(keys[SDL_SCANCODE_ESCAPE])
        done = true; //exit the program
    
    
    for (int j =0; j< entities.size(); j++){
        if (!boundarycheck_y(*entities[j]))
        {
            if (j == 0){
                end2.text = "Your player falls and dies!";
                state = STATE_GAME_OVER;
            }
        }
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
	if (type == "player") {
        float u = (float)(98 % SPRITE_COUNT_X) / SPRITE_COUNT_X;
		float v = (float)(98 / SPRITE_COUNT_X) / SPRITE_COUNT_Y;
		float w = 1.0f / SPRITE_COUNT_X;
		float h = 1.0f / SPRITE_COUNT_Y;
        
        Entity* player = new Entity(x, y, u, v, w, h, false, 0.45f, spriteSheetTexture, true);
        player->enableCollisions = true;
        player->velocity_x = 0;
        player->velocity_y = 0;
        player->friction_x = 1.8;
        player->friction_y = 0;
        player->acceleration_y = Gravity;
		entities.push_back(player);
	}
       else if (type == "enemy") {
           float u = (float)(80 % SPRITE_COUNT_X)/SPRITE_COUNT_X;
           float v = (float)(80 / SPRITE_COUNT_X)/SPRITE_COUNT_Y;
           float w = 1.0f / SPRITE_COUNT_X;
           float h = 1.0f / SPRITE_COUNT_Y;
           
           srand(unsigned (time(0)));
           int face = rand()%2-1;
           
        Entity* enemy = new Entity(x, y, u, v, w, h, false, 0.5f, spriteSheetTexture, true);
           enemy->enableCollisions = true;
           if (face == 0)
               enemy->velocity_x = -0.4;
           else
               enemy->velocity_x = 0.4;
           enemy->velocity_y = 0;
           enemy->friction_x = 0;
           enemy->friction_y = 0;
           enemy->acceleration_y = Gravity;
		entities.push_back(enemy);
	}
       else if (type == "key") {
           float u = (float)(86 % SPRITE_COUNT_X)/SPRITE_COUNT_X;
           float v = (float)(86 / SPRITE_COUNT_X)/SPRITE_COUNT_Y;
           float w = 1.0f / SPRITE_COUNT_X;
           float h = 1.0f / SPRITE_COUNT_Y;
           
           srand(unsigned (time(0)));
           int face = rand()%2-1;
           Entity* key = new Entity(x, y, u, v, w, h, false, 2.0f, spriteSheetTexture, true);
           key->enableCollisions = true;
           if (face == 0)
               key->velocity_x = -0.1;
           else
               key->velocity_x = 0.1;
           key->velocity_y = 0;
           key->friction_x = 0;
           key->friction_y = 0;
           key->acceleration_y = Gravity;
           entities.push_back(key);
       }
}


void ClassDemoApp::drawTileMap() {
    //glPushMatrix();
	vector<float> vertexData;
	vector<float> texCoordData;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, spriteSheetTexture);
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

bool ClassDemoApp::isSolid(unsigned char tile){
	switch (tile){
         case 16:
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
	if (gridX < 0 || gridX > 90 || gridY < 0 || gridY > 20)
		return 0.0f;
    
	if (long(levelData[gridY][gridX])== 16 ||long(levelData[gridY][gridX])== 32 ) {
		float yCoordinate = (gridY * TILE_SIZE);
		return -y - yCoordinate;
	}
	return 0.0f;
}

float ClassDemoApp::checkGridCollisionX(float x, float y) {
	
	worldToTileCoordinates(x, y, &gridX, &gridY);
	if (gridX < 0 || gridX > 90 || gridY < 0 || gridY > 20)
		return 0.0f;
    
	if (long(levelData[gridY][gridX])== 16 ||long(levelData[gridY][gridX])== 32) {
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
		entity->y -= adjust*TILE_SIZE - 0.0000001f;
        entity->velocity_y = 0 ;
		entity->collidedTop = true;
	}
}
void ClassDemoApp::LevelCollisionX(Entity* entity){
	float adjust = checkGridCollisionX(entity->x - entity->width * 0.5f, entity->y);
	if (adjust != 0.0f) {
		entity->x -= adjust * TILE_SIZE*0.1f + 0.0000001f;
		entity->velocity_x = 0;
		entity->collidedLeft = true;
	}
	adjust = checkGridCollisionX(entity->x + entity->width * 0.5f, entity->y);
	if (adjust != 0.0f) {
        entity->x += adjust * TILE_SIZE*0.1f + 0.0000001f;
		entity->velocity_x = 0;
		entity->collidedRight = true;
	}
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

float ClassDemoApp::easeOut(float from, float to, float time) {
    float oneMinusT = 1.0f-time;
    float tVal =  1.0f - (oneMinusT * oneMinusT * oneMinusT *
                          oneMinusT * oneMinusT);
    return (1.0f-tVal)*from + tVal*to;
}

float ClassDemoApp::easeOutElastic(float from, float to, float time) {
    float p = 0.3f;
    float s = p/4.0f;
    float diff = (to - from);
    return from + diff + (diff*pow(2.0f,-10.0f*time) * sin((time-s)*(2*PI)/p));
}
