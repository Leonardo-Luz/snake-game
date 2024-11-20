#include <stdlib.h>
#include <string.h>
#include <raylib.h>
#include <stdio.h>

#include "../include/game.h"

#define GRID		20
#define SCREEN_WIDTH	600
#define SCREEN_HEIGHT	600
#define FPS		60

#define TILE		SCREEN_HEIGHT/GRID

#define MULT_TD		6

#define MAIN_MENU_STATE 0
#define GAME_OVER_STATE 1
#define PAUSE_STATE	2
#define CONTROLS_STATE 3
#define SCORE_STATE	4
#define NEW_SCORE	5

// TODO: Change draw and menu functions to other files ? 

// NOTE: GLOBAL VARIABLES
double timer = 0;
double resetTime = 0;
bool pressed = false;
int option = 0;
int gameState = MAIN_MENU_STATE;
int gameStateBef = -1;

Texture2D apple;
Texture2D banana;
Texture2D berry;
Texture2D head;
Texture2D tail;
Texture2D body;

void quit(){
	printf("test");
	endScore();
	endPlayer();
	endFood();

	UnloadTexture(apple);
	UnloadTexture(banana);
	UnloadTexture(berry);
	UnloadTexture(head);
	UnloadTexture(tail);
	UnloadTexture(body);

	CloseWindow();
}

// NOTE: DRAW FUNCTIONS
void playerBody(Node* aux, Texture2D texture){ // FIX: Add direc to player Node to rotate texture
	Rectangle image;

	Vector2 position = {
		(float) aux->x * TILE,
		(float) aux->y * TILE
	};
	image = (Rectangle) {
		(float)0,
		(float)0,
		(float)texture.width,
		(float)texture.height
	};

	float rotation = 0;

	switch(getPlayerDirec()){
		case UP:
			rotation = 0.0f;
			break;
		case DOWN:
			rotation = 180.0f;
			break;
		case LEFT:
			rotation = 270.0f;
			break;
		case RIGHT:
			rotation = 90.0f;
			break;
	}
	
	for(int i = 0; i < MULT_TD; i++){ // NOTE: Make sprite 3d -- it was made by accident
		DrawTexturePro(texture, 
			image,
			(Rectangle){
				position.x - i + (float)TILE/2,
				position.y - i + (float)TILE/2,
				(float)TILE,
				(float)TILE,
			},
			(Vector2){ (float) TILE/2, (float) TILE/2},
			rotation,
			RAYWHITE
		);
	}
}
void playerMove(){
	Node* aux = getPlayerHead();
	
	while(aux != NULL){
		if(aux->before == NULL){
			playerBody(aux, head);
		}
		else if(aux->next == NULL)
			playerBody(aux, tail);
		else
			playerBody(aux, body);

		aux = aux->next;
	}
}

void foodDraw(){
	Food* foods = getFoods();
	
	FNode* aux = foods->first;


	while(aux != NULL){
		Texture2D image = 
			strcmp(aux->special, "commun") == 0 ? apple : 
			strcmp(aux->special, "speedup") == 0 ? berry : 
			strcmp(aux->special, "speeddown") == 0 ? banana : 
			apple;

		for(int i = 0; i < MULT_TD; i++)
			DrawTextureRec(image, 
				(Rectangle){0,0, image.width, image.height}, 
				(Vector2){ 
					(float) aux->x * TILE + i, 
					(float) aux->y * TILE + i
				}, 
				RAYWHITE);

		aux = aux->next;
	}
}

void draw(){
	BeginDrawing();

	ClearBackground(RAYWHITE);

	playerMove();
	foodDraw();

	
	DrawText(TextFormat("Score %d", *getPlayerPts()), 10, 20 * 1, 18, ColorAlpha(BLACK, 0.5));
	DrawText(TextFormat("Highscore: %d", getHighscore()), 10, 20 * 2, 18, ColorAlpha(BLACK, 0.5));

	DrawText(TextFormat("Play time: %.3f", GetTime() - resetTime), 450, 20 * 1, 18, ColorAlpha(BLACK, 0.5));
	DrawText(TextFormat("Speed: %.3f", getPlayerSpeed()), 450, 20 * 2, 18, ColorAlpha(BLACK, 0.5));

	EndDrawing();
}

