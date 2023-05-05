#include "Pomocnicza.h"

vector <string> const Pomocnicza::kolumny = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J" };

int Pomocnicza::indexOf(string kolumna) {
	for (int i = 0; i < kolumny.size(); i++) {
		if (kolumny[i] == kolumna) {
			return i;
		}
	}
	return -1; //rzuæ b³¹d
}

