#ifndef SALSA20_H_
#define SALSA20_H_
#include <iostream>
#include <string>
#include "crypto++/osrng.h"
#include "crypto++/salsa.h"
#include "crypto++/hex.h"
#include "crypto++/filters.h"
#include "sha.h"
using namespace CryptoPP;
using namespace std;
string encrypt(string text,string passPhrase);
string salsa_encrypt(byte* keyBytes,byte* textBytes,int numBytes);
string decrypt(string ciphertextStr,string passPhrase);
string salsa_decrypt(string ciphertextStr, byte* key, byte* iv);


#endif