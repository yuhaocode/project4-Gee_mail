#include "DBHelper.h"
#include <iostream>
#include <string>
#include <sstream>
#include <sqlite3.h>
#include <stdio.h>
#include "DBConnector.h"
#include <vector>
#include <ctime>
#include <typeinfo>
#include "salsa20.h"
#include "sha.h"
using namespace std;


bool reg(string username, string password)
{
    stringstream strm;
    strm << "insert into user(user_ID,password) values( '" << username << "','" << password << "');";

	string s = strm.str();
	char* str = &s[0];
    //cout<<str<<endl;
    DBConnector connector("gee_email.db");
    int r = connector.execute_operate(str);
    connector.disconnectDB();
    if(r == 1){
        return true;
    }
    return false;
       
}


bool login(string user,string pwd)
{
    stringstream strm;
	strm << "select password from user where user_ID = '" << user << "';";

	string s = strm.str();
	char* str = &s[0];
	DBConnector connector("gee_email.db");
	vector<vector<string> >res = connector.execute_show(str);//result, if is null set the value as null.
	connector.disconnectDB();
	if(res[0][0] == pwd){
	    return true;
	}
	return false;
	
}

bool send(string send_user,string target_user,string message,string title)
{
	//check existence of the reciever 
    stringstream strm;
	strm << "select * from user where user_ID = '" << target_user << "';";
	string s = strm.str();
	char* str = &s[0];
	DBConnector connector("gee_email.db");
	vector<vector<string> >res = connector.execute_show(str);
	if(res.size()==0){
	    target_user = "user_not_exist";
	}
	
   
   //insert into database
	stringstream strm2;
	strm2 << "insert into message (receiver_ID,sender_ID,title,content,timestamp) values ('"<<target_user<<"','"<<send_user<<"','"<<title<<"','"<<message<<"',datetime('now'));";
	string s2 = strm2.str();
	char* str2 = &s2[0];
	//cout<<str2<<endl;
	int r = connector.execute_operate(str2);
    connector.disconnectDB();
     if(r == 1){
        return true;
    }
    return false;
	
}


vector<vector<string> > receive(string curent_user)
{
	stringstream strm;
	strm << "select message_ID,title,sender_ID,timestamp from message where receiver_ID = '" << curent_user << "' order by timestamp desc;";
	string s = strm.str();
	char* str = &s[0];
	
	DBConnector connector("gee_email.db");
	vector<vector<string> >res = connector.execute_show(str);
	 for (int i = 0 ;i<res.size();i++)
    {
       if(res[i][1].empty()){
       	res[i][1] = "(No Subject)";
       }
    }
	connector.disconnectDB();
	return res;
}

string read(int message_ID)
{
	stringstream strm;
	strm << "select content from message where message_ID = " << message_ID << ";";
	string s = strm.str();
	char* str = &s[0];
	
	DBConnector connector("gee_email.db");
	vector<vector<string> >res = connector.execute_show(str);
	connector.disconnectDB();
	string rs = res[0][0];
	return rs;
}

vector<vector<string> > sent(string curent_user)
{
	stringstream strm;
	strm << "select message_ID,title,receiver_ID,timestamp from message where sender_ID = '" << curent_user << "' oder by timestamp;";
	string s = strm.str();
	char* str = &s[0];
	
	DBConnector connector("gee_email.db");
	vector<vector<string> >res = connector.execute_show(str);
	connector.disconnectDB();
	return res;
}




// 	int main(){
// //     //bool r = reg("shou","123akjdhasjkdhskajhdkjashdjkashdjkashdkashdjkhaskdhsakjhdkjashdjkahskjh");
// //   //cout<<"register"<<r<<endl;
// //   //bool c = login(a,b);
// 	  //cout<<c<<endl; 
// 	 // string a="shou";
// 	  string f;
// 	  f.clear();
// 	  f = encrypt("abcfewfeefwe ewfwef","124");
// 	  cout<<f<<endl;
// 	  string h;
// 	  h.clear();
// 	  h =decrypt(f,"124");
// 	  cout<<h<<endl;
// //   //bool d = send("andy","shou",f,"title");
  
  
// //   //vector<vector<string>> res = receive(a);
// //   //  cout<<res[0][0]<<endl;
// //   //  cout<<res[0][1]<<endl;
// //   //  cout<<res[0][2]<<endl;
// //   //  cout<<res[0][3]<<endl;
//      string z = read(2);
//       cout<<z<<endl;
//       cout<<decrypt(z,"123")<<endl;
//      return 0;
//  }