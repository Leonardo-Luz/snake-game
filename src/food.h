
#define MAXFOOD 5
#define MAXSPECIALFOOD 3

typedef struct FNode{
	int x;
	int y;
	int pts;
	char *special;
	struct FNode* next;
	struct FNode* before;
}FNode;

typedef struct Special{
	int rarity;
	int pts;
	char name[20];
}Special;

typedef struct Food{
	int max;
	int size;
	int spawnRate;
	struct FNode* first;
	struct FNode* last;
}Food;


int startFood();
void endFood();

void foodSpawn();

int consumeFood(int x, int y, int *pts);

Food* getFoods();
int getFoodSize();
int getFoodMax();
int getSpawnFoodRate();
