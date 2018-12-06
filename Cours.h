#include <iostream>
#include<string>

using namespace std;

#pragma once

class Cours{
public:
    Cours(){ m_nomCours = "NULL"; m_prof = "NULL"; m_location = "NULL";};;
    Cours(string nomCours, string prof, string loc) { m_nomCours=nomCours; m_prof=prof; m_location=loc;}

    string getNomCours() const {return this->m_nomCours;}
    string getLocation() const {return this->m_location;}
    string getProf() const {return this->m_prof;}


    void setNomCours(string nomCours) {m_nomCours=nomCours;}
    void setProf(string prof) {m_prof=prof;}
    void setLocation(string location) {m_location=location;}

private:
    string m_nomCours;
    string m_prof;
    string m_location;
};