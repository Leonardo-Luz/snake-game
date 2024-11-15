#include <stdlib.h>
#include <stdio.h>

#include "food.h"
//#include "map.h"

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
	
	return 1;
}

void endFood(){
	int i;
	for(i = 0; i < MAXFOOD; i++)
		free(foods[i]);

	free(foods);
}

void foodSpawn(){
	Food *food = (Food*) malloc(sizeof(Food));
	
	food->x = rand() % getCols();
	food->y = rand() % getRows();
	
	int random = rand() % 100;
	int i;
	if(rand >= 0 && rand <= getFoodSpecialChance())
	{
		random = rand() % 100;
		
	
		for(i = 0; i < MAXSPECIALFOOD; i++)
		{
			if(random <= specialFood[i].rarity)
			{
				food->pts = specialFood[i].pts;
				food->special = specialFood[i].name;
				return;				
			}
		}
	}
	
	food->pts = specialFood[0].pts;
	food->special = specialFood[0].name;
}

int consumeFood(int x, int y, int *pts){
	int i;
	for(i = 0; i < MAXFOOD; i++)
	{
		if(foods[i]->x == x && foods[i]->y == y){
			*pts += foods[i]->pts;
			free(foods[i]);
			foods[i] = NULL;
		}
	}
}




