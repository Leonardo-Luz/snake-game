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

int pop(int x, int y){ // FIX:
	if(foods->size == 0)
		return 0;

	FNode* aux = foods->first;

	if(foods->size == 1 && aux->x == x && aux->y == y){
		foods->first = NULL;
		foods->last = NULL;

		foods->size--;
		free(aux);

		return 1;
	}

	while (aux != NULL) {
		if(aux->x == x && aux->y == y){
			int pts = aux->pts;

			if(aux->next == NULL){
				foods->last = foods->last->before;
				foods->last->next = NULL;
				foods->size--;

				free(aux);

				return 1;
			}

			FNode* temp = aux;

			aux = aux->next; // aux->next is never null
			aux->before = temp->before;

			if(temp->before == NULL) // FIX: Enters on a infinite loop or crashes when eats a middle food
				foods->first = aux;

			foods->size--;
			free(temp);
			return 1; // FIX: Should return points
		}

		aux = aux->next;
	}

	return 0;
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

int consumeFood(int x, int y, int *pts){ // FIX: consuming foods[i] is letting a gap inside the array change to linked list
	int aux = pop(x, y);

	(*pts)+= aux;
	return aux;
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

