#include "../include/score.h"
#include <stdio.h>
#include <stdlib.h>

#define MAXSCORE 10

Score* scores;
int size = 0;
FILE* scoreFile = NULL;

void sort(){
	if(size == 0)
		return;

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
		fread(&scores[i], sizeof(Score), 1, scoreFile);
	}

	sort();

	return 1;
}

int saveScore(Score newScore){
	if(newScore.pts == 0) return 0;

	if(size > MAXSCORE -1 && newScore.pts > scores[size-1].pts){
		scores[size-1] = newScore;

		sort();

		return 1;
	}
	else if(size > MAXSCORE -1){
		return 0;
	}

	scores[size] = newScore;
	size++;

	sort();

	return 1;
}

void endScore(){
	rewind(scoreFile);
	
	for(int i = 0; i < size; i++)
		fwrite(&scores[i], sizeof(Score), 1, scoreFile);

	fclose(scoreFile);
	free(scores);
}

Score* getScores(){
	return scores;
}

Score getScoreByIndex(int index){
	return scores[index];
}

int getScoresSize(){
	return size;
}

int getHighscore(){
	if(size == 0)
		return 0;

	return scores[0].pts;
}
