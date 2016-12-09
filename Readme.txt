Gee_mail system

A simple mail system encrypted by Salsa20 and sha256. receiver need to input the same passphrase from sender that can decrypt the message

g++ salsa20.cpp sha.cpp main.cpp DBHelper.cpp DBConnector.cpp -lcrypto++ -lcrypto -lsqlite3 -o gee_mail

./gee_mail