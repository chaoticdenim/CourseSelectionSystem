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
	int selection;
	cout << "login successful\n\n\n" << endl;
	cout << "Welcome to our Fabulous Program !" << endl << endl << "1. Check my current Planning" << endl << "2. Browse Available Course" << endl << "3. Logout" << endl;
	cout << "selection: " << endl;
	cin >> selection;

	switch (selection)
	{
	case 1:
		cout << "You choose Planning" << endl;
		break;
	case 2:
		cout << "You chose Course choice" << endl;
		break;
	case 3:
		cout << "You logged out" << endl;
		break;
	}
}

void Display::clearScreen()
{
	cout << string(100, '\n');
}