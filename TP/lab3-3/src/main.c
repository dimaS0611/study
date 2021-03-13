// Created by Dzmitry Semianovich

// Main file

#include "../include/zoo.h"

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    int size = atoi(argv[1]);
    struct Zoo* zoosArray = (struct Zoo*)calloc(size, sizeof(struct Zoo));

    Read_Info(zoosArray, size);

    Write_Info(zoosArray, size);

    free(zoosArray);
}
