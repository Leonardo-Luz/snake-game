
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

typedef struct Node{
	int x;
	int y;
	struct Node *before;
	struct Node *next;
}Node;

typedef struct{
	int size;
	int pts;
	double speed;
	int direc;
	struct Node *head;
	struct Node *last;
}Player;

int startPlayer();
void endPlayer();

void loadPlayer(); //talvez n exista

void grow();
void move();
void changeDirec(int newDirec);
int autoHit();

void speedUp(double num);
void speedDown(double num);

double getPlayerSpeed();
int getPlayerPts();
int getPlayerDirec();
int getPlayerSize();
Node* getPlayerHead();

