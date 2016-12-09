#ifndef _DBCONNECTOR_H_
#define _DBCONNECTOR_H_

#include <iostream>
#include <sqlite3.h>
#include <vector>

using namespace std;

class DBConnector
{
    private:
    sqlite3* db;
    bool isOpenDB;
    
    public:
    DBConnector(const char* DBname);
    bool connectDB (const char* DBname);
    void disconnectDB ();
    vector<vector<string> > execute_show(const char *sql);
    int  execute_operate(const char *sql);
    bool getIsOpen();
   //& s int* callback(void *NotUsed, int argc, char **argv, char **azColName);
};
#endif