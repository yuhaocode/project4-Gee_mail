#ifndef _DBHELPER_H_
#define _DBHELPER_H_

#include <iostream>
#include <string>
#include <vector>
using namespace std;


bool login(string user,string pwd);
bool reg(string user,string pwd);
bool send(string send_user,string target_user,string message, string title);
vector<vector<string> > receive(string curent_user); //return title user(received from)  time message_ID
string read(int Message_ID); //message body
vector<vector<string> > sent(string curent_user);


#endif