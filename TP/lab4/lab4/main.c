//
//  main.c
//  lab4
//
//  Created by Dmitry Semenovich on 11.03.21.
//

#include "DataBase.h"

#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"

int main()
{
    sqlite3 *db;
    int openDB = sqlite3_open_v2("/Users/dmitrysemenovich/Documents/repos/labrabota4-gr13-1-dimaS0611/lab4/zoo.db", &db, SQLITE_OPEN_READWRITE, NULL);
    
    if(openDB)
    {
        printf("Something went wrong!\nCan not open data base");
    }
    
    int option = 1;
    
    while(option != 0)
    {
        printf("Please, chooise the option:\n");
        printf("\tPrint value by id: 1\n");
        printf("\tPrint value by certain field: 2\n");
        printf("\tPrint value by category: 3\n");
        printf("\tAdd a new record: 4\n");
        printf("\tPrint all records: 5\n");
        printf("\tDelete record by id: 6\n");
        printf("\tLoad image by id into file: 7\n");
        printf("\tExit: 0\n\n************************\n\n");
        
        int cmd = 1;
        scanf("%d", &cmd);
        
        switch (cmd) {
            case 1:
            {
                printf("\nInsert required id: ");
                
                int id = 0;
                scanf("%d", &id);
                
                PrintValueById(db, id);
                
                break;
            }
            
            case 2:
            {
                printf("\nInsert required field name: ");
                
                char field[40];
                scanf("%s", field);
                
                printf("\nInsert value from filed: ");
                
                char value[40];
                scanf("%s", value);
                
                PrintValueByField(db, field, value);
                
                break;
            }
            
            case 3:
            {
                printf("\nInsert required category: ");
                
                char category[50];
                scanf("%s", category);
                
                PrintValueByCategory(db, category);
                
                break;
            }
                
            case 4:
            {
                char animal[50];
                char animal_num[10];
                char country[50];
                char city[50];
                char street[50];
                char house[10];
                char category_id[10];
                char animal_gen[10];
                char emploees_num[10];
                
                printf("\n\tEnter the name of animal: ");
                scanf("%s", animal);
                
                printf("\n\tEnter number of animal: ");
                scanf("%s", animal_num);
                
                printf("\n\tEnter the country: ");
                scanf("%s", country);
                
                printf("\n\tEnter the city: ");
                scanf("%s", city);
                
                printf("\n\tEnter the street: ");
                scanf("%s", street);
                
                printf("\n\tEnter the house: ");
                scanf("%s", house);
                
                printf("\n\tEnter id of animal category: ");
                scanf("%s", category_id);
                
                printf("\n\tEnter the generel number of animals in the zoo: ");
                scanf("%s", animal_gen);
                
                printf("\n\tEnter the number of zoo emploees: ");
                scanf("%s", emploees_num);
                
                char* value[9];
                value[0] = animal;
                value[1] = animal_num;
                value[2] = country;
                value[3] = city;
                value[4] = street;
                value[5] = house;
                value[6] = category_id;
                value[7] = animal_gen;
                value[8] = emploees_num;
                
                AddValue(db, value);
                
                break;
            }
                
            case 5:
            {
                PrintValueByField(db, "animal_name", "%%");
                
                break;
            }
            case 6:
            {
                int id = 0;
                
                printf("Enter the id: ");
                scanf("%d", &id);
                
                DeleteValueById(db, id);
                break;
            }
            case 7:
            {
                int id = 0;
                
                printf("\nEnter the id: ");
                scanf("%d", &id);
                
                char path[50];
                
                printf("\nEnter the path to load image: ");
                scanf("%s", path);
                
                FILE* out = fopen(path, "wb");
                
                PrintImageById(db, id, out);
                
                break;
            }
                
            case 0:
            {
                option = 0;
                break;
            }
            default:
            {
                printf("\nInvaid option!");
                continue;
            }
        }
    }
    return 0;
}
