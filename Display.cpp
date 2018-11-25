#include "Display.h"
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
		this->login = login;
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

		if (users.find(this->login) != users.end())
		{
			if (users.find(this->login)->second == password)
			{
				result = true;
				return result;
			}
			else
			{
				cout << "wrong password" << endl;
				return result;
			}
		}
		else
		{
			cout << "user not found" << endl;
			return result;
		}

		return result;
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
		planningScreen();
		break;
	case 2:
		cout << "You chose Course choice" << endl;
		break;
	case 3:
		cout << "You logged out" << endl;
		break;
	}
}

void Display::planningScreen()
{
	fstream infile("planning.txt"); //line impaire = login. Ligne paire = vecteur. 1er élément : nbre de cours suivis. le reste : indique si le cours i est suivi ou non
	map<string, vector<int>> loginToPlanning;
	vector<int> coursesFollowed;
	vector<string> courseNames = { "Math", "Physics", "VHDL", "Another Useless One", "Haskell Programming", "SAM" };
	string line;
	string login;
	bool isLineEven = false;
	int isFollowed;
	string s_isFollowed;

	if (infile.fail())
	{
		cout << "error opening file" << endl;
	}
	else
	{
		while (getline(infile, line)) //Lecture des données sauvegardées dans planning.txt et restitution dans la map.
		{
			if (isLineEven)
			{
				stringstream linestream(line);
				while (getline(linestream, s_isFollowed, ' '))
				{
					coursesFollowed.push_back(stoi(s_isFollowed));
				}

				loginToPlanning.insert(make_pair(login, coursesFollowed));
				coursesFollowed.clear();
				isLineEven = false;
			}
			else
			{
				login = line;
				isLineEven = true;
			}
		}

		infile.close();

		cout << "current login : " << this->login << endl;

		map<string, vector<int>>::iterator found = loginToPlanning.find(this->login);

		if (found == loginToPlanning.end())
		{
			cout << "No courses taken. Planning created. You can now enroll in courses" << endl;
 			fstream outfile("planning.txt", fstream::app | fstream::out);
			if (outfile.fail())
			{
				cout << "error creating file" << endl;
			}
			else
			{
				outfile << endl << this->login << endl;
				for (int i = 0; i < 7; i++)
				{
					outfile << "0 ";
				}
			}

			outfile.close();
		}
		else //Display enrolled courses
		{
			cout << "You are enrolled in " << *found->second.begin() << " courses" << endl;
			int i = 0;
			for (auto it = found->second.begin() + 1; it != found->second.end(); it++)
			{
				if (*it == 1)
				{
					cout << courseNames[i] << ";";
				}
				i++;
			}
			cout << endl;
		}
	}
}

void Display::clearScreen()
{
	cout << string(100, '\n');
}