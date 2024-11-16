#include <stdlib.h>
#include <stdio.h>

#include "food.h"

int size;
Food **foods = NULL;

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
	foods = (Food**) malloc(sizeof(Food) * MAXFOOD);
	
	if(foods == NULL)
		return 0;
		
	int i;
	for(i = 0; i < MAXFOOD; i++){
		foods[i] = NULL;
	}

	size = 0;
	
	return 1;
}

void endFood(){
	int i;
	for(i = 0; i < MAXFOOD; i++)
		free(foods[i]);

	free(foods);
}

void foodSpawn(){
	if(size >= MAXFOOD)
		return;

	int random = rand() % 100;
	int i;

	Food *food = (Food*) malloc(sizeof(Food));
	
	food->x = rand() % 20;
	food->y = rand() % 20;

	for(i = 0; i < size; i++)
		while(food->x == foods[i]->x && food->y == foods[i]->y){
			food->x = rand() % 20;
			food->y = rand() % 20;
		}

	
	if(random >= 0 && random <= 100)
	{
	
		for(i = MAXSPECIALFOOD; i >= 0; i--)
		{
			if(random >= specialFood[i].rarity)
			{
				food->pts = specialFood[i].pts;
				food->special = specialFood[i].name;
				foods[size] = food;

				size++;
				return;
			}
		}
	}
	
	food->pts = specialFood[0].pts;
	food->special = specialFood[0].name;

	foods[size] = food;

	size++;
}

int consumeFood(int x, int y, int *pts){ // FIX: consuming foods[i] is letting a gap inside the array change to linked list
	int i;
	for(i = 0; i < MAXFOOD; i++){
		if(foods[i] != NULL && foods[i]->x == x && foods[i]->y == y){
			// (*pts) += foods[i]->pts;
			free(foods[i]);
			foods[i] = NULL;
			size--;
			return 1;
		}
	}

	return 0;
}

Food** getFoods(){
	return foods;
}

int getSize(){
	return size;
}

