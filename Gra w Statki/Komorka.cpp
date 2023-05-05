#include "Komorka.h"

Komorka::Komorka() {
	this->statek = nullptr;
};

bool Komorka::czyZestrzelona() {
	return czyZestrzelonaKomorka;
};

void Komorka::strzal() {
	this->czyZestrzelonaKomorka = true;
};

shared_ptr<Statek> Komorka::getStatek() {
	return statek;
};

void Komorka::setStatek(shared_ptr<Statek> s) {
	statek = s;
}

string Komorka::wartosc() {
	if (czyZestrzelonaKomorka) {
		return statek == NULL ? "o " : "# ";
	}
	return statek == NULL ? "~ " : "@ ";
}

string Komorka::ukrytaWartosc() {
	if (czyZestrzelonaKomorka) {
		return statek == NULL ? "o " : "# ";
	}
	return "~ ";
}