#include "Czteromasztowiec.h"

Czteromasztowiec::Czteromasztowiec() {};

Czteromasztowiec::Czteromasztowiec(string poleStartowe, Kierunek kierunek) {
	smatch matches;
	if (regex_match(poleStartowe, matches, wzorzec(kierunek))) {
		string kolumna = matches[1].str();
		int rzad = stoi(matches[2].str());
		for (int i = 0; i < 4; i++) {
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
		throw invalid_argument("blad w Czteromasztowcu");
	}
};

regex Czteromasztowiec::wzorzec(Kierunek kierunek) {
	regex wzorzecDOWN("^([A-J])([1-7])$");
	regex wzorzecRIGHT("^([A-G])([1-9]|10)$");
	switch (kierunek) {
	case Kierunek::DOWN:
		return wzorzecDOWN;
	case Kierunek::RIGHT:
		return wzorzecRIGHT;
	}
};