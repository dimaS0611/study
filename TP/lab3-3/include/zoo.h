// Created by Dzmitry Semianovich

// This file implements the
// functionality of zoo.h

struct Zoo
{
	char _animalName[25]; 	// Name of animal 
	int _animalNum;		// Number of animals
	int _generalNum;	// Total number of animals at the zoo
	int _employeesNum;	// Total number of employees at the zoo

    	int _index;		// Zoo address
    	char _country[25];
	char _region[25];
	char _district[25];
	char _city[25];
	char _street[25];
		
	int _house;
	int _flat;
};

void Read_Info(struct Zoo* arr, int size);	// Function to read input file and init zoo struct 

void Write_Info(struct Zoo* arr, int size);	// Function that displays info 
						// about zoos with Ussuri tigers
