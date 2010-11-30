// Switching.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <cryptlib.h>
#include <filters.h>
#include <channels.h>

#include <iostream>
#include <string>

using namespace std;
using namespace CryptoPP;


int _tmain(int argc, _TCHAR* argv[])
{
	char instr[25];
	cout << "Enter a string: ";
	cin.getline(instr, 25);

	cout << instr << endl;

	string out1 = "ONE_";
	string out2 = "TWO_";

	StringSink sink1(out1);
	StringSink sink2(out2);

	ChannelSwitch *cs = new ChannelSwitch(sink1);
	cs->AddDefaultRoute(sink2);

	StringSource(instr,true,cs);

	cout << out1 << endl;
	cout << out2 << endl;

	return 0;
}

