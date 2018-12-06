#include <fstream>
#include <sstream>
#include "listeCours.h"

using namespace std;

listeCours::listeCours() // Creates the list of courses from cours.txt
{
	ifstream infile("cours.txt");
	string line, name, location, prof;
	int i = 0;

	while (getline(infile, line))
	{
		stringstream linestream(line);
		linestream >> name >> location >> prof;
		availableCourses.push_back(Cours(name, prof, location));
	}
}

void listeCours::displayAvailableCourses(Eleve* e)
{
	int i = 0;
	bool taken = false;
	for (vector<Cours>::iterator it = availableCourses.begin(); it != availableCourses.end(); it++)
	{

		for (int i = 0; i < 4; i++)
		{
			if (it->getNomCours() == e->getPlanning()[i].getNomCours())
				taken = true;
		}
		if (!taken)
			cout << i + 1 << ". Course: " << it->getNomCours() << endl << "Classroom: " << it->getLocation() << endl << "Professor: " << it->getProf() << endl << endl;
		else
			taken = false;
		i++;
	}
}