void resetFunc(){
	cleanFoods();
	cleanPlayer();
	
	resetTime = GetTime();
	pressed = false;
}
void pauseMenu(int input){
	if(input == 256){
		gameState = -1;
		
		return;
	}

	const int resume = 0, controlls = 1, mainMenu = 2, exit = 3;

	switch(input){
		case 74:
			option++;
			break;
		case 75:
			option--;
			break;
		case 257:
			switch(option){
				case 0: // NOTE: resume
					gameState = -1;
					option = 0;
					break;
				case 1: // TODO: controlls menu
					gameStateBef = gameState;
					gameState = CONTROLS_STATE;
					option = 0;
					break;
				case 2: // NOTE: mainMenu[WIP]
					resetFunc();

					gameState = MAIN_MENU_STATE;
					option = 0;
					break;
				case 3: // NOTE: exit
					quit();
					break;
			}
			break;
	}

	if(option > 3)
		option = resume;
	else if(option < 0)
		option = mainMenu;

	BeginDrawing();
	
	if(gameStateBef == PAUSE_STATE) ClearBackground(RAYWHITE);

	DrawText("PAUSE", 240, 160, 30, DARKGRAY);

	DrawRectangle(240, 200, 120, 20, option == resume ? LIGHTGRAY : RAYWHITE);
	DrawText("Continue", 250, 200, 20, option == resume ? DARKPURPLE : DARKGRAY);

	DrawRectangle(240, 220, 120, 20, option == controlls ? LIGHTGRAY : RAYWHITE);
	DrawText("controlls", 250, 220, 20, option == controlls ? DARKPURPLE : DARKGRAY);

	DrawRectangle(240, 240, 120, 20, option == mainMenu ? LIGHTGRAY : RAYWHITE);
	DrawText("Main Menu", 250, 240, 20, option == mainMenu ? DARKPURPLE : DARKGRAY);

	DrawRectangle(240, 260, 120, 20, option == exit ? LIGHTGRAY : RAYWHITE);
	DrawText("Exit", 250, 260, 20, option == exit ? DARKPURPLE : DARKGRAY);
	EndDrawing();
}

char username[20] = "";
Score newScore;
void newScoreMenu(int input){
	if(input == 256 || input == 257){
		newScore.pts = *getPlayerPts();
		strcpy(newScore.username, username);

		saveScore(newScore);
		gameStateBef = gameState;
		gameState = GAME_OVER_STATE;
		return;
	}

	if(input == 259){
		username[strlen(username)-1] = '\0';
	}
	else{
		char letter = input;
		strcat(username, &letter);
	}


	BeginDrawing();

	ClearBackground(RAYWHITE);
	
	DrawText(TextFormat("NEW SCORE: %d", *getPlayerPts()), 180, 220, 30, DARKGRAY);

	DrawText(TextFormat("USERNAME: %s", username), 180, 250, 20, DARKGRAY);

	DrawRectangle(240, 280, 120, 30, LIGHTGRAY);
	DrawText("SAVE", 260, 285, 20, DARKPURPLE);

	EndDrawing();
}
void gameOverMenu(int input){
	
	const int retry = 0, mainMenu = 1, exit = 2;

	switch(input){
		case 74:
			++option;
			break;
		case 75:
			--option;
			break;
		case 256:
			quit();
			break;
		case 257:
			switch(option){
				case 0: // NOTE: retry
					resetFunc();
					gameState = -1;
					option = 0;
					break;
				case 1: // NOTE: mainMenu[WIP]
					resetFunc();
					gameState = MAIN_MENU_STATE;
					option = 0;
					break;
				case 2: // NOTE: exit
					quit();
					break;
			}
			break;
	}

	if(option > 2)
		option = retry;
	else if(option < 0)
		option = mainMenu;

	BeginDrawing();

	if(gameStateBef == NEW_SCORE)
		ClearBackground(RAYWHITE);

	DrawText("GAME OVER", 200, 160, 30, DARKGRAY);
	DrawText(TextFormat("SCORE: %d", *getPlayerPts()), 200, 190, 15, DARKGRAY);

	DrawRectangle(240, 220, 120, 20, option == retry ? LIGHTGRAY : RAYWHITE);
	DrawText("Retry", 250, 220, 20, option == retry ? DARKPURPLE : DARKGRAY);

	DrawRectangle(240, 240, 120, 20, option == mainMenu ? LIGHTGRAY : RAYWHITE);
	DrawText("Main Menu", 250, 240, 20, option == mainMenu ? DARKPURPLE : DARKGRAY);

	DrawRectangle(240, 260, 120, 20, option == exit ? LIGHTGRAY : RAYWHITE);
	DrawText("Exit", 250, 260, 20, option == exit ? DARKPURPLE : DARKGRAY);
	EndDrawing();
}

