
#define MAXFOOD 3
#define MAXSPECIALFOOD 3

typedef struct Food{
	int x;
	int y;
	int pts;
	char *special;
}Food;

typedef struct Special{
	int rarity;
	int pts;
	char name[20];
}Special;

int startFood();
void endFood();

void foodSpawn();

int consumeFood(int x, int y, int *pts);

Food** getFoods();
