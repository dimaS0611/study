// Created by Dzmitry Semianovich

// This file implements the
// functionality of basketball.c

#include "../include/basketball.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_players(struct Player* arr, int size)
{
	struct Player player;

	for (int i = 0; i < size; ++i)
	{
		printf("Enter the name of player: ");
		scanf("%s", player._name);

		printf("Enter date of birth: \n\tDay: ");
		scanf("%i", player._day);
		
		printf("\tMonth: ");
		scanf("%i", player._month);
		
		printf("\tYear: ");
		scanf("%i", player._year);
			
		printf("\nEnter the club name: ");
		scanf("%s", player._club);

		printf("\nEnter the role of a player: ");
		scanf("%s", player._type);
		
		printf("\nEnter the number of games: ");
		scanf("%i", &player._games);

		printf("\nEnter the number of point: ");
		scanf("%i", &player._points);

		printf("\nEnter the number of fouls: ");
		scanf("%i", &player._fouls);

		printf("\nEnter place of birth: ");
		scanf("%s", player._birthPlace);

		arr[i] = player;

		printf("\n");
	}
}

int compare_By_Age(const void* lsh, const void* rsh)
{
	struct Player* pl1 = (struct Player*)lsh;
	struct Player* pl2 = (struct Player*)rsh;

	int cmp = 0;

	if (pl1->_year == pl2->_year)
		cmp = 0;
	else if (pl1->_year < pl2->_year)
		cmp = -1;
	else
		cmp = 1;

	return cmp;
}

void sort_By_Age(struct Player* arr, int size)
{
	qsort(arr, size, sizeof(struct Player), compare_By_Age);
}


int compare_By_Points(const void* lsh, const void* rsh)
{
	struct Player* pl1 = (struct Player*)lsh;
	struct Player* pl2 = (struct Player*)rsh;

	int cmp = 0;

	if (pl1->_points == pl2->_points)
		cmp = 0;
	else if (pl1->_points < pl2->_points)
		cmp = -1;
	else
		cmp = 1;

	return cmp;
}

void sort_By_Points(struct Player* arr, int size)
{
	qsort(arr, size, sizeof(struct Player), compare_By_Points);
}

void info_PlayersU20(struct Player* arr, int size)
{
	printf("\nU20 players that score more than 18 points: ");

	for (int i = 0; i < size; ++i)
	{
		int age = 2021 - *arr[i]._year;
		int averagePoints = arr[i]._points / arr[i]._games;

		if (age < 20 && averagePoints > 18)
		{
			print_Info(arr[i]);
		}
	}

}

void info_Player_From_Vitebsk(struct Player* arr, int size)
{
	printf("\n\nPlayers from Vitebsk who don't have fouls: ");

	for (int i = 0; i < size; ++i)
	{
		int isVitebsk = strcmp("Vitebsk", arr[i]._birthPlace);
		
		if (isVitebsk == 0 && arr[i]._fouls == 0)
		{
			print_Info(arr[i]);
		}
	}
}

void youngest_Player(struct Player* arr, int size)
{
	printf("\n\nThe youngest player: ");

	sort_By_Age(arr, size);

	print_Info(arr[0]);
}

void max_Point_Player(struct Player* arr, int size)
{
	printf("\nPlayer with the most points: ");

	sort_By_Points(arr, size);

	print_Info(arr[size - 1]);
}

void print_Info(struct Player pl)
{
	printf("\nName: %s\nBirth place: %s\nClub: %s\nRole: %s\nGames: %d, Points: %d, Fouls: %d\n", 
		pl._name, pl._birthPlace, pl._club, pl._type, pl._games, pl._points, pl._fouls);
}
