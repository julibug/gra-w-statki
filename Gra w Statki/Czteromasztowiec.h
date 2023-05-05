#pragma once
#include "Statek.h"

class Czteromasztowiec : public Statek {
private:
	regex wzorzec(Kierunek kierunek);
public:
	Czteromasztowiec();
	Czteromasztowiec(string poleStartowe, Kierunek kierunek);
};

