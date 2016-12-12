#include <iostream>
#include <string>
#include <sqlite3.h>
#include <set>
#include "DBConnector.h"
#include "DBHelper.h"
#include "sha.h"
#include <cstdlib>
#include <math.h>
#include "salsa20.h"
using namespace std;
bool Find(vector<int> S,int target){
    int Length=S.size();
    int goal=0;
    int upper=Length-1;
    int lower=0;
    int middle=(upper+lower)/2;
    while(upper>lower+1){
        if(target>S[middle]){
            lower=middle;
            middle=(upper+lower)/2;
        }
        else if(target<S[middle]){
            upper=middle;
            middle=(upper+lower)/2;
        }
        else{
            return true;
        }
    }
    if(target==S[upper]||target==S[lower]){
        return true;
    }
    return false;
}
int convert(string source){
    int l=source.size();
    int b[l];
    int i=0;
    for(;i<l;i++){
        b[i]=(int)(source[i]-48);
    }
    i=l-1;
    int sum=0;
    for(;i>=0;i--){
        sum =b[i]*pow(10,(l-1-i)) + sum;
    }
    return sum;
}
int main(){
    bool loop=true;
    while(loop){
        bool success=false;
        cout<<"Are you a new user?(y/n)"<<endl;
        string ans="";
        ans.clear();
        getline(cin,ans);
        string username="";
        string pwd="";
        if(ans=="y"){  //new user
            cout<<"Please provide information of new account:"<<endl;
            cout<<"Username:";
            username.clear();
            getline(cin,username);
            username=username; //encode
            cout<<"Password:";
            pwd.clear();
            getline(cin,pwd);
            pwd=sha256(pwd);  //encode
            reg(username,pwd);
            success=true;
        }
        else{          //return user
            while(!success){
                cout<<"Username:";
                username.clear();
                getline(cin,username);
                cout<<"Password:";
                pwd.clear();
                getline(cin,pwd);
                username=username; //encode
                pwd=sha256(pwd);  //encode
                if(login(username,pwd)){
                //successful login interface
                    success=true;
                }
                else{
                     cout<<"Invalid username or password!"<<endl;
                     cout<<"Want try again?(y/n)";
                     ans.clear();
                     getline(cin,ans);
                     if(ans=="y"){
                         continue;
                     }
                     else{
                         loop=false;
                         break;
                     }
                }
            }
        }
        if(success){
            vector<int> m_ID_set;
            string command;
            bool inLoop=true;
            while(inLoop){
                cout<<"R(read message)  S(send message)  E(exit)"<<endl;
                
                command.clear();
                getline(cin,command);
                if(command=="R"||command=="r"){
                    vector<vector<string> > MessageTable=receive(username);
                    if(MessageTable.size()>0){
                        int i;
                        for(i=0;i<MessageTable.size();i++){
                            int j;
                            for(j=0;j<MessageTable[i].size();j++){
                                if(j==0){
                                    m_ID_set.push_back(i);
                                    cout<<i<<" ";
                                }
                                else{
                                    cout<<MessageTable[i][j]<<" ";
                                }
                            }
                            cout<<endl;
                        }
                        while(1){
                            cout<<"Select the message ID you want to read:";
                            string m_ID="";
                            getline(cin,m_ID);
                            cout<<"Enter passphrase:";
                            string passphrase;
                            passphrase.clear();
                            getline(cin,passphrase);
                            int temp=convert(m_ID);
                            if(Find(m_ID_set,temp)){
                                //char* temp_ID=&(MessageTable[m_ID][0]);
                                cout<<decrypt(read(convert(MessageTable[temp][0])),passphrase)<<endl;
                                cout<<"B(back to previous level) H(home)"<<endl;
                                  a:
                                    string jump;
                                    jump.clear();
                                    getline(cin,jump);
                                    if(jump=="B"){
                                        continue;
                                    }
                                    else if(jump=="H" || jump=="h"){
                                        break;
                                    }
                                    else{
                                        cout<<"Wrong command!"<<endl;
                                        cout<<"Try again!"<<endl;
                                        goto a;
                   
                                    }
                                
                            }

                            else{
                                cout<<"ID doesn't exist! Want try again?(y/n)"<<endl;
                                getline(cin,ans);
                                if(ans=="y"){
                                    continue;
                                }
                                else{
                                    break;
                                }
                            }
                        }
                    }
                    else{
                        cout<<"You didn't receive any email."<<endl;
                    }
                }
                else if(command=="S"||command=="s"){
                    cout<<"Enter the username you want send to:";
                    string send_to_user;
                    getline(cin,send_to_user);
                    cout<<"Enter the title of the email:";
                    string title;
                    getline(cin,title);
                    cout<<"enter passphrase:";
                    string passphrase;
                    getline(cin,passphrase);
                    cout<<"Message body:"<<endl;
                    string message;
                    getline(cin,message);
                    string ciphermessage;
                    ciphermessage = encrypt(message,passphrase);
                    if(send(username,send_to_user,ciphermessage,title)){
                        cout<<"Email has been sent successfully!"<<endl;
                    }
                    else{
                        cout<<"Email can not be sent!"<<endl;
                    }
                }
                else if(command=="E"||command=="e"){
                    inLoop=false;
                }
                else{
                     cout<<"Wrong command!"<<endl;
                }
            }
        }
    }
    return 0;
}
