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

void listeCours::displayAvailableCourses()
{
	int i = 0;
	for (vector<Cours>::iterator it = availableCourses.begin(); it != availableCourses.end(); it++)
	{
		cout << i+1 << ". Course: " << it->getNomCours() << endl << "Classroom: " << it->getLocation() << endl << "Professor: " << it->getProf() << endl << endl;
		i++;
	}
}
