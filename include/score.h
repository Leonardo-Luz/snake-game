#define MAXSCORE 10

typedef struct Score{
	char username[20];
	int pts;
}Score;

int loadScore();
int saveScore(Score newScore);

Score* getScores();
Score getScoreByIndex(int index);
void endScore();
int getScoresSize();
int getHighscore();
