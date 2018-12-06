#pragma once

#include"Cours.h"
#include "Eleve.h"
#include <vector>


using namespace std;

class listeCours
{
public:
	listeCours();
	vector<Cours> availableCourses;
	void displayAvailableCourses(Eleve* e);
};

