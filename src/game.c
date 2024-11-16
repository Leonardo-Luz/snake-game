#include <math.h>
#include <raylib.h>
#include <stdio.h>

#include "game.h"

#define GRID		20
#define SCREEN_WIDTH	600
#define SCREEN_HEIGHT	600
#define FPS		60

#define TILE		600/20

// NOTE: STOPED ON PLAYER GROW

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

void draw( int x, int y ){
	BeginDrawing();

	ClearBackground(RAYWHITE);

	DrawRectangle(x, y, TILE, TILE, YELLOW);
	DrawText("Hello World", TILE, TILE, 20, BLACK);

	playerMove();

	EndDrawing();
}

bool canMove(){
	Node* head = getPlayerHead();
	int direc = getPlayerDirec();

	if(head->x - (direc == LEFT ? 1 : 0) < 0 || // NOTE: POS X < 0
		head->x + (direc == RIGHT ? 1 : 0) >= GRID || // NOTE: POS X > 600 / 20
		head->y - (direc == UP ? 1 : 0) < 0 || // NOTE: POS Y < 0
		head->y + (direc == DOWN ? 1 : 0) >= GRID // NOTE: POS Y > 600 / 20
		|| autoHit()
	)
		return false;

	return true;
}

void loop(){
	int auxDirec = 0;
	
	timer = GetTime();

	while(!WindowShouldClose()){
		draw(round(timer) * TILE, round(timer) * TILE);

		

		auxDirec = GetCharPressed();

		switch((char) auxDirec){
			case 'h': 
				changeDirec(LEFT);
				break;
			case 'j':
				changeDirec(DOWN);
				break;
			case 'k':
				changeDirec(UP);
				break;
			case 'l':
				changeDirec(RIGHT);
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
		
		if(canMove() && ((GetTime() - timer) > getPlayerSpeed())){
			move();
			timer = GetTime();
		}
	}
}

int main(int argc, char *argv[]) {

	if(!startPlayer()){
		printf("\nError on start!\n");
		return 1;
	}

	// NOTE: RAYLIB INIT
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake Game");
	SetTargetFPS(FPS);

	loop();

	CloseWindow();

	return 0;
}
