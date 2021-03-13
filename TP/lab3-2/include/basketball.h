// Created by Dzmitry Semianovich
 
// There is the struct that describe
// a basketball player
 
#pragma once
struct Player
{
    int _day[2];		// Date of birth
    int _month[2];
    int _year[2];
	
	char _name[30];		// Name of the palyer
	char _club[50];		// Clud of the player
	char _type[20];		// Position of the player

	int _games;		// Number of games
	int _points;		// Number of points per season
	int _fouls;		// Number of fouls per season

	char _birthPlace[50]; 	// Place of birth
};

void init_players(struct Player* arr, int size);  		// Function that init array of players structs

void info_PlayersU20(struct Player* arr, int size);		// Function that distpays info about players U20 
								// who score more than 18 points per game 

void info_Player_From_Vitebsk(struct Player* arr, int size); 	// Function that displays info about players from Vitebsk
								// who have 0 fouls per seasson

void youngest_Player(struct Player* arr, int size);		// Function that displays info about the youngest player

void max_Point_Player(struct Player* arr, int size);		// Function that displays info about the player who have 
								//max amount of points per season 

void print_Info(struct Player pl);				// Function that print info

