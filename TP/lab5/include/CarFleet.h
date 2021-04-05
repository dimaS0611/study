//
//  CarFleet.h
//  CarFleet
//
//  Created by Dmitry Semenovich on 12.03.21.
//

#ifndef carFleet_h
#define carFleet_h

#include <stdio.h>
#include <stdbool.h>
#include "sqlite3.h"

int printTable(sqlite3* db, char* table);

int printValueById(sqlite3* db, char* table, int id);

void insertValue(sqlite3* db, char* table, char** value);

void addOrder(sqlite3* db, char** value);

void updateValue(sqlite3* db, char* table, char* field, char* value, char* update);

void deleteValue(sqlite3* db, char* table, char* value);

int listOfOrdersForPeriod(sqlite3* db, int driver_id, char* since_date, char* to_date);

int carInfo(sqlite3* db, int car_id);

int driverInfo(sqlite3* db, int driver_id);

int driverMinOrder(sqlite3* db);

int carMaxMileageOfDriver(sqlite3* db, int driver_id);

int carMaxMileage(sqlite3* db);

void getSalaryOfDriver(sqlite3* db, char* since_date, char* to_date, int driver_id);

void getSalary(sqlite3* db, char* since_date, char* to_date);

void getSalaryOfDriverBySurname(sqlite3* db, char* since_date, char* to_date, char* surname);

void printImageById(sqlite3* db, int id, FILE* outFile);

#endif /* carFleet_h */
