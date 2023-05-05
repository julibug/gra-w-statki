#pragma once
#include "Statek.h"

class Trzymasztowiec : public Statek {
	regex wzorzec(Kierunek kierunek);
public:
	Trzymasztowiec();
	Trzymasztowiec(string poleStartowe, Kierunek kierunek);
};

