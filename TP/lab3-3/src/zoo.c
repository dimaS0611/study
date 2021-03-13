// Created by Dzmitry Semianovich

// This file implements the
// functionality of zoo.c

#include "../include/zoo.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Read_Info(struct Zoo* arr, int size)
{
	FILE* input = fopen("input.txt", "r");
    struct Zoo zoo;

	if (input != NULL)
	{
		for (int i = 0; i < size; ++i)
		{
			fgets(zoo._animalName, 25, input);
            
			fscanf(input, "%d", &zoo._animalNum);
			fscanf(input, "%d", &zoo._generalNum);
			fscanf(input, "%d", &zoo._employeesNum);
			fscanf(input, "%d", &zoo._index);
			fscanf(input, "%s", zoo._country);
			fscanf(input, "%s", zoo._region);
			fscanf(input, "%s", zoo._district);
			fscanf(input, "%s", zoo._city);
			fscanf(input, "%s", zoo._street);
			fscanf(input, "%d", &zoo._house);
			fscanf(input, "%d", &zoo._flat);
			
			char buf[255];
			fgets(buf, 2, input);

			arr[i] = zoo;
		}
	}

	fclose(input);
}

void Write_Info(struct Zoo* arr, int size)
{
    struct Zoo zoo;
	FILE* output = fopen("output.txt", "w");

	if (output != NULL) {
		fputs("Zoos that have Ussuri tigers:\n\n", output);

		for (int i = 0; i < size; ++i)
		{
			int cmp = strcmp("Ussuri tiger\n", arr[i]._animalName);

			if (cmp == 0)
			{
				fprintf(output, "Number of Ussuri tigers: %d\nGeneral number of animals: %d\nNumber of employees: %d",
					arr[i]._animalNum, arr[i]._generalNum, arr[i]._employeesNum);
				fprintf(output, "\n\nAddress:\n\tIndex: %d\n\tCountry: %s\n\tRegion: %s\n\tCity: %s",
					arr[i]._index, arr[i]._country, arr[i]._region, arr[i]._city);
				fprintf(output, "\n\tStreet: %s\n\tHouse: %d\n\tFlat: %d",
					arr[i]._street, arr[i]._house, arr[i]._flat);
				fputs("\n\n", output);
			}
		}
	}

	fclose(output);
}
