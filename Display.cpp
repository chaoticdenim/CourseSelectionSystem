#include "Display.h"
#include "listeCours.h"
using namespace std;


void Display::session()
{
	cout << "*******LOGIN SCREEN***********" << endl;

	Eleve* currentUser = this->loginScreen();

	if (currentUser->getId() != "NULL") //If login sucessful
	{
		this->clearScreen();
		cout << "login successful\n" << "*****Welcome " << currentUser->getPrenom() << " " << currentUser->getNom() << "*****" << endl;
		this->menu(currentUser);
	}
	else
	{
		cout << "failed login" << endl;
		this->session();
	}
}

Eleve* Display::loginScreen()
{

	Eleve* ep = new Eleve();
	string login;
	string password;
	string flogin, fpassword, fname, fsurname;
	bool loginSuccess = false;

	while (!loginSuccess)
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

		while (infile >> flogin >> fpassword >> fname >> fsurname)
		{
			if (login == flogin && fpassword == password)
			{
				ep->setId(login);
				ep->setMdp(password);
				ep->setNom(fsurname);
				ep->setPrenom(fname);
				ep->setPlanningFromFile();
				loginSuccess = true;
				break;
			}
		}

		if (!loginSuccess)
		{
			cout << "failed login. please try again" << endl;
		}
	}

	return ep;
}

int Display::menu(Eleve* e)
{
	
	int selection;
	cout << endl << endl << "1. Check my current Planning" << endl << "2. Register for a course" << endl << "3. Unregister from a Course" << endl << "4. Logout" << endl << "5. Logout and Quit" << endl;
	cout << "selection: " << endl;
	cin >> selection;
	this->clearScreen();
	

	switch (selection)
	{
		case 1:
			this->planningScreen(e);
			this->menu(e);
			break;
		case 2:
			this->registerToCourse(e);
			this->menu(e);
			break;
		case 3:
			this->unregisterFromCourse(e);
			this->menu(e);
			break;
		case 4:
			this->logout(e);
			this->session();
			break;
		case 5:
			this->logout(e);

			cout << " ____                   ____             _" << endl;
			cout << "| __ ) _   _  ___      | __ ) _   _  ___| |" << endl;
			cout << "|  _ \\| | | |/ _ \\_____| _  \\| | | |/ _ \\ |" << endl;
			cout << "| |_) | |_| |  __/_____| |_) | |_| |  __/_|" << endl;
			cout << "|____ /\\__, |\\___|     |____ /\\__, |\\___(_)" << endl;
			cout << "        |___/                  |___/" << endl;

			cout << "Have a nice day!" << endl;
			break;
	}
	

	return selection;
}

void Display::planningScreen(Eleve* e)
{
	listeCours lc;
	int index;
	vector<string> courseNames; //vector similar to lc.availableCourses but only contains the names of the courses.

	for (unsigned int i = 0; i < lc.availableCourses.size(); i++)
	{
		courseNames.push_back(lc.availableCourses[i].getNomCours());
	}

	if (e->isPlanningEmpty())
	{
		cout << "You haven't registered for any courses yet. " << endl;
	}
	else
	{
		cout << "You are enrolled in :" << endl;

		for (int i = 0; i < 4; i++)
		{
			if (e->getPlanning()[i].getNomCours() != "NULL")
			{
				vector<string>::iterator it = find(courseNames.begin(), courseNames.end(), e->getPlanning()[i].getNomCours());
				index = it - courseNames.begin();
				cout << endl << i + 1 << ". Course name: " << lc.availableCourses[index].getNomCours() << endl << "Location: "
					<< lc.availableCourses[index].getLocation() << endl << "Professor: " << lc.availableCourses[index].getProf() << endl;
			}
				
		}
	}
}

void Display::registerToCourse(Eleve* e)
{
	int regNumber;
	string yesNo;
	listeCours lc; //Create an object to store all available courses as described in cours.txt
	lc.displayAvailableCourses(e);

	cout << "\n\nTo register for a class, simply enter the corresponding number" << endl;
	cin >> regNumber;

	switch (e->AddCours(lc.availableCourses[regNumber-1]))
	{
	case 0:
		cout << "Registration successful." << endl << lc.availableCourses[regNumber-1].getNomCours() << " added to your planning" << endl;
		break;
	case 1:
		cout << "You already registered to " << lc.availableCourses[regNumber-1].getNomCours() << ". Please try another one" << endl;
		break;
	case 2:
		cout << "You are registered to the maximum number of courses (4). Please delete a course first" << endl;
		cout << "Do you want to delete a course ?" << endl << "[y/n]";
		cin >> yesNo;
		if (yesNo == "y")
		{
			this->unregisterFromCourse(e);
			if (e->AddCours(lc.availableCourses[regNumber - 1]) == 0)
			{
				cout << "Registration successful." << endl << lc.availableCourses[regNumber - 1].getNomCours() << " added to your planning" << endl;
			}
			else
			{
				cout << "failed to add course" << endl;
			}
		}

	}
	
}

void Display::logout(Eleve* e)
{
	e->savePlanning();
	cout << "You logged out" << endl;
}

void Display::unregisterFromCourse(Eleve* e)
{
	int delNumber;

	cout << "Which one ?" << endl;
	for (int i = 0; i < 4; i++)
	{
		if(e->getPlanning()[i].getNomCours() != "NULL")
			cout << i + 1 << ". " << e->getPlanning()[i].getNomCours() << endl;
	}
	cin >> delNumber;

	if (e->RmCours(e->getPlanning()[delNumber - 1].getNomCours()))//delete selected course from planning
		cout << "course successfully deleted" << endl;
	else
	{
		cout << "you are not registered to this course" << endl;
	}	
}

void Display::clearScreen()
{
	cout << string(100, '\n');
}