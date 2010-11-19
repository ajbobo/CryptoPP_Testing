// AES_Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <cryptlib.h>
#include <filters.h>
#include <modes.h>
#include <aes.h>
#include <hex.h>

#include <iostream>
#include <string>

using namespace std;
using namespace CryptoPP;

#define KEY_LEN AES::DEFAULT_KEYLENGTH

int _tmain(int argc, _TCHAR* argv[])
{
	string plaintext = "Welcome to the next level. Welcome to the next Level.";
	
	cout << "Key length: " << KEY_LEN << endl;
	char key[KEY_LEN], iv[KEY_LEN];
	while (1)
	{
		cout << "Enter the key (or 'quit'): ";
		cin >> key;
		if (strcmp(key,"quit") == 0)
			break;
		cout << "Enter the Initialization Vector: ";
		cin >> iv;

		// Pad the key and IV
		for (int x = strlen(key); x < KEY_LEN; x++)
			key[x] = '2';
		for (int x = strlen(iv); x < KEY_LEN; x++)
			iv[x] = '2';

		//string hexkey, hexiv;
		//StringSource(key,false,new HexEncoder(new StringSink(hexkey))).Pump(KEY_LEN);
		//StringSource(iv,false,new HexEncoder(new StringSink(hexiv))).Pump(KEY_LEN);
		//cout << "HexKey: " << hexkey << endl;
		//cout << "HexIV:  " << hexiv << endl;

		try
		{
			string output;
			CTR_Mode<AES>::Encryption encrypt((const byte*)key,KEY_LEN,(const byte*)iv);
			StringSource(plaintext, true, new StreamTransformationFilter(encrypt, new StringSink(output)));
			cout << "Encrypted: " << output << endl;

			string res;
			CTR_Mode<AES>::Decryption decrypt((const byte*)key,KEY_LEN,(const byte*)iv);
			StringSource(output, true, new StreamTransformationFilter(decrypt, new StringSink(res)));
			cout << "Decrypted: " << res << endl;

			cout << endl;
		}
		catch (Exception ex)
		{
			cout << ex.GetWhat() << endl;
		}
	}


	return 0;
}

