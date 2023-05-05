#pragma once
#include "Kierunek.h"
#include "Pomocnicza.h"
#include <iostream>
#include <vector>
#include <string>
#include <regex>

using namespace std;

class Statek
{
protected:
	vector <string> wspolrzedne;
	virtual regex wzorzec(Kierunek kierunek) = 0;
public:
	Statek();
	vector <string> getWspolrzedne();
};

