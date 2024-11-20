
typedef struct Score{
	char username[20];
	int pts;
}Score;

int loadScore();
int saveScore(Score newScore);

Score* getScores();
void endScore();
int getScoresSize();
int getHighscore();
