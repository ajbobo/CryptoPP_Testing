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

	try
	{
		int bitsperchar = 2; // 1-7 are valid values
		int numchars = (int)pow(2.0,bitsperchar);
		const byte alphabet[] = "0123";//456789ABCDEFGHIJKLMNOPQRSTUV"; // This needs to have numchars unique characters in it
		int lookup[256];
		BaseN_Decoder::InitializeDecodingLookupArray(lookup,alphabet,numchars,false);
		
		int len = ceil(plainstr.length() * 8.0 / bitsperchar) + 1;
		byte *hashstr = new byte[len];
		memset(hashstr,0,len);
		BaseN_Encoder encode;
		StringSource(plainstr, true, new BaseN_Encoder(alphabet, bitsperchar, new ArraySink(hashstr,len),0));
		cout << hashstr << endl;
		
		int shortlen = plainstr.length() + 1;
		byte *endres = new byte[shortlen];
		memset(endres,0,shortlen);
		ArraySource(hashstr, len, true, new BaseN_Decoder(lookup, bitsperchar, new ArraySink(endres,shortlen)));
		cout << endres << endl;
		
		delete[] hashstr;
		delete[] endres;

		// For some reason this crashes when connected to a Crypto++'s DLL if plainstr is more than 5 characters long
		//string secondhash;
		//StringSource(plainstr, true, new HexEncoder(new StringSink(secondhash),true,2));
		//cout << secondhash << endl;
	}
	catch (Exception ex)
	{
		cout << ex.GetWhat() << endl;
	}

	return 0;
}

