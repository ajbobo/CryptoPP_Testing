// SimpleHashing.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <cryptlib.h>
#include <filters.h>
#include <sha.h>
#include <hex.h>
#include <base32.h>
#include <base64.h>

#include <string>
#include <iostream>


using namespace std;
using namespace CryptoPP;

void Hash(string &text, HashTransformation &hash)
{
	string res;
	StringSource(text, true, new HashFilter(hash, new StringSink(res), false));
	cout << hash.AlgorithmName() << " | None : " << res.length() << endl;
}

void HashWithEncoding(string &text, HashTransformation &hash, BufferedTransformation &encoding, string encodingname)
{
	string res;

	encoding.Detach(new StringSink(res));
	StringSource(text, true, new HashFilter(hash, new Redirector(encoding), false)); // The Redirector's attachment is NOT automatically deleted when the StringSource is
	cout << hash.AlgorithmName() << " | " << encodingname << " : " << res.length() << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	string text = "ABC";
	byte alphabet[4] = {'A', 'B', 'C', 'D'};

	SHA sha;
	SHA224 sha224;
	SHA256 sha256;
	SHA384 sha384;
	SHA512 sha512;

	HexEncoder hex;
	Base32Encoder base32;
	Base64Encoder base64(NULL, false, 100);
	BaseN_Encoder base4(alphabet,2);

	Hash(text, sha);
	HashWithEncoding(text, sha, hex, "Hex");
	HashWithEncoding(text, sha, base4, "Base4");
	HashWithEncoding(text, sha, base32, "Base32");
	HashWithEncoding(text, sha, base64, "Base64");
	cout << endl;

	Hash(text, sha224);
	HashWithEncoding(text, sha224, hex, "Hex");
	HashWithEncoding(text, sha224, base4, "Base4");
	HashWithEncoding(text, sha224, base32, "Base32");
	HashWithEncoding(text, sha224, base64, "Base64");
	cout << endl;

	Hash(text, sha256);
	HashWithEncoding(text, sha256, hex, "Hex");
	HashWithEncoding(text, sha256, base4, "Base4");
	HashWithEncoding(text, sha256, base32, "Base32");
	HashWithEncoding(text, sha256, base64, "Base64");
	cout << endl;

	Hash(text, sha384);
	HashWithEncoding(text, sha384, hex, "Hex");
	HashWithEncoding(text, sha384, base4, "Base4");
	HashWithEncoding(text, sha384, base32, "Base32");
	HashWithEncoding(text, sha384, base64, "Base64");
	cout << endl;

	Hash(text, sha512);
	HashWithEncoding(text, sha512, hex, "Hex");
	HashWithEncoding(text, sha512, base4, "Base4");
	HashWithEncoding(text, sha512, base32, "Base32");
	HashWithEncoding(text, sha512, base64, "Base64");
	cout << endl;

	return 0;
}

