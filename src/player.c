#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "player.h"

Player *player = NULL;

int startPlayer(){
	srand(time(NULL));

	player = (Player*) malloc(sizeof(Player));
	
	if(player == NULL)
		return 0;
		
	Node *head = NULL;
	
	head = (Node*) malloc(sizeof(Node));

	if(head == NULL)
		return 0;
	
	head->x = -1;
	head->y = -1;

	int windowOffset = 0;
	int windowLimit = 20;

	while(head->x < windowOffset || head->x > windowLimit || head->y < windowOffset || head->y > windowLimit ){
		head->x = rand() % 20;
		head->y = rand() % 20;
	}

	head->before = NULL;
	head->next = NULL;
	
	player->pts = 0;
	player->size = 1;
	player->speed = 0.6;
	player->direc = rand() % 4;

	player->head = head;
	player->last = head;
	
	return 1;
}

void endPlayer(){
	Node *aux = player->last->before;
	
	while(aux->before != NULL)
	{
		free(aux->next);
		aux = aux->before;
	}

	free(player->head);
	free(player);
}

void grow(){
	Node *growth = (Node*) malloc(sizeof(Node));
	
	growth->next = NULL;
	growth->before = player->last;

	growth->x = player->last->x;
	growth->y = player->last->y;
	
	player->size++;

	player->last->next = growth;
	player->last = growth;
}

void moveBody(int x, int y){
	Node* aux = player->last;

	while(aux->before != NULL){
		aux->x = aux->before->x;
		aux->y = aux->before->y;

		aux = aux->before;
	}

	aux->x = aux->x + x;
	aux->y = aux->y + y;
}

void move(){
	switch(player->direc){
		case UP:
			moveBody( 0, -1 );
			break;
		case DOWN:
			moveBody( 0, 1 );
			break;
		case LEFT:
			moveBody( -1, 0 );
			break;
		case RIGHT:
			moveBody( 1, 0 );
			break;
	}
}

int canChangeDirec(int newDirec){
	return (
		(player->direc != UP && newDirec == DOWN) ||
		(player->direc != DOWN && newDirec == UP) ||
		(player->direc != LEFT && newDirec == RIGHT) ||
		(player->direc != RIGHT && newDirec == LEFT)
	);
}

int changeDirec(int newDirec){	
	if(player->size == 1 || canChangeDirec(newDirec)){
		player->direc = newDirec;
		return 1;
	}

	return 0;
}

int autoHit(){
	Node *aux = player->head->next;
	
	while(aux != NULL){
		if(aux->x == player->head->x && aux->y == player->head->y)
			return 1;

		aux = aux->next;
	}
	
	return 0;
}

void speedUp(double num){
	player->speed -= num;
}
void speedDown(double num){
	player->speed += num;
}

double getPlayerSpeed(){
	return player->speed;
}

int getPlayerDirec(){
	return player->direc;
}

int getPlayerSize(){
	return player->size;
}

Node* getPlayerHead(){
	return player->head;
}

int getPlayerPts(){
	return player->pts;
}
