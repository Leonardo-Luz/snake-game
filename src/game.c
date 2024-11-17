#include <stdlib.h>
#include <string.h>
#include <raylib.h>
#include <stdio.h>

#include "game.h"

#define GRID		20
#define SCREEN_WIDTH	600
#define SCREEN_HEIGHT	600
#define FPS		60

#define TILE		SCREEN_HEIGHT/GRID

// NOTE: GLOBAL VARIABLES
double timer = 0;

// NOTE: FUNCTIONS
void playerBody(Node* aux, Texture2D texture){
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

	DrawText("H J K L - LEFT DOWN UP RIGHT", TILE, TILE, 20, BLACK);
	DrawText(TextFormat("Points %d", *getPlayerPts()), TILE, TILE * 2, 18, BLACK);
	DrawText(TextFormat("Speed %f", getPlayerSpeed()), TILE, TILE * 3, 18, BLACK);

	foodDraw(apple, banana, berry);

	playerMove(head, tail, body);

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

void loop(Texture2D apple, Texture2D banana, Texture2D berry, Texture2D head, Texture2D tail, Texture2D body){
	int auxDirec = 0;
	bool pressed = false;
	int foodSpawnRate = getSpawnFoodRate();

	timer = GetTime();

	while(!WindowShouldClose()){
		draw(apple, banana, berry, head, tail, body);


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

	// NOTE: Image Load
	Image icon = LoadImage("src/images/head.png");

	Texture2D apple = LoadTexture("src/images/Apple.png");
	Texture2D banana = LoadTexture("src/images/Banana.png");
	Texture2D berry = LoadTexture("src/images/blueberry.png");

	Texture2D head = LoadTexture("src/images/head.png");
	Texture2D tail = LoadTexture("src/images/tail.png");
	Texture2D body = LoadTexture("src/images/body.png");
	
	SetWindowIcon(icon);
	SetTargetFPS(FPS);
	UnloadImage(icon);

	loop(apple, banana, berry, head, tail, body);

	CloseWindow();

	// endPlayer();

	// NOTE: Image unload
	UnloadTexture(apple);
	UnloadTexture(banana);
	UnloadTexture(berry);
	UnloadTexture(head);
	UnloadTexture(tail);
	UnloadTexture(body);

	return 0;
}