void mainMenu(int input){
	const int start = 0, scores = 1, controlls = 2, exit = 3;

	switch(input){
		case 74:
			++option;
			break;
		case 75:
			--option;
			break;
		case 256:
			quit();
			break;
		case 257:
			switch(option){
				case 0: // NOTE: start
					gameState = -1;
					option = 0;
					break;
				case 1: // NOTE: scores
					gameStateBef = gameState;
					gameState = SCORE_STATE;
					option = 0;
					break;
				case 2: // NOTE: controlls
					gameStateBef = gameState;
					gameState = CONTROLS_STATE;
					option = 0;
					break;
				case 3: // NOTE: exit
					quit();
					break;
			}
			break;
	}

	if(option > 3)
		option = start;
	else if(option < 0)
		option = exit;

	BeginDrawing();

	ClearBackground(RAYWHITE);
	
	DrawText("SNAKE GAME", 200, 180, 30, DARKGRAY);

	DrawRectangle(240, 220, 120, 20, option == start ? LIGHTGRAY : RAYWHITE);
	DrawText("Start", 250, 220, 20, option == start ? DARKPURPLE : DARKGRAY);

	DrawRectangle(240, 240, 120, 20, option == scores ? LIGHTGRAY : RAYWHITE);
	DrawText("Scores", 250, 240, 20, option == scores ? DARKPURPLE : DARKGRAY);

	DrawRectangle(240, 260, 120, 20, option == controlls ? LIGHTGRAY : RAYWHITE);
	DrawText("controlls", 250, 260, 20, option == controlls? DARKPURPLE : DARKGRAY);

	DrawRectangle(240, 280, 120, 20, option == exit ? LIGHTGRAY : RAYWHITE);
	DrawText("Exit", 250, 280, 20, option == exit ? DARKPURPLE : DARKGRAY);
	EndDrawing();
}

void controllsMenu(int input){
	if(input == 256 || input == 257){
		gameState = gameStateBef;
		
		return;
	}

	BeginDrawing();

	ClearBackground(RAYWHITE);
	
	DrawText("CONTROLS", 200, 180, 30, DARKGRAY);

	DrawText("H - LEFT", 230, 220, 20, DARKGRAY);
	DrawText("J - DOWN", 230, 250, 20, DARKGRAY);
	DrawText("K - UP", 230, 270, 20, DARKGRAY);
	DrawText("L - RIGHT", 230, 300, 20, DARKGRAY);

	DrawText("ESC - PAUSE", 230, 340, 20, DARKGRAY);

	DrawRectangle(200, 400, 120, 20, LIGHTGRAY);
	DrawText("Back", 220, 400, 20, DARKPURPLE);
	EndDrawing();
}

void scoresMenu(int input){
	if(input == 256 || input == 257){
		gameState = gameStateBef;
		
		return;
	}

	BeginDrawing();

	ClearBackground(RAYWHITE);
	
	DrawText("SCORES", 200, 100, 30, DARKGRAY);

	for(int i = 0; i < getScoresSize(); i++){
		Score aux = getScoreByIndex(i);
		DrawText(TextFormat("%d - %s - %d", i+1, aux.username, aux.pts), 230, 170 + 20 * i, 20, DARKGRAY);
	}

	DrawRectangle(200, 400, 120, 20, LIGHTGRAY);
	DrawText("Back", 220, 400, 20, DARKPURPLE);
	EndDrawing();
}

