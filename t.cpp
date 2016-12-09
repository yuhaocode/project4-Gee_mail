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
#include <math.h>
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
    
    

int main(){
  vector<int> s;
  s.push_back(1);
  s.push_back(2);
  s.push_back(3);
  s.push_back(4);
  s.push_back(5);
  s.push_back(6);
  s.push_back(7);
  s.push_back(8);
  s.push_back(9);
  s.push_back(10);
  s.push_back(11);
  if(Find(s,12)){
    cout<<"got it!"<<endl;
    
  }
  else{
    cout<<"wrong!"<<endl;
  }
  return 0;
}
