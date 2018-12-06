#include <iostream>
#include <vector>
#include <string>

#include "Cours.h"

using namespace std;

#pragma once


class Eleve{
public:
    Eleve();
    Eleve(string id, string mdp, string nom, string prenom) {m_id=id; m_mdp=mdp; m_nom=nom; m_prenom=prenom;}
    friend ostream& operator<<(ostream& flux, const Eleve& eleve);
	string getId() const { return this->m_id; };
	string getPrenom() const { return this->m_prenom; };
	string getNom() const { return this->m_nom; };
	vector<Cours> getPlanning() { return this->m_planning; };
	bool isPlanningEmpty() { return m_planningEmpty; };
	

	void setId(string id) { m_id = id; };
	void setMdp(string mdp) { m_mdp = mdp; };
	void setPrenom(string prenom) { m_prenom = prenom; };
	void setNom(string nom) { m_nom = nom; };
	void setPlanningFromFile();
	void savePlanning();
	void setPlanningEmpty(bool emptyness) { m_planningEmpty = emptyness; };

    int AddCours(Cours newCours);
    bool RmCours(string nomCours);


private:
    string m_id;
    string m_mdp;
    string m_nom;
    string m_prenom;
    vector<Cours> m_planning;
	bool m_planningEmpty;
};