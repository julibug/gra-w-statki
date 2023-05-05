#include "Plansza.h"

Plansza::Plansza() {
	for (string kolumna : Pomocnicza::kolumny) {
		for (int i = 1; i <= 10; i++) {
			pola.emplace(kolumna + to_string(i), new Komorka());
		}
	}
};

void Plansza::utworzStatek(int rozmiar, string poleStartowe, Kierunek kierunek) {
	vector <shared_ptr <Statek>> statek;
	switch (rozmiar) {
	case 4:
		statek.emplace_back(new Czteromasztowiec(poleStartowe, kierunek));
		przygotujKomorki(statek.back());
		break;
	case 3:
		statek.emplace_back(new Trzymasztowiec(poleStartowe, kierunek));
		przygotujKomorki(statek.back());
		break;
	case 2:
		statek.emplace_back(new Dwumasztowiec(poleStartowe, kierunek));
		przygotujKomorki(statek.back());
		break;
	case 1:
		statek.emplace_back(new Jednomasztowiec(poleStartowe));
		przygotujKomorki(statek.back());
		break;
	default:
		throw invalid_argument("Blad");
		break;
	};
	for (vector <shared_ptr <Statek>>::iterator it = statek.begin(); it != statek.end(); ++it) {
		statki.emplace_back(move(*it));
	}
};

string Plansza::strzal(string klucz) {
	smatch matches;
	if (regex_match(klucz, matches, wzorzec())) {
		shared_ptr<Komorka> k = pola.at(klucz);
		k->strzal();
		shared_ptr<Statek> s = k->getStatek();
		if (s == nullptr) {
			return "Pudlo";
		}
		else if (czyZatopiony(s)) {
			return "Trafiony zatopiony";
		}
		else {
			return "Trafiony";
		}
	}
	else {
		throw invalid_argument("blad");
	}
};

bool Plansza::czyWszystkieZatopione() {
	bool zatopione = true;
	for (int i = 0; i < statki.size(); i++) {
		zatopione = zatopione && czyZatopiony(statki[i]);
	}
	return zatopione;
};

void Plansza::wypisz() {
	wypisz(false);
};

void Plansza::wypiszDlaPrzeciwnika() {
	wypisz(true);
};

void Plansza::wypisz(bool ukryta) {
	cout << "   A B C D E F G H I J" << endl;
	for (int i = 1; i <= 10; i++) {
		cout << i << "  ";
		for (string kolumna : Pomocnicza::kolumny) {
			shared_ptr<Komorka> komorka = pola[kolumna + to_string(i)];
			if (ukryta) {
				cout << komorka->ukrytaWartosc();
			}
			else {
				cout << komorka->wartosc();
			}
		}
		cout << endl;
	}
}

bool Plansza::czyZatopiony(shared_ptr<Statek> statek) {
	bool czyZatopionyStatek = true;
	for (string klucz : statek->getWspolrzedne()) {
		shared_ptr<Komorka> k = this->pola.at(klucz);
		czyZatopionyStatek = czyZatopionyStatek && k->czyZestrzelona();
	}
	return czyZatopionyStatek;
}

void Plansza::przygotujKomorki(shared_ptr<Statek> statek) {

	for (string klucz : statek->getWspolrzedne()) {
		sprawdzKomorke(statek, klucz);
	}
	for (string klucz : statek->getWspolrzedne()) {
		shared_ptr<Komorka> komorka = pola[klucz];
		komorka->setStatek(statek);
	}
}

void Plansza::sprawdzKomorke(shared_ptr<Statek> statek, string klucz) {
	shared_ptr<Komorka> komorka = pola[klucz];
	if (komorka->getStatek() != NULL) {
		throw invalid_argument("blad");
	}
};

regex Plansza::wzorzec() {
	regex wzorzecREGEX("^([A-J])([1-9]|10)$");
	return wzorzecREGEX;
};