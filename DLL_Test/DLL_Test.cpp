// DLL_Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// Include the dll-version of Crypto++
#include "dll.h"

#include <iostream>
#include <string>

using namespace std;
using namespace CryptoPP;


int _tmain(int argc, _TCHAR* argv[])
{
	string plainstr;
	cout << "Enter a string to hash: ";
	cin >> plainstr;

	try
	{
		SHA hash_function;
		string hashstr;
		StringSource(plainstr, true, new HexEncoder(new StringSink(hashstr),true,2));


		cout << hashstr << endl;
	}
	catch (Exception ex)
	{
		cout << ex.GetWhat() << endl;
	}

	return 0;
}

