#include "../include/score.h"
#include <stdio.h>
#include <stdlib.h>

#define MAXSCORE 10

Score* scores;
int size = 0;
FILE* scoreFile = NULL;

void sort(){
	for(int i = 0; i < size-1; i ++)
		for(int j = i + 1; j < size; j++){
			if(scores[i].pts < scores[j].pts){
				Score aux = scores[j];
				scores[j] = scores[i];
				scores[i] = aux;
			}
		}
}

int loadScore(){
	scores = (Score*) malloc(sizeof(Score) * 10);

	scoreFile = fopen("scores", "r+");

	if(scoreFile == NULL){
		scoreFile = fopen("scores", "w+");

		if(scoreFile == NULL)
			return 0;
	}

	fseek(scoreFile, 0, SEEK_END);

	size = ftell(scoreFile) / sizeof(Score); // FIX: Not working properly

	rewind(scoreFile);


	for(int i = 0; i < size; i++){
		fread(&scores[i], sizeof(Score), i, scoreFile);
	}

	printf("\nSize: %d", size);

	sort();

	return 1;
}

int saveScore(Score newScore){
	printf("\nSIZE: %d\n", size);
	printf("\nTEST SCORE : %d", newScore.pts);

	if(newScore.pts == 0) return 0;
	
	if(size > MAXSCORE -1 && newScore.pts > scores[size].pts){
		scores[size] = newScore;

		printf("\n\n!INSIDE ARRAY: %d", scores[size].pts);

		return 1;
	}
	else if(size > MAXSCORE -1){
		return 0;
	}
	scores[size] = newScore;
	printf("\n\n!INSIDE ARRAY: %d", scores[size].pts);
	size++;

	sort();

	printf("\nSCORE ENTER");

	return 1;
}

void endScore(){
	printf("\nTESTE3\n");
	for(int i = 0; i < size; i++)
		fwrite(&scores[i], sizeof(Score), 1, scoreFile);

	printf("\nTESTE4\n");
	fclose(scoreFile);
}

Score* getScores(){
	return scores;
}

int getScoresSize(){
	return size;
}

int getHighscore(){
	if(size == 0)
		return 0;

	return scores[0].pts;
}
