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


int _tmain(int argc, _TCHAR* argv[])
{
	string plainstr;
	cout << "Enter a string to hash: ";
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

	// SHA HASHING/VERIFYING
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

	return 0;
}

