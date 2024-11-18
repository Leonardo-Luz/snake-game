#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "../include/food.h"

Food *foods = NULL;

Special* specialFood = NULL;

int startSpecialFood(){
	specialFood = (Special*) malloc(sizeof(Special) * MAXSPECIALFOOD);

	specialFood[0].pts = 10;
	specialFood[0].rarity = 0;
	specialFood[0].name = (char*) malloc(sizeof(char) * 20);
	strcpy(specialFood[0].name, "commun");

	specialFood[1].rarity = 35;
	specialFood[1].pts = 5;
	specialFood[1].name = (char*) malloc(sizeof(char) * 20);
	strcpy(specialFood[1].name, "speeddown");

	specialFood[2].rarity = 65;
	specialFood[2].pts = 20;
	specialFood[2].name = (char*) malloc(sizeof(char) * 20);
	strcpy(specialFood[2].name, "speedup");

	return 1;
}
int startFood(){
	foods = (Food*) malloc(sizeof(Food));
	
	if(foods == NULL)
		return 0;
	
	foods->max = 5;
	foods->last = NULL;
	foods->first = NULL;
	foods->size = 0;
	foods->spawnRate = 5;
	
	return 1;
}

void cleanFoods(){
	printf("\nTEST");

	FNode* aux = foods->last;

	if(aux == NULL)
		return;

	while(aux->before != NULL){
		aux = aux->before;

		printf("\nTEST %d", aux->x);

		free(aux->next->special);
		free(aux->next);
	}

	printf("\nTESTF %d", foods->first->x);
	free(foods->first->special);
	free(foods->first);

	foods->size = 0;
}

void endFood(){ // FIX:
	cleanFoods();
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

FNode* pop(int x, int y){
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
			if(aux->next == NULL){
				foods->last = foods->last->before;
				foods->last->next = NULL;
				foods->size--;

				return aux;
			}

			FNode* temp = aux;

			aux = aux->next;
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

	
	food->special = (char*) malloc(sizeof(char) * 20);

	while(find(food) != NULL){
		food->x = rand() % 20;
		food->y = rand() % 20;
	}
	
	if(random >= 0 && random <= 100)
		for(i = MAXSPECIALFOOD -1; i >= 0; i--)
		{
			if(random >= specialFood[i].rarity)
			{
				food->pts = specialFood[i].pts;
				strcpy(food->special, specialFood[i].name);

				insert(food);
				return;
			}
		}
}

char* consumeFood(int x, int y, int *pts){
	FNode* aux = pop(x, y); // FIX: rename to Remove();

	if(aux == NULL)
		return NULL;

	char* special = (char*) malloc(sizeof(char) * 20);
	strcpy(special, aux->special);

	(*pts) += aux->pts;
	
	free(aux->special);
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

