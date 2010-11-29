#ifndef _UserList
#define _UserList

#include <cryptlib.h>
#include <sha.h>
#include <base64.h>

#include <string>

using namespace std;

#define HASH SHA
#define ENCODER Base64Encoder
#define DECODER Base64Decoder

#define MAX_NAME_LENGTH 10
#define PASSWORD_LENGTH 28

/**************************************************************************
 The password length is based on the hashing algorithm and encoding scheme.
 length = ceil( DigestSize * 8 / BitsPerCharacter )
 Base64 rounds up to the nearest multiple of 4
 Here are the possible values:
          No Encoding | Hex  | Base32 | Base64 |
 SHA-1  |     20      |  40  |   32   |   28   |
 SHA224 |     28      |  56  |   45   |   40   |
 SHA256 |     32      |  64  |   52   |   44   |
 SHA384 |     48      |  96  |   77   |   64   |
 SHA512 |     64      |  128 |   103  |   88   |
 **************************************************************************/
struct User
{
	// The two arrays need to be big enough to store a null-terminator
	char Name[MAX_NAME_LENGTH + 1];
	char PasswordHash[PASSWORD_LENGTH + 1];
	User *Next;
};

User *FindLastUser();
User *FindUser(string username);
void MakeUser(string username, string password);

#endif