// NOTE: LOGIC FUNCTIONS
bool canMove(){
	Node* head = getPlayerHead();
	int direc = getPlayerDirec();

	int windowOffset = 0;
	int windowLimit = GRID;

	if(head->x - (direc == LEFT ? 1 : 0) < windowOffset || 
		head->x + (direc == RIGHT ? 1 : 0) >= windowLimit ||
		head->y - (direc == UP ? 1 : 0) < windowOffset ||
		head->y + (direc == DOWN ? 1 : 0) >= windowLimit
	)
		return false;

	return true;
}

void death(){
	if(*getPlayerPts() > getScoreByIndex(getScoresSize()-1).pts)
		gameState = NEW_SCORE;
	else
		gameState = GAME_OVER_STATE;
}

// NOTE: MAIN FUNCTIONS
void loop(){
	int auxDirec = 0;
	int foodSpawnRate = getSpawnFoodRate();
	timer = GetTime();

	while(!WindowShouldClose()){
		auxDirec = GetKeyPressed();


		switch(gameState){
			case MAIN_MENU_STATE:
				mainMenu(auxDirec);
				continue;
			case GAME_OVER_STATE:
				gameOverMenu(auxDirec);
				continue;
			case PAUSE_STATE:
				pauseMenu(auxDirec);
				continue;
			case CONTROLS_STATE:
				controllsMenu(auxDirec);
				continue;
			case SCORE_STATE:
				scoresMenu(auxDirec);
				continue;
			case NEW_SCORE:
				newScoreMenu(auxDirec);
				continue;

		}

		draw();
		
		if(pressed == false){
			switch(auxDirec){
				case 72: 
					pressed = changeDirec(LEFT);
					break;
				case 74:
					pressed = changeDirec(DOWN);
					break;
				case 75:
					pressed = changeDirec(UP);
					break;
				case 76:
					pressed = changeDirec(RIGHT);
					break;
				case 86:
					speedUp(0.1f);
					break;
				case 67:
					speedDown(0.05f);
					break;
				case 71:
					grow();
					break;
				case 256:
					gameState = PAUSE_STATE;
					continue;
			}
		}
		
		if(getPlayerDirec() >= 0 && ((GetTime() - timer) > getPlayerSpeed())){
			
			
			if(canMove())
				move();
			else{
				death();
				continue;
			}

			pressed = false;
			timer = GetTime();

			if(autoHit()){
				death();
				continue;
			}

			char* aux = consumeFood(getPlayerHead()->x, getPlayerHead()->y, getPlayerPts());
			
			if(aux != NULL){
				grow();

				if(strcmp(aux, "speedup") == 0){
					speedUp(0.01f);
				}
				else if(strcmp(aux, "speeddown") == 0){
					speedDown(0.01f);
				}

				free(aux);
			}
			foodSpawnRate--;
		}

		if(foodSpawnRate <= 0){
			foodSpawn();
			foodSpawnRate = getSpawnFoodRate();
		}
	}
}
int main(int argc, char *argv[]) {

	if(!startPlayer() ||!startSpecialFood() || !startFood() || !loadScore()){
		printf("\nError on start!\n");
		return 1;
	}

	// NOTE: RAYLIB INIT
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake Game");
	SetExitKey(0);

	Image icon = LoadImage("assets/head.png");
	SetWindowIcon(icon);
	SetTargetFPS(FPS);

	apple = LoadTexture("assets/apple.png");
	banana = LoadTexture("assets/banana.png");
	berry = LoadTexture("assets/berry.png");

	head = LoadTexture("assets/head.png");
	tail = LoadTexture("assets/tail.png");
	body = LoadTexture("assets/body.png");
	
	UnloadImage(icon);

	if(gameState == PAUSE_STATE)
		pauseMenu(0);
	else
		loop();


	return 0;
}
