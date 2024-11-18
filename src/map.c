#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/map.h"

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

Map *map = NULL;
Tile *tiles = NULL;
Tunel **tunels = NULL;
FILE *mapArchive = NULL;

int startMap(){
	map = (Map*) malloc(sizeof(Map));
	if(map == NULL)
		return 0;
		
	map->cols = 0;
	map->rows = 0;
	map->tileSize = 0;
	map->qtyTunels = 0;
	map->foodSpawnRate = 0f;
	map->foodSpecialChance = 0f;
	map->mapSize = (map->cols * map->rows) * map->tileSize;
	
	tunels = (Tunel**) malloc(sizeof(Tunel) * map->qtyTunels);
	if(tunels == NULL)
		return 0;
	
	tiles = (Tile*) malloc(sizeof(Tile) * (map->rows * map->cols));
	if(tiles == NULL)
		return 0;
	
	map->tiles = tiles;
	
	return 1;
}
void endMap(){
	free(tiles);
	free(tunels);
	free(map);
}

int loadMap(char *mapName){
	mapArchive = fopen( mapName , "r" );
	if(mapArchive == NULL)
		return 0;
		
	rewind(mapArchive);
	
	char *buffer;

	fgets(buffer, 100 ,mapArchive);
	map->cols = (int)(buffer - '0');

	fgets(buffer, 100 ,mapArchive);
	map->rows = (int)(buffer - '0');
	
	fgets(buffer, 100 ,mapArchive);
	map->qtyTunels = (int)(buffer - '0');

	fgets(buffer, 100 ,mapArchive);
	map->foodSpawnRate = (int)(buffer - '0');

	fgets(buffer, 100 ,mapArchive);
	map->foodSpecialChance = (int)(buffer - '0');

	
	map->mapSize = (map->cols * map->rows) * map->tileSize;

	tunels = (Tunel**) malloc(sizeof(Tunel) * map->qtyTunels);
	if(tunels == NULL)
		return 0;
		
	int i;
	for(i = 0; i < map->qtyTunels; i++)
	{
		tunels[i] = (Tunel*) malloc(sizeof(Tunel));

		tunels[i]->direc = -1;
		tunels[i]->exit = NULL;
	}
	
	tiles = (Tile*) malloc(sizeof(Tile) * (map->rows * map->cols));
	if(tiles == NULL)
		return 0;
	
	map->tiles = tiles;

	int y = 0; //maybe start in 1
	int count = 0;
	while(fgets(buffer, map->cols * 2 ,mapArchive) != NULL)
	for(i = 0; i < strlen(buffer); i++)
	{
		map->tiles[count].x = i;
		map->tiles[count].y = y;
		
		map->tiles[count].type = (char*) malloc(sizeof(char) * 20);
		
		switch(buffer[i]){
			case '#':
				strcpy(map->tiles->type, "wall");
				break;	
		}
		
		if(map->tiles[count].type - '0' >= 0 && map->tiles[count].type - '0' < map->qtyTunels)
			if(tunels[map->tiles->type - '0']->direc == -1)
			{
				tunels[map->tiles->type - '0']->direc == 0;
				tunels[map->tiles->type - '0']->x = i;
				tunels[map->tiles->type - '0']->y = y;
				tunels[map->tiles->type - '0']->exit = NULL;
			}
			else
			{
				Tunel *exit = (Tunel*) malloc(sizeof(Tunel));
				
				exit->x = i;
				exit->y = y;
				exit->exit = tunels[map->tiles->type - '0'];
				
				tunels[map->tiles->type - '0']->exit = exit;
			}
		
		count++;
	}

	return 1;
}

int moveCheck(int *x, int *y, int *direc){
	int i;
	for(i = 0; i < map->tiles; i++)
	{
		if(map->tiles[i]->x == *x && map->tiles[i]->y == *y)
		{
			switch(map->tiles->type){
				case "floor":
					return 1;
					break;
				case "wall":
					printf("\nMorreu");
					return 0;
					break;
				case "tunel":
					return moveTunel(&x , &y, &direc, map->tiles[i]);
					break;
				case "door":
					printf("\nGanhou!");
					return 1;
					break;
			}
		}
	}
	return 1;
}

int moveTunel(int *x, int *y, int *direc, Tile tile){
	int i;
	for(i = 0; i < map->qtyTunels; i++){
		if(tile->x == tunels[i]->x && tile->y == tunels[i]->y){
			if(
				(*direc == UP && tunels[i]->direc == DOWN) ||
				(*direc == DOWN && tunels[i]->direc == UP) ||
				(*direc == LEFT && tunels[i]->direc == RIGHT) ||
				(*direc == RIGHT && tunels[i]->direc == LEFT)
			)
			{
				*x = tunels[i]->exit->x;
				*y = tunels[i]->exit->y;
				*direc = tunels[i]->exit->direc;
				
				switch(*direc){
					case UP:
						*y--;
						break;
					case DOWN:
						y++;
						break;
					case LEFT:
						x--;
						break;
					case RIGHT:
						x++;
						break;
				}
				return 1;	
			}
			else
				return 0;
			}	
		}
	}
	return 0;
}

int getRows(){
	return map->rows;
}

int getCols(){
	return map->cols;
}

int getMapSize(){
	return map->mapSize;
}

int getTileSize(){
	return map->tileSize;
}

int getFoodSpawnRate(){
	return map->foodSpawnRate;
}

int getFoodSpecialChance(){
	return map->foodSpecialChance;
}

