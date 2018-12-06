//
// Created by alexi on 16/11/2018.
//

#pragma warning( disable : 4996)

#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "Eleve.h"
#include "Cours.h"

using namespace std;

Eleve::Eleve() {
    m_id="NULL";
    m_mdp="NULL";
    m_prenom="NULL";
    m_nom="NULL";

    for(int i=0;i<4;i++)
        m_planning.push_back( Cours());
}

ostream& operator<<(ostream& flux, const Eleve& eleve)
{
    flux<<"Id :"<<eleve.m_id;
    return flux;
}

void Eleve::setPlanningFromFile()
{
	ifstream infile("planning.txt");
	string line, planning, course;
	int i = -1;
	bool userFound = false;
	if (infile.fail())
	{
		cout << "can't open account.txt" << endl;
	}

	while (getline(infile, line) && !userFound) //read plannings from planning.txt
	{
		if (line == this->getId())
		{
			userFound = true;
			getline(infile, planning);
			istringstream planningstream(planning);

			while (planningstream >> course)
			{
				if (course != "NULL")
				{
					i++;
					this->m_planning[i] = Cours(course, "unknown", "unkown");
				}
			}
		}
	}

	if (i == -1)
	{
		this->m_planningEmpty = true;
	}
	else
	{
		this->m_planningEmpty = false;
	}
}

int Eleve::AddCours(Cours newCours)
{
    int ajout=0;
	vector<string> courseNames; //to prevent from adding 2 times the same course

	for (int i = 0; i < 4; i++)
	{
		courseNames.push_back(m_planning[i].getNomCours());
	}

	if (find(courseNames.begin(), courseNames.end(), newCours.getNomCours()) != courseNames.end())
	{
		return 1;
	}

    for(int i=0;i<4;i++)
    {
        if(m_planning[i].getNomCours()=="NULL")
        {
			if (this->isPlanningEmpty())
			{
				this->setPlanningEmpty(false);
			}
			m_planning[i] = Cours(newCours.getNomCours(), newCours.getProf(), newCours.getLocation());
            ajout=1;
			this->savePlanning();
			return 0;
        }
    }
	if (ajout == 0)
		return 2;
}
bool Eleve::RmCours(string nomCours)
{
    Cours libre; //on crée un cours sans initialiser les données membres
    int indice=0;
	int remaining = 0;
	bool found = false;
    for(int i=0;i<4;i++)
    {
        if(m_planning[i].getNomCours() == nomCours)
        {
			found = true;
            indice=i;
            m_planning[i]=libre;
        }
    }

    for(int j=indice;j<4;j++)
    {
        if (m_planning[j].getNomCours() != "NULL")
		{
			remaining++;
            m_planning[j-1] = m_planning[j];
            m_planning[j] = libre;
        }
    }

	if (remaining == 0)
	{
		this->setPlanningEmpty(true);
	}

	return found;
}

void Eleve::savePlanning()
{
	fstream infile("planning.txt");
	ofstream outfile("newplanning.txt");
	string line, course, newPlanning, old;
	bool planningExists = false;

	for (int i = 0; i < 4; i++)
	{
		course = m_planning[i].getNomCours();

		if (course != "NULL")
		{
			newPlanning += course + " ";
		}
	}

	newPlanning += "\n";



	if (infile.fail())
	{
		cout << "can't save because planning.txt doesn't exist" << endl;
	}

	while (getline(infile, line))
	{
		outfile << line << endl;

		if (line == this->getId())
		{
			planningExists = true;
			getline(infile, old); 
			outfile << newPlanning; // replace old with newPlanning
		}
	}

	if (!planningExists)
	{
		outfile << this->getId() << endl << "NULL" << endl;
	}

	infile.close();
	outfile.close();

	if (remove("planning.txt") == 0)
	{
	 
	}
	else
	{
		cout << "Can't remove planning.txt :" << strerror(errno) << endl;
	}


	if (rename("newplanning.txt", "planning.txt") == 0)
	{
	}
	else
	{
		cout << "Can't rename planning.txt :" << strerror(errno) << endl;
	}
}