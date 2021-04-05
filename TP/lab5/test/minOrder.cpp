//
//  printValue.cpp
//  CarFleet
//
//  Created by Dmitry Semenovich on 13.03.21.
//
//#include <string>
#include "gtest/gtest.h"
#include "sqlite3.h"

extern "C" {
    #include "../include/CarFleet.h"
}

sqlite3 *db;
int openDB = sqlite3_open_v2("/Users/dmitrysemenovich/Documents/CarFleet/DB/Car_fleet_DB.db", &db, SQLITE_OPEN_READWRITE, NULL);

TEST(minOrder, ok)
{
    ASSERT_EQ(driverMinOrder(db), 1);
}

