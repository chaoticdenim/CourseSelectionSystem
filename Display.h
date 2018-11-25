#pragma once
#include <sstream>
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>
using namespace std;

class Display
{
public:
	bool loginScreen();
	void menu();
	void planningScreen();
	void clearScreen();
private:
	string login;
	vector<int> courseVector = { 0, 0, 0, 0, 0, 0, 0 };
};

