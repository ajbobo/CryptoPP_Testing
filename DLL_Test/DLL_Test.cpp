// DLL_Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// Include the dll-version of Crypto++
#include <dll.h>

#include <iostream>
#include <string>
#include <cmath>

using namespace std;
using namespace CryptoPP;

void Hashing()
{
	string plainstr;
	cout << "Enter a string to hash: ";
	cin >> plainstr;

	SHA hash;
	while (1)
	{
		string teststr;
		cout << "Enter string to test (or 'quit'): ";
		cin >> teststr;
		if (teststr == "quit")
			break;

		int len = SHA::DIGESTSIZE + teststr.length() + 1;
		byte *hashstr = new byte[len];
		memset(hashstr,0,len);
		StringSource source(plainstr,true,new HashFilter(hash, new ArraySink(hashstr,SHA::DIGESTSIZE)));
		for (size_t x = 0; x < teststr.length(); x++)
			hashstr[SHA::DIGESTSIZE + x] = teststr[x];
		cout << "Hash: " << hashstr << endl;

		byte result[1];
		word32 flags = HashVerificationFilter::HASH_AT_BEGIN | HashVerificationFilter::PUT_RESULT;
		ArraySource(hashstr,len - 1,true,new HashVerificationFilter(hash, new ArraySink(result,sizeof(result)), flags)); // Make sure the null-terminator isn't pumped by the Source
		if (result[0] == 1)
			cout << "CORRECT" << endl;
		else
			cout << "WRONG" <<  endl;

		delete[] hashstr;
	}
}

void Encoding()
{
	string plainstr;
	cout << "Enter a string to encode: ";
	cin >> plainstr;

	// ENCODING/DECODING
	int bitsperchar = 2; // 1-7 are valid values
	int numchars = (int)pow(2.0,bitsperchar);
	const byte alphabet[] = "0123";//456789ABCDEFGHIJKLMNOPQRSTUV"; // This needs to have numchars (2^bitsperchar) unique characters in it
	int lookup[256];
	BaseN_Decoder::InitializeDecodingLookupArray(lookup,alphabet,numchars,false);
	
	int len = (int)ceil(plainstr.length() * 8.0 / bitsperchar) + 1; // Calculate the bytes required for the translation, plus a null-terminator
	byte *hashstr = new byte[len]; // For some reason, using a string here causes a crash during deallocation when connected to the Crypto++ DLL
	memset(hashstr,0,len);
	StringSource(plainstr, true, new BaseN_Encoder(alphabet, bitsperchar, new ArraySink(hashstr,len),0));
	cout << hashstr << endl;
	
	int shortlen = plainstr.length() + 1;
	byte *endres = new byte[shortlen];
	memset(endres,0,shortlen);
	ArraySource(hashstr, len, true, new BaseN_Decoder(lookup, bitsperchar, new ArraySink(endres,shortlen)));
	cout << endres << endl;
	
	delete[] hashstr;
	delete[] endres;
}

void Encrypting()
{
	string inputname = "input.txt";
	string outputname = "output.txt";
	string encryptedname = "encrypted.txt";

#define KEY_LEN AES::DEFAULT_KEYLENGTH * 2
	char key[KEY_LEN + 1]; // Needs a null-terminator to be deallocated correctly, but don't pass the terminator to AES
	cout << "Enter the encryption key (max length: " << KEY_LEN << "): ";
	cin >> key;
	int len = strlen(key);
	if (len < KEY_LEN)
		memset(&key[len],1,KEY_LEN - len); // Add padding
	key[KEY_LEN] = 0;
	
	// Clear out the two destination files - is there a better way to do it?
	StringSource("",true,new FileSink(outputname.c_str(),false));
	StringSource("",true,new FileSink(encryptedname.c_str(),false));

	// I need to use the Encoder because there seem to be characters in the raw encryption that screw things up when they are read from a file (newlines, etc)
	CTR_Mode<AES>::Encryption encrypt((const byte*)key, KEY_LEN, (const byte*)key); // Using the Key as the Initialization Vector as well
	FileSource(inputname.c_str(), true, new StreamTransformationFilter(encrypt, new HexEncoder(new FileSink(encryptedname.c_str(), false), true, 50, "\n")), false);

	CTR_Mode<AES>::Decryption decrypt((const byte*)key, KEY_LEN, (const byte*)key);
	FileSource(encryptedname.c_str(), true, new HexDecoder(new StreamTransformationFilter(decrypt, new FileSink(outputname.c_str(), false))), false);
}


int _tmain(int argc, _TCHAR* argv[])
{
	bool done = false;
	int choice;
	while (!done)
	{
		cout << "Available options:" << endl;
		cout << " 1) Encoding" << endl;
		cout << " 2) Hashing" << endl;
		cout << " 3) AES Encrypting" << endl;
		cout << " 4) Quit" << endl;
		cout << "Select an operation: ";
		cin >> choice;

		switch (choice)
		{
		case 1: Encoding(); break;
		case 2: Hashing(); break;
		case 3: Encrypting(); break;
		case 4: done = true; break;
		default:
			cout << "Invalid option. Enter 1-4" << endl;
			break;
		}

		cout << endl;
	}

	return 0;
}

