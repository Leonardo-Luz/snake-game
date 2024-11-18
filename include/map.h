

typedef struct Tile{
	int x;
	int y;
	char *type;
}Tile;

typedef struct{
	int rows;
	int cols;
	int mapSize;
	int tileSize;
	int qtyTunels;
	int foodSpawnRate;
	int foodSpecialChance;
	struct Tile* tiles;
}Map;

typedef struct Tunel{
	int x;
	int y;
	int direc;
	struct Tunel *exit;
}Tunel;

int startMap();
void endMap();

int loadMap();

int moveCheck(int *x, int *y, int *direc)

int getRows();
int getCols();
int getMapSize();
int getTileSize();

int getFoodSpawnRate();
int getFoodSpecialChance();

