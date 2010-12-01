// Files.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <cryptlib.h>
#include <files.h>
#include <hex.h>

#include <iostream>

using namespace std;
using namespace CryptoPP;


int _tmain(int argc, _TCHAR* argv[])
{
	// This writes the same string to the files in two different modes
	// In binary mode, the text is written to the file exactly as it was	
	// In non-binary mode, the text is written to the file with the \n converted to \r\n

	string teststr = "AB\nCD\n123";
	StringSource(teststr, true, new FileSink("notbinary.txt", false));
	StringSource(teststr, true, new FileSink("binary.txt", true));


	// These FileSources get the files exactly how they are on the disk, then display the hex values for the text read
	string filetext;
	FileSource("binary.txt", true, new HexEncoder(new StringSink(filetext), true, 2, ":"), true);
	cout << "binary.txt _" << filetext << "_" << endl;

	filetext.clear();
	FileSource("notbinary.txt", true, new HexEncoder(new StringSink(filetext), true, 2, ":"), true);
	cout << "notbinary.txt _" << filetext << "_" << endl;

	return 0;
}

