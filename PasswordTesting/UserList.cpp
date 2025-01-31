#include "stdafx.h"
#include "UserList.h"

#include <string>

using namespace std;

User *UserList;

User *FindLastUser()
{
	// Find the last User in the list
	User *LastUser = UserList;
	while (LastUser != NULL && LastUser->Next != NULL)
		LastUser = LastUser->Next;

	return LastUser;
}

User *FindUser(string username)
{
	User *CurUser = UserList;
	while (CurUser != NULL)
	{
		if (CurUser->Name == username)
			return CurUser;
		CurUser = CurUser->Next;
	}

	return NULL;
}

void MakeUser(string username, string password)
{
	User *LastUser = FindLastUser();
	if (LastUser == NULL)
	{
		LastUser = new User();
		UserList = LastUser;
	}
	else
	{
		LastUser->Next = new User();
		LastUser = LastUser->Next;
	}

	strcpy_s(LastUser->Name,MAX_NAME_LENGTH + 1,username.c_str());
	strcpy_s(LastUser->PasswordHash,PASSWORD_LENGTH + 1,password.c_str());
	LastUser->Next = NULL;
}