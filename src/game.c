#include <raylib.h>

#define SCREEN_WIDTH	600
#define SCREEN_HEIGHT	600
#define FPS		60

int main(int argc, char *argv[]) {
	
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake Game");
	SetTargetFPS(FPS);

	while(!WindowShouldClose()){
		
		BeginDrawing();

		ClearBackground(RAYWHITE);

		DrawText("Hello World", 250, 200, 20, BLACK);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
