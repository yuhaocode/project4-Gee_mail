#include <iostream>

#include "salsa20.h"
using namespace std;
using namespace CryptoPP;


using CryptoPP::Salsa20;


using CryptoPP::AutoSeededRandomPool;


using std::cout;
using std::endl;

string encrypt(string text, string passPhrase){

    string cipherText;
    int stretch=100;
    string salt="mysalt";
    string theHash="0"+passPhrase+salt;
    theHash=sha256(theHash);
    int i=0;
    for(;i<stretch-1;i++){
        theHash=sha256(theHash+passPhrase+salt);
    }
    int l=text.size();
    byte textBytes[l];
    byte keyBytes[32];
    for(i=0;i<32;i++){
        keyBytes[i]=(byte)theHash[i];
    }
    i=0;
    for(;i<l;i++){
        textBytes[i]=(byte)text[i];
    }
    cipherText=salsa_encrypt(keyBytes,textBytes ,l);
    return cipherText;
}
void Print(byte* t,string name,int l){
  	cout<<name;
  	int i=0;
    for(;i<l;i++){
       cout<<t[i];
    }
    cout<<endl;
}
void PrintIv(string t,string name,int l){
  	cout<<name;
  	int i=0;
    for(;i<l;i++){
       cout<<t[i];
    }
    cout<<endl;
}
void convert(string source, byte* target){
    int i=0;
    for(;i<source.size();i++){
      target[i]=source[i];
    }
}

//-------------------------------------------------------
string salsa_encrypt(byte* keyBytes,byte* textBytes,int numBytes) {
	AutoSeededRandomPool prng;
  
	string ciphertextStr("");
	//string plaintextStr(text);
	//byte *plaintextBytes = (byte *) plaintextStr.c_str();
	//I could statically allocate this, but then changes will require work, and typing
	byte *ciphertextBytes = new byte[numBytes];

	//~Key and IV Generation/Initialization======================================
	/////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////
	byte iv[8];
	//prng.GenerateBlock(key, numBytes);
	
	prng.GenerateBlock(iv, sizeof(iv));
	//~Encryption================================================================
	/////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////

	Salsa20::Encryption salsa;
	salsa.SetKeyWithIV(keyBytes, 32, iv);
	salsa.ProcessData(ciphertextBytes, textBytes, numBytes);
	ciphertextStr.assign((char *) ciphertextBytes);
  std::string s(reinterpret_cast<char*>(iv), sizeof(iv));
	//Output plaintext/ciphertext for sanity check
	ciphertextStr=s+ciphertextStr;
	//cout<<"ciphertextStr : "<<ciphertextStr<<endl;
	//Output newly decrypted plaintext
	//cout << "Plaintext Again: " << plaintextStr << endl << endl;
	//cout << endl << "SALSA!" << endl << endl << "     " << "...20..." << endl;
    s.clear();
    delete ciphertextBytes;
    return ciphertextStr;
}

string decrypt(string ciphertextStr,string passPhrase){
    int stretch=100;
    string salt="mysalt";
    string theHash="0"+passPhrase+salt;
    theHash=sha256(theHash);
    int i=0;
    for(;i<stretch-1;i++){
        theHash=sha256(theHash+passPhrase+salt);
    }
    byte ivBytes[8];
    byte keyBytes[32];
    for(i=0;i<32;i++){
        keyBytes[i]=(byte)theHash[i];
    }
    i=0;
    for(;i<8;i++){
        ivBytes[i]=(byte)ciphertextStr[i];
    }
    byte ciphertextBytes[ciphertextStr.size()-8];
   // 
    string Text=salsa_decrypt(ciphertextStr.substr(8),keyBytes,ivBytes);
    return Text;
}

string salsa_decrypt(string ciphertextStr, byte* key, byte* iv) {
  string plaintextStr;
  byte* plaintextBytes = new byte[ciphertextStr.size()];
  byte *ciphertextBytes = new byte[ciphertextStr.size()];
  convert(ciphertextStr,ciphertextBytes);
  plaintextStr.assign("");
  
  
  Salsa20::Encryption salsa;	
	//Reset Key & IV
	//!!! THIS IS IMPORTANT: If you do not reset the stream cipher the data will
		//be encrypted again with a different part of the streaming key
		//Resetting the key & IV ensure that the same key is used, and we decrypt
	/////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////
	salsa.SetKeyWithIV(key, 32, iv);
  salsa.ProcessData(plaintextBytes, ciphertextBytes, ciphertextStr.length());
	plaintextStr.assign((char *) plaintextBytes);

	//Output newly decrypted plaintext


  delete plaintextBytes;
  delete ciphertextBytes;
	return plaintextStr;
}


// int main(){
// string f = encrypt("abcfewfeefwe ewfwef","124");
//   cout<<f<<endl;
//   string h =decrypt(f,"124");
//   cout<<h<<endl;
//   return 0;
// }
