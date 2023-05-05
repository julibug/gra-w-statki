#pragma once
#include "Statek.h"

class Jednomasztowiec : public Statek {
private:
	regex wzorzec(Kierunek kierunek);
public:
	Jednomasztowiec();
	Jednomasztowiec(string poleStartowe);
};

