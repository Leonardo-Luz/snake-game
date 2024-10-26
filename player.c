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
	player->speed = 50;
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
	
	player->last->next = growth;
}

void move(){
	switch(player->direc){
		case UP:
			player->head->y = player->head->y - 1;
			break;
		case DOWN:
			player->head->y = player->head->y + 1;
			break;
		case LEFT:
			player->head->x = player->head->x - 1;
			break;
		case RIGHT:
			player->head->x = player->head->x + 1;
			break;
	}
}

void changeDirec(int newDirec){	
	if(player->size == 1 || canChangeDirec(newDirec))
		player->direc = newDirec;
}

int canChangeDirec(int newDirec){
	return (
		(player->direc != UP && newDirec == DOWN) ||
		(player->direc != DOWN && newDirec == UP) ||
		(player->direc != LEFT && newDirec == RIGHT) ||
		(player->direc != RIGHT && newDirec == LEFT)
	);
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

int getPlayerDirec(){
	return player->direc;
}

int getPlayerSize(){
	return player->size;
}

Node* getHead(){
	return player->head;
}
