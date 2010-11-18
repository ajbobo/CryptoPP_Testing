// SimpleHashing.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <cryptlib.h>
#include <filters.h>
#include <sha.h>
#include <base64.h>

#include <string>
#include <iostream>


using namespace std;
using namespace CryptoPP;

int _tmain(int argc, _TCHAR* argv[])
{
	string password;

	cout << "Enter the password: ";
	cin >> password;

	// Hash the password and store the result
	SHA512 chosen_hash;
	string hashedstr;
	StringSource(password, true, new HashFilter(chosen_hash, new Base64Encoder(new StringSink(hashedstr),false)));
	//StringSource(password, true, new HashFilter(chosen_hash, new StringSink(hashedstr)));

	cout << "HASH: " << hashedstr << endl; // Show the hash in Base64

	while (1) // There'll be a break to get out of this
	{
		string mystr;
		cout << "Enter a string (or \"quit\"): ";
		cin >> mystr;
		if (mystr == "quit")
			break;

		// Decode the Base64 hash and concatenate the hash with the test string
		StringSource(hashedstr,true,new Base64Decoder(new StringSink(mystr)));
		//cout << "Test string: _" << mystr << "_" << endl;

		// Check to see if the test string matched the hash
		byte output[1];
		word32 flags = HashVerificationFilter::HASH_AT_END | HashVerificationFilter::PUT_RESULT;
		StringSource(mystr, true, new HashVerificationFilter(chosen_hash,new ArraySink(output, sizeof(output)),flags));

		cout << "output: _" << output[0] << "_ -> " << (output[0] ? "CORRECT" : "WRONG") << endl;
	}
	

	return 0;
}

