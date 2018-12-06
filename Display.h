#pragma once
#include <sstream>
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>
#include "Cours.h"
#include "Eleve.h"
using namespace std;

class Display
{
public:
	void session();
	Eleve* loginScreen();
	int menu(Eleve* e);
	void planningScreen(Eleve* e);
	void registerToCourse(Eleve* e);
	void unregisterFromCourse(Eleve* e);
	void logout(Eleve* e);
	void clearScreen();
private:
	string login;
};

