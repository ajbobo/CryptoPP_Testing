#ifndef _UserList
#define _UserList

#include <string>

using namespace std;

#define MAX_NAME_LENGTH 10
#define PASSWORD_LENGTH 28

struct User
{
	char Name[MAX_NAME_LENGTH];
	char PasswordHash[PASSWORD_LENGTH];
	User *Next;
};

User *FindLastUser();
User *FindUser(string username);
void MakeUser(string username, string password);

#endif