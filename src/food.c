#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "food.h"

Food *foods = NULL;

Special specialFood[MAXSPECIALFOOD] = {
	{
		0,
		10,
		"comun"
	},
	{
		65,
		20,
		"speedup"
	},
	{
		35,
		-5,
		"speeddown"
	}
};

int startFood(){
	foods = (Food*) malloc(sizeof(Food));
	
	if(foods == NULL)
		return 0;
	
	foods->max = MAXFOOD;
	foods->last = NULL;
	foods->first = NULL;
	foods->size = 0;
	foods->spawnRate = 5;
	
	return 1;
}

void endFood(){ // FIX:
	free(foods);
}

FNode* find(FNode* target){
	FNode* aux = foods->first;

	while(aux != NULL){
		if(aux->x == target->x && aux->y == target->y)
			return aux;

		aux = aux->next;
	}

	return aux;
}

void insert(FNode* target){
	if(foods->last != NULL){
		foods->last->next = target;
		target->before = foods->last;
	}
	else{
		foods->first = target;
	}

	foods->last = target;
	foods->size++;
}

FNode* pop(int x, int y){ // FIX:
	if(foods->size == 0)
		return NULL;

	FNode* aux = foods->first;

	if(foods->size == 1 && aux->x == x && aux->y == y){
		foods->first = NULL;
		foods->last = NULL;

		foods->size--;

		return aux;
	}

	while (aux != NULL) {
		if(aux->x == x && aux->y == y){
			int pts = aux->pts;

			if(aux->next == NULL){
				foods->last = foods->last->before;
				foods->last->next = NULL;
				foods->size--;

				return aux;
			}

			FNode* temp = aux;

			aux = aux->next; // aux->next is never null
			aux->before = temp->before;

			if(temp->before == NULL) 
				foods->first = aux;
			else
				temp->before->next = aux;

			foods->size--;

			return temp;
		}

		aux = aux->next;
	}

	return NULL;
}

void foodSpawn(){
	if(foods->size >= foods->max)
		return;

	int random = rand() % 100;
	int i;

	FNode *food = (FNode*) malloc(sizeof(FNode));
	
	food->x = rand() % 20;
	food->y = rand() % 20;

	food->next = NULL;
	food->before = NULL;

	while(find(food) != NULL){
		food->x = rand() % 20;
		food->y = rand() % 20;
	}
	
	if(random >= 0 && random <= 100)
		for(i = MAXSPECIALFOOD; i >= 0; i--)
		{
			if(random >= specialFood[i].rarity)
			{
				food->pts = specialFood[i].pts;
				food->special = specialFood[i].name;

				insert(food);
				return;
			}
		}
	
	food->pts = specialFood[0].pts;
	food->special = specialFood[0].name;
}

char* consumeFood(int x, int y, int *pts){
	FNode* aux = pop(x, y);

	if(aux == NULL)
		return NULL;

	char* special = aux->special;

	(*pts)+= aux->pts;

	free(aux);
	return special;
}

Food* getFoods(){
	return foods;
}

int getFoodSize(){
	return foods->size;
}
int getFoodMax(){
	return foods->max;
}

int getSpawnFoodRate(){
	return foods->spawnRate;
}

