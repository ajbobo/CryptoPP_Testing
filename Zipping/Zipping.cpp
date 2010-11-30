// Zipping.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <cryptlib.h>
#include <filters.h>
#include <files.h>
#include <gzip.h>


#include <iostream>
#include <string>

using namespace std;
using namespace CryptoPP;

void DoZip(string filename, int deflate_level)
{
 	string outfile = filename;
	outfile = outfile.replace(outfile.length() - 4, 4, "-0.zzz");
	outfile[outfile.length() - 5] = (char)(deflate_level + '0');

	cout << "Creating " << outfile << "...";
	FileSource(filename.c_str(), true, new Gzip(new FileSink(outfile.c_str()), deflate_level));
	cout << "Done" << endl;
}

void ZipFile()
{
	string infile;
	cout << "Enter name of file to zip: ";
	cin >> infile;

	DoZip(infile,Gzip::MIN_DEFLATE_LEVEL);
	DoZip(infile,1);
	DoZip(infile,Gzip::DEFAULT_DEFLATE_LEVEL);
	DoZip(infile,Gzip::MAX_DEFLATE_LEVEL);

	cout << endl;
}

void UnzipFile()
{
	string infile;
	cout << "Enter name of file to unzip: ";
	cin >> infile;

	string outfile = infile;
	outfile = outfile.replace(outfile.length() - 3, 3, "res");

	cout << "Creating " << outfile << "...";
	FileSource(infile.c_str(), true, new Gunzip(new FileSink(outfile.c_str())));
	cout << "Done" << endl;

	cout << endl;
}


int _tmain(int argc, _TCHAR* argv[])
{
	bool done = false;
	while (!done)
	{
		int choice;
		cout << "Available options: " << endl;
		cout << "\t1) Zip a file" << endl;
		cout << "\t2) Unzip a file" << endl;
		cout << "\t3) Quit" << endl;
		cout << "Select an option: ";
		cin >> choice;

		switch (choice)
		{
		case 1: ZipFile(); break;
		case 2: UnzipFile(); break;
		case 3: done = true; break;
		}
	}
	return 0;
}

