//
//  main.c
//  CarFleet
//
//  Created by Dmitry Semenovich on 12.03.21.
//

#include "../include/CarFleet.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"

int main()
{
    sqlite3 *db;
    int openDB = sqlite3_open_v2("/Users/dmitrysemenovich/Documents/CarFleet/DB/Car_fleet_DB.db", &db, SQLITE_OPEN_READWRITE, NULL);

    if(openDB)
    {
        printf("Something went wrong!\nCan not open database");
    }
    
    int option = 1;
    
    while(option != 0)
    {
        printf("Please, chooise the option: \n");
        printf("\tPrint all records of table: 1\n");
        printf("\tPrint record by id: 2\n");
        printf("\tAdd new record: 3\n");
        printf("\tUpdate record: 4\n");
        printf("\tDelete record: 5\n");
        printf("\tAdd new order: 6\n");
        printf("\tPrint list of orders for a certain period: 7\n");
        printf("\tPrint information about the car: 8\n");
        printf("\tPrint information about the driver: 9\n");
        printf("\tDisplay the information about the driver who has the minimum order: 10\n");
        printf("\tDisplay information about the driver's car that have the most mileage: 11\n");
        printf("\tDisplay information about the car that have the most mileage: 12\n");
        printf("\tPrint the driver's salary for a certain period: 13\n");
        printf("\tPrint the salary of all drivers for a certain period: 14\n");
        printf("\tPrint the driver's salary by his surname for a certain period: 15\n");
        printf("\tUpload an image of the car by id to a file: 16\n");
        printf("\tExit: 0\n\n*****************************************\n\n");
        
        int cmd = 1;
        scanf("%d", &cmd);
        
        switch(cmd)
        {
            case 1:
            {
                printf("\nChooise the table");
                printf("\n\tDrver: 1\n\tCar: 2\n\tOrder_Info: 3\n");
                
                int table = 1;
                scanf("%d", &table);
                
                if(table >= 1 && table <=3)
                {
                    char* table_name = NULL;
                
                    if(table == 1){
                        table_name = "Driver";
                    } else if(table == 2){
                        table_name = "Car";
                    } else if(table == 3){
                        table_name = "Order_info";
                    }
                
                    printTable(db, table_name);
                }
                else{
                    printf("Invalid option!\n");
                }
                break;
            }
            case 2:
            {
                printf("\nChooise the table");
                printf("\n\tDrver: 1\n\tCar: 2\n\tOrder_Info: 3\n\n");
                
                int table = 1;
                scanf("%d", &table);
                
                if(table >= 1 && table <=3)
                {
                    char* table_name = NULL;
                
                    if(table == 1){
                        table_name = "Driver";
                    } else if(table == 2){
                        table_name = "Car";
                    } else if(table == 3){
                        table_name = "Order_info";
                    }
                    
                    int id = 0;
                    printf("\nEnter required id: ");
                    scanf("%d", &id);
                
                    printValueById(db, table_name, id);
                } else{
                    printf("Invalid name of table!");
                }
                break;
            }
            case 3:
            {
                printf("\nChooise the table");
                printf("\n\tDrver: 1\n\tCar: 2\n\n");
                
                int table = 1;
                scanf("%d", &table);
                
                char* table_name = NULL;
                
                if(table >= 1 && table <=3)
                {
                    if(table == 1)
                    {
                        table_name = "Driver";
                        
                        char surname[30];
                        char category[10];
                        char experience[10];
                        char address[70];
                        char birthDate[11];
                        
                        printf("\n\tEnter a surname: ");
                        scanf("%s", surname);
                        
                        printf("\n\tEnter a category: ");
                        scanf("%s", category);
                        
                        printf("\n\tEnter an experience: ");
                        scanf("%s", experience);
                        
                        printf("\n\tEnter the address: ");
                        scanf("%s", address);
                        
                        printf("\n\tEnter the date of birth(YYYY-MM-DD): ");
                        scanf("%s", birthDate);
                        
                        char* value[5];
                        value[0] = surname;
                        value[1] = category;
                        value[2] = experience;
                        value[3] = address;
                        value[4] = birthDate;
                        
                        insertValue(db, table_name, value);
                    }
                    else if(table == 2)
                    {
                        table_name = "Car";
                        
                        char number[50];
                        char brand[30];
                        char mileage[10];
                        char capacity[10];
                        char driver_id[10];
                    
                        printf("\n\tEnter a number: ");
                        scanf("%s", number);
                    
                        printf("\n\tEnter a brand: ");
                        scanf("%s", brand);
                    
                        printf("\n\tEnter mileage: ");
                        scanf("%s", mileage);
                    
                        printf("\n\tEnter capacity: ");
                        scanf("%s", capacity);
                    
                        printf("\n\tEnter the driver id: ");
                        scanf("%s", driver_id);
                    
                        char* value[5];
                        value[0] = number;
                        value[1] = brand;
                        value[2] = mileage;
                        value[3] = capacity;
                        value[4] = driver_id;
                    
                        insertValue(db, table_name, value);
                    }
                    else{
                        printf("Invalid name of table!");
                    }
                
                }
                
                break;
            }
            case 4:
            {
                printf("\nChooise the table");
                printf("\n\tDrver: 1\n\tCar: 2\n\tOrder_Info: 3\n");
                
                int table = 1;
                scanf("%d", &table);
                
                if(table >= 1 && table <=3)
                {
                    char* table_name = NULL;
                
                    if(table == 1){
                        table_name = "Driver";
                    } else if(table == 2){
                        table_name = "Car";
                    }
                    
                    char* field = NULL;
                    char update[50];
                    
                    int field_chooise = 1;
                    
                    printf("\nChooise the field to update:");
                    
                    if(!strcmp("Driver", table_name))
                    {
                        printf("\n\texperience: 1\n\tcategory: 2\n");
                        scanf("%d", &field_chooise);
                        
                        if(field_chooise == 1)
                        {
                            field = "experience";
                            
                            printf("\nEnter a value to set: ");
                            scanf("%s", update);

                        }
                        if(field_chooise == 2)
                        {
                            field = "category";
                            
                            printf("\nEnter a value to set: ");
                            scanf("%s", update);

                        }
                        
                    }
                    if(!strcmp("Order", table_name))
                    {
                        printf("\n\tmileage: 1\n\tweight:2\n\tprice: 3\n");
                        
                        if(field_chooise==1)
                        {
                            field = "mileage";
                        
                            printf("\nEnter a value to set: ");
                            scanf("%s", update);
                        }
                        if(field_chooise==2)
                        {
                            field = "weight";
                        
                            printf("\nEnter a value to set: ");
                            scanf("%s", update);
                        }
                        if(field_chooise==3)
                        {
                            field = "price";
                            
                            printf("\nEnter a value to set: ");
                            scanf("%s", update);
                        }
                    }
                    
                    printf("\nEnter the id of value to update: ");
                    char id[10];
                    scanf("%s", id);
                    
                    
                    updateValue(db, table_name, field, id, update);
                } else{
                    printf("Invalid option!");
                }
                
                break;
            }
            case 5:
            {
                printf("\nChooise the table");
                printf("\n\tDrver: 1\n\tCar: 2\n\tOrder_Info: 3\n");
                
                int table = 1;
                scanf("%d", &table);
                
                if(table >= 1 && table <=3)
                {
                    char* table_name = NULL;
                
                    if(table == 1){
                        table_name = "Driver";
                    } else if(table == 2){
                        table_name = "Car";
                    } else if(table == 3){
                        table_name = "Order_info";
                    }
                  
                    printf("\nEnter the id of value: ");
                    char id[10];
                    scanf("%s", id);
                    
                    deleteValue(db, table_name, id);
                } else{
                    printf("Invalid option!");
                }
                    break;
            }
            case 6:
            {
                char date[11];
                char surname[30];
                char number[50];
                char mileage[10];
                char weight[10];
                char price[10];
                char driver_id[10];
                    
                printf("\n\tEnter a date(YYYY-MM-DD): ");
                scanf("%s", date);
                
                printf("\n\tEnter a surname: ");
                scanf("%s", surname);
                
                printf("\n\tEnter an number: ");
                scanf("%s", number);
                
                printf("\n\tEnter the mileage: ");
                scanf("%s", mileage);
                
                printf("\n\tEnter the weight: ");
                scanf("%s", weight);
                
                printf("\n\tEnter a price: ");
                scanf("%s", price);
                
                printf("\n\tEnter the driver id: ");
                scanf("%s", driver_id);
                
                char* value[7];
                value[0] = date;
                value[1] = surname;
                value[2] = number;
                value[3] = mileage;
                value[4] = weight;
                value[5] = price;
                value[6] = driver_id;
                
                addOrder(db, value);
                break;
            }
            case 7:
            {
                char since_date[11];
                char to_date[11];
                int driver_id = 0;
                
                printf("\n\tEnter the beginning of the period in format(YYYY-MM-DD): ");
                scanf("%s", since_date);
                
                printf("\n\tEnter the end of the period in format(YYYY-MM-DD): ");
                scanf("%s", to_date);
                
                printf("\n\tEnetr the driver id: ");
                scanf("%d", &driver_id);
                
                listOfOrdersForPeriod(db, driver_id, since_date, to_date);
                break;
            }
            case 8:
            {
                int car_id;
                
                printf("\n\tEnter the car id: ");
                scanf("%d", &car_id);

                carInfo(db, car_id);
                break;
            }
            case 9:
            {
                int driver_id;
                
                printf("\n\tEnter the driver id: ");
                scanf("%d", &driver_id);
                
                driverInfo(db, driver_id);
                break;
            }
            case 10:
            {
                driverMinOrder(db);
                break;
            }
            case 11:
            {
                int driver_id;
                
                printf("\n\tEnter the driver id: ");
                scanf("%d", &driver_id);
                
                carMaxMileageOfDriver(db, driver_id);
                break;
            }
            case 12:
            {
                carMaxMileage(db);
                break;
            }
            case 13:
            {
                char since_date[11];
                char to_date[11];
                int driver_id = 0;
                
                printf("\n\tEnter the beginning of the period in format(YYYY-MM-DD): ");
                scanf("%s", since_date);
                
                printf("\n\tEnter the end of the period in format(YYYY-MM-DD): ");
                scanf("%s", to_date);
                
                printf("\n\tEnetr the driver id: ");
                scanf("%d", &driver_id);
                
                getSalaryOfDriver(db, since_date, to_date, driver_id);
                break;
            }
            case 14:
            {
                char since_date[11];
                char to_date[11];
                
                printf("\n\tEnter the beginning of the period in format(YYYY-MM-DD): ");
                scanf("%s", since_date);
                
                printf("\n\tEnter the end of the period in format(YYYY-MM-DD): ");
                scanf("%s", to_date);
                
                getSalary(db, since_date, to_date);
                break;
            }
            case 15:
            {
                char since_date[11];
                char to_date[11];
                char surname[50];
                
                printf("\n\tEnter the beginning of the period in format(YYYY-MM-DD): ");
                scanf("%s", since_date);
                
                printf("\n\tEnter the end of the period in format(YYYY-MM-DD): ");
                scanf("%s", to_date);
                
                printf("\n\tEnter surname of the driver: ");
                scanf("%s", surname);
                
                getSalaryOfDriverBySurname(db, since_date, to_date, surname);
                break;
            }
            case 16:
            {
                int id;
                char path[200];
                
                printf("\n\tEnter the id of the car that the image you want to  upload: ");
                scanf("%d", &id);
                
                printf("\n\tEnter the path to load image: ");
                scanf("%s", path);
                
                FILE* out = fopen(path, "wb");
                
                printImageById(db, id, out);
                break;
            }
            case 0:
            {
                option = 0;
                break;
            }
            default:
            {
                printf("/nInvalid option!");
                break;
            }
        }
    }
    return 0;
}
