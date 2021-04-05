//
//  CarFleet.c
//  CarFleet
//
//  Created by Dmitry Semenovich on 12.03.21.
//

#include "../include/CarFleet.h"

#include "sqlite3.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static int callback(void* NotUsed, int argc, char** argv, char** azColName)
{
    printf("\n");
    
    for (int i = 0; i < argc; i++)
    {
        printf(" %s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    
    printf("\n");
    return 0;
}

int printTable(sqlite3* db, char* table)
{
    int res = 1;
    char requestBuffer[60];
    sprintf(requestBuffer, "SELECT * FROM %s ;", table);

    char* errorMsg=0;
    
    if (sqlite3_exec(db, requestBuffer, callback, 0, &errorMsg) != SQLITE_OK) {
        printf("%s", errorMsg);
        res = 0;
    }
    
    return res;
}

int printValueById(sqlite3* db, char* table, int id)
{
    int res = 1;
    char requestBuffer[60];
    sprintf(requestBuffer, "SELECT * FROM %s WHERE id=%d;", table, id);
    
    char* errorMsg=0;
    
    if (sqlite3_exec(db, requestBuffer, callback, 0, &errorMsg) != SQLITE_OK) {
        printf("%s", errorMsg);
        res = 0;
    }
    
    return res;
}

int listOfOrdersForPeriod(sqlite3* db, int driver_id, char* since_date, char* to_date)
{
    int res = 1;
    char requestBuffer[255];
    char* errorMsg = 0;
    
    sprintf(requestBuffer, "SELECT number, mileage, weight, price FROM Order_Info WHERE driver_id=%d AND date between '%s' AND '%s';", driver_id, since_date, to_date);
    
    if(sqlite3_exec(db, requestBuffer, callback, 0, &errorMsg) != SQLITE_OK)
    {
        printf("%s", errorMsg);
        res = 0;
    }
    
    return res;
}

int carInfo(sqlite3* db, int car_id)
{
    int res = 1;
    char requestBuffer[255];
    char* errorMsg = 0;
    
    sprintf(requestBuffer, "SELECT Car.mileage, Car.capacity FROM Car WHERE id=%d;", car_id);
    
    if(sqlite3_exec(db, requestBuffer, callback, 0, &errorMsg) != SQLITE_OK)
    {
        printf("%s", errorMsg);
        res = 0;
    }
    
    return res;
}

int driverInfo(sqlite3* db, int driver_id)
{
    int res = 1;
    char requestBuffer[255];
    char* errorMsg = 0;
    
    sprintf(requestBuffer, "SELECT count(driver_id), sum(weight), sum(price) FROM Order_Info WHERE driver_id=%d;", driver_id);
    
    if(sqlite3_exec(db, requestBuffer, callback, 0 ,&errorMsg) != SQLITE_OK){
        printf("%s", errorMsg);
        res = 0;
    }
    
    return res;
}

int driverMinOrder(sqlite3* db)
{
    int res = 1;
    char requestBuffer[300];
    char* errorMsg = 0;
    
    sprintf(requestBuffer, "SELECT  surname, birthDate, category, experience, min(orders) FROM (SELECT Driver.surname, Driver.birthDate, Driver.category, Driver.experience, count(Order_Info.driver_id) as orders FROM Driver LEFT JOIN Order_Info ON Driver.id=Order_Info.driver_id GROUP BY driver_id);");
    
    if(sqlite3_exec(db, requestBuffer, callback, 0, &errorMsg)){
        printf("%s", errorMsg);
        res = 0;
    }
    
    return res;
}

int carMaxMileageOfDriver(sqlite3* db, int driver_id)
{
    int res = 1;
    char requestBuffer[300];
    char* errorMsg = 0;
    
    sprintf(requestBuffer, "SELECT driver_id, brand, number, capacity, max(distance) FROM (SELECT Car.driver_id, Car.brand, Car.number, sum(Car.capacity) as capacity,  sum(Order_Info.mileage) as distance FROM Car LEFT JOIN Order_Info ON Car.driver_id=Order_Info.driver_id WHERE Order_Info.driver_id=%d);", driver_id);
    
    if(sqlite3_exec(db, requestBuffer, callback, 0, &errorMsg)){
        printf("%s", errorMsg);
        res = 0;
    }
    
    return res;
}

int carMaxMileage(sqlite3* db)
{
    int res = 1;
    char requestBuffer[255];
    char* errorMsg = 0;
    
    sprintf(requestBuffer, "SELECT brand, number, capacity, max(distance)  FROM            (SELECT Car.brand, Car.number, Car.capacity, sum(Order_Info.mileage)  as distance FROM Car LEFT JOIN Order_Info ON Car.driver_id=Order_Info.driver_id GROUP BY  Order_Info.driver_id);");
    
    if(sqlite3_exec(db, requestBuffer, callback, 0, &errorMsg)){
        printf("%s", errorMsg);
        res = 0;
    }
    
    return res;
}

void insertValue(sqlite3* db, char* table, char** value){
    char requestBuffer[255];
    char* errorMsg = 0;
    
    if(!strcmp(table, "Driver")){
        sprintf(requestBuffer, "INSERT INTO Driver (surname, category, experience, address, birthDate) VALUES ('%s', '%s', %d, '%s', '%s');", value[0], value[1], atoi(value[2]), value[3], value[4]);
    }
    else if(!strcmp(table, "Order"))
    {
        addOrder(db, value);
    }
    else if(!strcmp(table, "Car")){
            sprintf(requestBuffer, "INSERT INTO Car (number, brand, mileage, capacity, driver_id) VALUES ('%s', '%s', %d, %d, %d);", value[0], value[1], atoi(value[2]), atoi(value[3]), atoi(value[4]));
    }
    else{
        printf("Invalid table name");
    }
    
    if(sqlite3_exec(db, requestBuffer, callback, 0, &errorMsg)){
        printf("%s", errorMsg);
    }
}

void updateValue(sqlite3* db, char* table, char* field, char* value, char* update)
{
    char requestBuffer[255];
    char* errorMsg = 0;
    

    if(!strcmp("Driver", table) && !strcmp(field, "category"))
    {
        sprintf(requestBuffer, "UPDATE %s SET %s='%s' WHERE id=%d;", table, field, update, atoi(value));
    }
    else if(!strcmp("Driver", table)){
        sprintf(requestBuffer, "UPDATE %s SET %s=%d WHERE id=%d;", table, field, atoi(update), atoi(value));
    }
    else{
        sprintf(requestBuffer, "UPDATE %s SET %s=%d WHERE id=%d;", table, field, atoi(update), atoi(value));
    }
    
    
    if(sqlite3_exec(db, requestBuffer, callback, 0, &errorMsg)){
        printf("%s", errorMsg);
    }
}

void deleteValue(sqlite3* db, char* table, char* value)
{
    char requestBuffer[255];
    char* errorMsg = 0;
    
    sprintf(requestBuffer, "DELETE FROM %s WHERE id=%d;", table, atoi(value));
    
    if(sqlite3_exec(db, requestBuffer, callback, 0, &errorMsg)){
        printf("%s", errorMsg);
    }
}

int carWeight = 0;

static int carWeight_callback(void* NotUsed, int argc, char** argv, char** azColName)
{
    carWeight = atoi(argv[0]);
    return 0;
}

void addOrder(sqlite3* db, char** values)
{
    char check[255];
    char* err = 0;
    sprintf(check, "SELECT capacity FROM Car WHERE number='%s'", values[2]);
    
    if(sqlite3_exec(db, check, carWeight_callback, 0, &err))
    {
        printf("%s", err);
    }
    else
    {
        if(atoi(values[4]) <= carWeight)
        {
            char requestBuffer[255];
            char* errorMsg = 0;
            
            sprintf(requestBuffer, "INSERT INTO Order_Info (date, surname, number, mileage, weight, price, driver_id) VALUES ('%s', '%s', '%s', %d, %d, %d, %d);", values[0], values[1], values[2], atoi(values[3]), atoi(values[4]), atoi(values[5]), atoi(values[6]));
            
            sqlite3_stmt* pStmt;
            sqlite3_prepare_v2(db, requestBuffer, -1, &pStmt, 0);
            
            if(sqlite3_exec(db, requestBuffer, callback, 0, &errorMsg)){
                printf("%s", errorMsg);
            }
            
            sqlite3_finalize(pStmt);
        }
    }
}

void getSalaryOfDriver(sqlite3* db, char* since_date, char* to_date, int driver_id)
{
    char requestBuffer[300];
    char* errorMsg = 0;
    
    sprintf(requestBuffer, "SELECT Order_Info.driver_id, Order_Info.surname, Order_Info.mileage, Order_Info.weight, (sum(Order_Info.price) * 0.2) FROM Order_Info WHERE Order_Info.driver_id=%d AND date BETWEEN '%s' AND '%s';", driver_id, since_date, to_date);
    
    if(sqlite3_exec(db, requestBuffer, callback, 0, &errorMsg) != SQLITE_OK)
    {
        printf("%s", errorMsg);
    }
}

void getSalary(sqlite3* db, char* since_date, char* to_date)
{
    char requestBuffer[255];
    char* errorMsg = 0;
    
    sprintf(requestBuffer, "SELECT Order_Info.driver_id, Order_Info.surname, Order_Info.mileage, Order_Info.weight, (sum(Order_Info.price) * 0.2) FROM Order_Info WHERE Order_Info.date BETWEEN '%s' AND '%s' GROUP BY driver_id;", since_date, to_date);
    
    if(sqlite3_exec(db, requestBuffer, callback, 0, &errorMsg) != SQLITE_OK)
    {
        printf("%s", errorMsg);
    }
}

void getSalaryOfDriverBySurname(sqlite3* db, char* since_date, char* to_date, char* surname)
{
    char requestBuffer[300];
    char* errorMsg = 0;
    
    sprintf(requestBuffer, "SELECT Order_Info.driver_id, Order_Info.surname, Order_Info.mileage, Order_Info.weight, (sum(Order_Info.price) * 0.2) FROM Order_Info WHERE Order_Info.surname='%s' AND Order_Info.date BETWEEN '%s' AND '%s';", surname, since_date, to_date);
    
    if(sqlite3_exec(db, requestBuffer, callback, 0, &errorMsg) != SQLITE_OK)
    {
        printf("%s", errorMsg);
    }
}

void printImageById(sqlite3* db, int id, FILE* outFile)
{
    char requestBuffer[200];
    sprintf(requestBuffer, "SELECT image FROM Car WHERE id=%d;", id);

    sqlite3_stmt* pStmt;
    sqlite3_prepare_v2(db, requestBuffer, -1, &pStmt, 0);

    int rc = sqlite3_step(pStmt);
    int bytes = 0;
    
    if (rc == SQLITE_ROW) {
        bytes = sqlite3_column_bytes(pStmt, 0);
    }

    fwrite(sqlite3_column_blob(pStmt, 0), bytes, 1, outFile);
    fclose(outFile);
    sqlite3_finalize(pStmt);
}
