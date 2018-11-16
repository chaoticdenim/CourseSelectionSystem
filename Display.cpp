#include "Display.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
using namespace std;

bool Display::loginScreen()
{
	string login;
	string password;
	string flogin, fpassword;
	bool result = false;
	map<string, string> users;

	while (!result)
	{
		cout << "Login: " << endl;
		cin >> login;
		cout << "Password: " << endl;
		cin >> password;

		ifstream infile("account.txt");

		if (infile.fail())
		{
			cout << "error opening file" << endl;
		}

		while (infile >> flogin >> fpassword)
		{
			users.insert(pair<string, string>(flogin, fpassword));
		}

		if (users.find(login) != users.end())
		{
			if (users.find(login)->second == password)
			{
				result = true;
				return result;
			}
			else
			{
				cout << "wrong password" << endl;
			}
		}
		else
		{
			cout << "user not found" << endl;
		}
	}	
}

void Display::menu()
{
	cout << "login successful\n\n\n" << endl;
	cout << "Welcome to our Fabulous Program !" << endl;
}

void Display::clearScreen()
{
	cout << string(100, '\n');
}