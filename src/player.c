#include <stdio.h>
#include <stdlib.h>

#include "player.h"

Player *player = NULL;

int startPlayer(){
	player = (Player*) malloc(sizeof(Player));
	
	if(player == NULL)
		return 0;
		
	Node *head = NULL;
	
	head = (Node*) malloc(sizeof(Node));

	if(head == NULL)
		return 0;
	
	
	//Player Initial Position
	head->x = 0;
	head->y = 0;
	head->before = NULL;
	head->next = NULL;
	
	player->pts = 0;
	player->size = 1;
	player->speed = 1;
	player->direc = -1;

	player->head = head;
	player->last = head;
	
	return 1;
}

void endPlayer(){
	Node *aux = player->last->before;
	
	int i;
	for(i = player->size; i > 0; i--)
	{
		if(i == 1)
		{
			free(player->head);
			break;
		}
				
		free(aux->next);
		aux = aux->before;
	}

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
	return ( // FIX: If I input down left when i was going right snake goes through its own body
		(player->direc != UP && newDirec == DOWN) ||
		(player->direc != DOWN && newDirec == UP) ||
		(player->direc != LEFT && newDirec == RIGHT) ||
		(player->direc != RIGHT && newDirec == LEFT)
	);
}

void changeDirec(int newDirec){	
	if(player->size == 1 || canChangeDirec(newDirec))
		player->direc = newDirec;
}

int autoHit(){
	Node *aux = player->head->next;
	
	while(aux != NULL){ // FIX: Snake growns inside her self, making it to stop on spot
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
