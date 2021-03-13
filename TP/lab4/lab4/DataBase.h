//
//  DataBase.h
//  lab4
//
//  Created by Dmitry Semenovich on 11.03.21.
//

#ifndef DataBase_h
#define DataBase_h

#include <stdio.h>
#include "sqlite3.h"

void PrintValueById(sqlite3* db, int id);

void PrintValueByField(sqlite3* db, char* field, char* value);

void AddValue(sqlite3* db, char** value);

void PrintValueByCategory(sqlite3* db, char* value);

void DeleteValueById(sqlite3* db, int id);

void PrintImageById(sqlite3* db, int id, FILE* file);

#endif /* DataBase_h */
