// Switching.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <cryptlib.h>
#include <filters.h>
#include <channels.h>
#include <hex.h>

#include <iostream>
#include <string>

using namespace std;
using namespace CryptoPP;


int _tmain(int argc, _TCHAR* argv[])
{
	char instr[25];
	cout << "Enter a string: ";
	cin.getline(instr, 25);

	// Display the string as entered, and in ASCII
	cout << instr << " --> ";
	for (size_t x = 0; x < strlen(instr); x++)
	{
		cout << (int)instr[x] << " ";
	}
	cout << endl;

	// Send the string down three different paths from a single source
	string out1 = "ONE_";
	string out2 = "TWO_";
	string out3 = "THREE_";

	StringSink sink1(out1);
	StringSink sink2(out2);
	HexEncoder sink3(new StringSink(out3),true,2,":");

	ChannelSwitch *cs = new ChannelSwitch(sink1);
	cs->AddDefaultRoute(sink2);
	cs->AddDefaultRoute(sink3);

	StringSource(instr,true,cs);

	cout << out1 << endl;
	cout << out2 << endl;
	cout << out3 << endl;

	return 0;
}

