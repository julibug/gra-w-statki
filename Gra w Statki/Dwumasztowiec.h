#pragma once
#include "Statek.h"

class Dwumasztowiec : public Statek {
private:
	regex wzorzec(Kierunek kierunek);
public:
	Dwumasztowiec();
	Dwumasztowiec(string poleStartowe, Kierunek kierunek);
};

