#include <stdlib.h>
#include <string.h>
#include <raylib.h>
#include <stdio.h>

#include "../include/game.h"

#define CONTINUE	0
#define CONTROLLS	1
#define MAIN_MENU	2

#define GRID		20
#define SCREEN_WIDTH	600
#define SCREEN_HEIGHT	600
#define FPS		60

#define TILE		SCREEN_HEIGHT/GRID

// NOTE: GLOBAL VARIABLES
double timer = 0;
bool pause = false;
int option = CONTINUE;

// NOTE: DRAW FUNCTIONS
void playerBody(Node* aux, Texture2D texture){ // FIX: Add direc to player Node
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

	DrawTexturePro(texture, 
		image,
		(Rectangle){
			position.x + (float)TILE/2,
			position.y + (float)TILE/2,
			(float)TILE,
			(float)TILE,
		},
		(Vector2){ (float) TILE/2, (float) TILE/2},
		rotation,
		RAYWHITE
	);


}
void playerMove(Texture2D head, Texture2D tail, Texture2D body){
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

void foodDraw(Texture2D apple, Texture2D banana, Texture2D berry){
	Food* foods = getFoods();
	
	FNode* aux = foods->first;


	while(aux != NULL){
		Texture2D image = strcmp(aux->special, "commun") == 0 ? apple : strcmp(aux->special, "speedup") == 0 ? berry : strcmp(aux->special, "speeddown") == 0 ? banana : apple;

		DrawTextureRec(image, (Rectangle){0,0, image.width, image.height}, (Vector2){ (float) aux->x * TILE, (float) aux->y * TILE }, RAYWHITE);

		aux = aux->next;
	}
}

void draw(Texture2D apple, Texture2D banana, Texture2D berry, Texture2D head, Texture2D tail, Texture2D body){
	BeginDrawing();

	ClearBackground(RAYWHITE);

	DrawText("H J K L - MOVE", 10, 0, 20, BLACK);
	DrawText(TextFormat("Score %d", *getPlayerPts()), 10, 20 * 1, 18, BLACK);
	DrawText(TextFormat("Highscore: %f", getPlayerSpeed()), 10, 20 * 2, 18, BLACK);

	DrawText(TextFormat("Speed: %.3f", getPlayerSpeed()), 450, 0, 18, BLACK);
	DrawText(TextFormat("Play time: %.3f", GetTime()), 450, 20 * 1, 18, BLACK);
	foodDraw(apple, banana, berry);

	playerMove(head, tail, body);

	EndDrawing();
}

void pauseMenu(int input){
	switch(input){
		case 74:
			option++;
			break;
		case 75:
			option--;
			break;
		case 257:
			switch(option){
				case CONTINUE:
					pause = !pause;
					break;
				case CONTROLLS: // TODO:
					printf("\nWIP");
					break;
				case MAIN_MENU:
					CloseWindow();
					break;

			}
			break;
	}

	if(option > 2)
		option = CONTINUE;
	else if(option < 0)
		option = MAIN_MENU;


	BeginDrawing();
	
	DrawRectangle(240, 200, 120, 20, option == CONTINUE ? LIGHTGRAY : RAYWHITE);
	DrawText("Continue", 250, 200, 20, option == CONTINUE ? YELLOW : DARKGRAY);

	DrawRectangle(240, 220, 120, 20, option == CONTROLLS ? LIGHTGRAY : RAYWHITE);
	DrawText("Controlls", 250, 220, 20, option == CONTROLLS ? YELLOW : DARKGRAY);

	DrawRectangle(240, 240, 120, 20, option == MAIN_MENU ? LIGHTGRAY : RAYWHITE);
	DrawText("Main Menu", 250, 240, 20, option == MAIN_MENU ? YELLOW : DARKGRAY);
	EndDrawing();
}

void gameOverMenu(){

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

// NOTE: MAIN FUNCTIONS
void loop(Texture2D apple, Texture2D banana, Texture2D berry, Texture2D head, Texture2D tail, Texture2D body){
	int auxDirec = 0;
	bool pressed = false;
	int foodSpawnRate = getSpawnFoodRate();

	timer = GetTime();

	while(!WindowShouldClose()){
		auxDirec = GetKeyPressed();

		if(auxDirec == 256){
			pause = !pause;
		}

		if(pause){
			pauseMenu(auxDirec);

			continue;
		}

		draw(apple, banana, berry, head, tail, body);
		
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
			}
		}
		
		if(((GetTime() - timer) > getPlayerSpeed())){
			
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
			
			if(canMove())
				move();
			else
				CloseWindow();

			pressed = false;
			timer = GetTime();

			if(autoHit()){
				CloseWindow();
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

	if(!startPlayer() || !startFood()){
		printf("\nError on start!\n");
		return 1;
	}

	// NOTE: RAYLIB INIT
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake Game");
	SetExitKey(0);

	// NOTE: Image Load
	Image icon = LoadImage("assets/head.png");

	Texture2D apple = LoadTexture("assets/Apple.png");
	Texture2D banana = LoadTexture("assets/Banana.png");
	Texture2D berry = LoadTexture("assets/blueberry.png");

	Texture2D head = LoadTexture("assets/head.png");
	Texture2D tail = LoadTexture("assets/tail.png");
	Texture2D body = LoadTexture("assets/body.png");
	
	SetWindowIcon(icon);
	SetTargetFPS(FPS);
	UnloadImage(icon);

	if(pause)
		pauseMenu(0);
	else
		loop(apple, banana, berry, head, tail, body);

	endPlayer();

	// NOTE: Image unload
	UnloadTexture(apple);
	UnloadTexture(banana);
	UnloadTexture(berry);
	UnloadTexture(head);
	UnloadTexture(tail);
	UnloadTexture(body);

	return 0;
}
