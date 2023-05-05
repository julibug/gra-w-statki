#include "Dwumasztowiec.h"

Dwumasztowiec::Dwumasztowiec() {};

Dwumasztowiec::Dwumasztowiec(string poleStartowe, Kierunek kierunek) {
	smatch matches;
	if (regex_match(poleStartowe, matches, wzorzec(kierunek))) {
		string kolumna = matches[1].str();
		int rzad = stoi(matches[2].str());
		for (int i = 0; i < 2; i++) {
			if (kierunek == Kierunek::DOWN) {
				string klucz = kolumna + to_string(rzad + i);
				this->wspolrzedne.push_back(klucz);
			}
			else {
				int index = Pomocnicza::indexOf(kolumna) + i;
				string klucz = Pomocnicza::kolumny[index] + to_string(rzad);
				this->wspolrzedne.push_back(klucz);
			}
		}
	}
	else {
		throw invalid_argument("blad w Dwumasztowcu");
	}
};

regex Dwumasztowiec::wzorzec(Kierunek kierunek) {
	regex wzorzecDOWN("^([A-J])([1-9])$");
	regex wzorzecRIGHT("^([A-I])([1-9]|10)$");
	switch (kierunek) {
	case Kierunek::DOWN:
		return wzorzecDOWN;
	case Kierunek::RIGHT:
		return wzorzecRIGHT;
	}
};