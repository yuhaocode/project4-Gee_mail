#include <iostream>
#include <sqlite3.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include "DBConnector.h"
#include "salsa20.h"
#include "sha.h"
#include <vector>

using namespace std;


DBConnector::DBConnector(const char* DBname)
{   
    db = NULL;
    isOpenDB = false;
    this->isOpenDB = connectDB(DBname);
}
    
bool DBConnector::connectDB (const char* DBname)
{
    int rc = sqlite3_open(DBname, &this->db);
    //printf("%p\n",this->db);
    if ( rc == SQLITE_OK )
    {
        cout << "Database connect successfully!" <<endl;
        return true;
    }
        
    return false;
}
void DBConnector::disconnectDB ()
{
    if ( this->isOpenDB == true )
    {
        this->isOpenDB = false;
        int dc;
        dc = sqlite3_close_v2(db);
      // cout << "Database disconnect successfully!" << endl;
    }
    else
    {
       cout << "Database connection already closed" << endl;
    }
}
    
vector<vector<string> > DBConnector::execute_show(const char *sql)
{
    //cout << sql << endl;
    //cout << SQLITE_OK << endl;
    //char *zErrMsg = 0;
    // printf("%p\n",this->db);
    //cout << sqlite3_prepare_v2(this->db, sql, -1, &statement, NULL) << endl;
    vector<vector<string> > result;
    vector<string> row;
    sqlite3_stmt *statement;
    if ( this->isOpenDB == true )
    {
        if ( sqlite3_prepare(this->db, sql, -1, &statement, 0 ) == SQLITE_OK ) 
	    {
	        int ctotal = sqlite3_column_count(statement);
		    int res = 0;
            while ( 1 ) 		
            {
			    res = sqlite3_step(statement);
			    if ( res == SQLITE_ROW ) 
		    	{   
		    	    row.clear();
		    	    for ( int i = 0; i < ctotal; i++ ) 
				    {
				        string s;
				        if((char*)sqlite3_column_text(statement, i) == NULL)
				        {
				            s = "";
				        }
				        else
				        {
				            s = (char*)sqlite3_column_text(statement, i);
				        }
				        // if(s.empty()){
				        //     s = "Default title";
				        // }
				    	row.push_back(s);
			    	}
		    	 }
                if ( res == SQLITE_DONE )	
		    	 {
		    	    //Finish reading the result
		    	    /*
		    	     might need to handle with null result here
		    	    */
			    	//cout << "done " << endl;
			    	break;
		    	 }	
		    	 result.push_back(row);
			 }
			 sqlite3_finalize(statement);
			 return result;
    	 }
    	else
    	{
    	   cout << "sql failed !" << endl;
    	}
    }
    else
    {
        cout << "There is a problem with db connection" << endl;
    }
    return result;
        
}

int DBConnector::execute_operate(const char *sql)
{
    sqlite3_stmt *statement;
    int result;
	if (this->isOpenDB == true)
	{
	    if(sqlite3_prepare(this->db, sql, -1,&statement,0)==SQLITE_OK)
	    {
		    int res=sqlite3_step(statement);
		    result = res;
		    sqlite3_finalize(statement);
		    return 1;
	    }
    
	}
	else
	{
	    cout << "There is a problem with db connection"<<endl;
	}
	return 0;
}
// int* DBConnector::callback(void *NotUsed, int argc, char **argv, char **azColName)
// {
//     int i;
//     for(i=0; i<argc; i++)
//     {
//         printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
//     }
//     printf("\n");
//     return 0;
// }

bool DBConnector::getIsOpen()
{
    return isOpenDB;
}

//  int main()
//  {
// //     DBConnector connector("gee_email.db");
    
// //     std::stringstream strm;
// //     strm << "select * from message;";
// //     string s = strm.str();
// //     char* sql= &s[0];
// //     vector<vector<string> > result = connector.execute_show(sql);
// //     int i,j;
// //     for (i = 0 ;i<result.size();i++)
// //     {
// //         for (j = 0;j<result[i].size();j++)
// //         {
// //             cout << result[i][j] <<" ";
// //         }
// //         cout << endl;
// //     }
// //     connector.disconnectDB();
   
// //     return 0;
//   string f = encrypt("abcfewfeefwe ewfwef","124");
//   cout<<f<<endl;
//   string h =decrypt(f,"124");
//   cout<<h<<endl;
//   return 0;
//  }