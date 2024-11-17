#include <math.h>
#include <raylib.h>
#include <stdio.h>

#include "game.h"

#define GRID		20
#define SCREEN_WIDTH	600
#define SCREEN_HEIGHT	600
#define FPS		60

#define TILE		600/20

// NOTE: GLOBAL VARIABLES
double timer = 0;

// NOTE: FUNCTIONS
void playerMove(){
	Node* aux = getPlayerHead();
	
	while(aux != NULL){
		DrawRectangle(aux->x * TILE, aux->y * TILE, TILE, TILE, BLACK);

		aux = aux->next;
	}
}

void foodDraw(){
	Food* foods = getFoods();
	
	FNode* aux = foods->first;

	while(aux != NULL){
		DrawRectangle(aux->x * TILE, aux->y * TILE, TILE, TILE, YELLOW);

		aux = aux->next;
	}
}

void draw( int x, int y ){
	BeginDrawing();

	ClearBackground(RAYWHITE);

	DrawRectangle(x, y, TILE, TILE, YELLOW);
	DrawText("H J K L - LEFT DOWN UP RIGHT", TILE, TILE, 20, BLACK);

	foodDraw();

	playerMove();

	EndDrawing();
}

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

void loop(){
	int auxDirec = 0;
	bool pressed = false;
	int foodSpawnRate = getSpawnFoodRate();

	timer = GetTime();

	while(!WindowShouldClose()){
		draw(round(timer) * TILE, round(timer) * TILE);


		auxDirec = GetCharPressed();

		if(pressed == false){
			switch((char) auxDirec){
				case 'h': 
					pressed = changeDirec(LEFT);
					break;
				case 'j':
					pressed = changeDirec(DOWN);
					break;
				case 'k':
					pressed = changeDirec(UP);
					break;
				case 'l':
					pressed = changeDirec(RIGHT);
					break;
				case 'v':
					speedUp(0.05f);
					break;
				case 'c':
					speedDown(0.05f);
					break;
				case 'g':
					grow();
					break;
			}
		}
		
		if(((GetTime() - timer) > getPlayerSpeed())){
			int* temp; // FIX: getPlayerPts() isnt working
			if(consumeFood(getPlayerHead()->x, getPlayerHead()->y, temp))
				grow();
			
			if(canMove())
				move();
			else
				CloseWindow();

			pressed = false;
			timer = GetTime();

			if(autoHit())
				CloseWindow();

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
	SetTargetFPS(FPS);

	loop();

	CloseWindow();

	// endPlayer();

	return 0;
}
