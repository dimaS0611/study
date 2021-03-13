//
//  DataBase.c
//  lab4
//
//  Created by Dmitry Semenovich on 11.03.21.
//

#include "DataBase.h"

#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"

static int callback(void* NotUsed, int argc, char** argv, char** azColName)
{
    for (int i = 0; i < argc; i++)
    {
        printf(" %s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    
    printf("\n");
    return 0;
}

void PrintValueById(sqlite3* db, int id)
{
    char requestBuffer[60];
    sprintf(requestBuffer, "SELECT * FROM Zoo_Info WHERE id=%d;", id);
    
    char* errorMsg=0;
    
    if (sqlite3_exec(db, requestBuffer, callback, 0, &errorMsg) != SQLITE_OK) {
        printf("%s", errorMsg);
    }
}

void PrintValueByField(sqlite3* db, char* field, char* value)
{
    char requestBuffer[150];
    char* errorMsg = 0;
    
    sprintf(requestBuffer, "SELECT * FROM Zoo_Info WHERE %s LIKE '%s';", field, value);
    
    if(sqlite3_exec(db, requestBuffer, callback, 0, &errorMsg)!=SQLITE_OK)
    {
        printf("%s", errorMsg);
    }
}

void AddValue(sqlite3* db, char** argv)
{
    char requestBuffer[500];
    char* errorMsg = 0;
 
    sprintf(requestBuffer, "INSERT INTO Zoo_Info (animal_name,animal_num, country, city, street, house, category_id, animal_gen, emploees_num) VALUES ('%s',%d,'%s','%s','%s',%d,%d,%d, %d)",
        argv[0], atoi(argv[1]), argv[2], argv[3], argv[4], atoi(argv[5]), atoi(argv[6]), atoi(argv[7]), atoi(argv[8]));
    
    if (sqlite3_exec(db, requestBuffer, callback, 0, &errorMsg) != SQLITE_OK)
    {
        printf("%s", errorMsg);
    }
}

void PrintValueByCategory(sqlite3* db, char* category)
{
    char requestBuffer[250];
    char* errorMsg = 0;
    
    sprintf(requestBuffer, "SELECT animal_name, animal_num, category_id, cat_description, country, city, street, house FROM Zoo_Info INNER JOIN Category ON Category.id=Zoo_Info.category_id WHERE Category.cat_description='%s';", category);

    if(sqlite3_exec(db, requestBuffer, callback, 0, &errorMsg)!=SQLITE_OK)
    {
        printf("%s", errorMsg);
    }
}

void DeleteValueById(sqlite3* db, int id)
{
    char requestBuffer[200];
    char* errorMsg = 0;
    
    sprintf(requestBuffer, "DELETE FROM Zoo_info WHERE id=%d;", id);

    if (sqlite3_exec(db, requestBuffer, callback, 0, &errorMsg) != SQLITE_OK)
    {
        printf("%s", errorMsg);
    }
}

void PrintImageById(sqlite3* db, int id,FILE* outFile)
{
    char requestBuffer[200];
    sprintf(requestBuffer, "SELECT image FROM Category WHERE id=%d;", id);

    sqlite3_stmt* pStmt;
    sqlite3_prepare_v2(db, requestBuffer, -1, &pStmt, 0);

    int rc = sqlite3_step(pStmt);
    int bytes = 0;
    
    if (rc == SQLITE_ROW)
    {
        bytes = sqlite3_column_bytes(pStmt, 0);
    }

    fwrite(sqlite3_column_blob(pStmt, 0), bytes, 1, outFile);
    fclose(outFile);
    sqlite3_finalize(pStmt);
}

