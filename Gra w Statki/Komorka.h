#pragma once
#include "Statek.h"
#include <iostream>

using namespace std;

class Komorka {
private:
	bool czyZestrzelonaKomorka = false;
	shared_ptr<Statek> statek;
public:
	Komorka();
	bool czyZestrzelona();
	void strzal();
	shared_ptr<Statek> getStatek();
	void setStatek(shared_ptr<Statek> statek);
	string wartosc();
	string ukrytaWartosc();
};

