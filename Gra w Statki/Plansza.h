#pragma once
#include <vector>
#include <string>
#include <map>
#include <regex>
#include "Komorka.h"
#include "Statek.h"
#include "Jednomasztowiec.h"
#include "Dwumasztowiec.h"
#include "Trzymasztowiec.h"
#include "Czteromasztowiec.h"

using namespace std;

class Plansza {
private:
	map <string, shared_ptr<Komorka>> pola;
	vector <shared_ptr <Statek>> statki;
	void wypisz(bool ukryta);
	bool czyZatopiony(shared_ptr<Statek> statek);
	void przygotujKomorki(shared_ptr<Statek> statek);
	void sprawdzKomorke(shared_ptr<Statek> statek, string klucz);
	regex wzorzec();
public:
	Plansza();
	void utworzStatek(int rozmiar, string poleStartowe, Kierunek kierunek);
	string strzal(string klucz);
	bool czyWszystkieZatopione();
	void wypisz();
	void wypiszDlaPrzeciwnika();
};

