#include <iostream>
#include "Display.h"
#include <fstream>
#include <sstream>

using namespace std;

int main()
{
	Display d;
	d.loginScreen() ? d.menu() : d.loginScreen();
    return 0;
}

