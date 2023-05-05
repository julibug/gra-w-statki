#include "Jednomasztowiec.h"

Jednomasztowiec::Jednomasztowiec() {};

Jednomasztowiec::Jednomasztowiec(string poleStartowe) {
	smatch matches;
	if (regex_match(poleStartowe, matches, wzorzec(Kierunek::DOWN))) {
		this->wspolrzedne.push_back(poleStartowe);
	}
	else {
		throw invalid_argument("blad w Jednomasztowcu");
	}
};

regex Jednomasztowiec::wzorzec(Kierunek kierunek) {
	regex wzorzecREGEX("^([A-J])([1-9]|10)$");
	return wzorzecREGEX;
};