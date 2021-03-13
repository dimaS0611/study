// Created by Dzmitry Semianovich

// Main file

#include "../include/basketball.h"

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    int size = atoi(argv[1]);
    struct Player* playersArray = (struct Player*)calloc(size, sizeof(struct Player));
    
    init_players(playersArray, size);

    info_PlayersU20(playersArray, size);

    info_Player_From_Vitebsk(playersArray, size);

    youngest_Player(playersArray, size);

    max_Point_Player(playersArray, size);

    free(playersArray);
 }
