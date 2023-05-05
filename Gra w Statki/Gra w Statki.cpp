#include <iostream>
#include <windows.h>
#include <thread>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <ranges>
#include <cstdlib>
#include "Statek.h"
#include "Czteromasztowiec.h"
#include "Trzymasztowiec.h"
#include "Dwumasztowiec.h"
#include "Jednomasztowiec.h"
#include "Komorka.h"
#include "Plansza.h"
#include "Kierunek.h"

using namespace std;

Plansza inicjalizujPlansze() {
    int rozmiarStatku = 4;
    Plansza plansza = Plansza();
    while (rozmiarStatku > 0) {
        try {
            string klucz;
            cout << "Podaj pole startowe:" << endl;
            cin >> klucz;
            Kierunek kierunek;
            string x;
            if (rozmiarStatku > 1) {
                cout << "Podaj kierunek: 0 - dol, 1 - w prawo" << endl;
                cin >> x;
                if (x == "0") {
                    kierunek = Kierunek::DOWN;
                }
                else if (x == "1") {
                    kierunek = Kierunek::RIGHT;
                }
                else {
                    throw invalid_argument("Blad");
                }
                plansza.utworzStatek(rozmiarStatku, klucz, kierunek);
            }
            else {
                plansza.utworzStatek(rozmiarStatku, klucz, Kierunek::DOWN);
            }
            rozmiarStatku--;
        }
        catch (...) {
            cout << "Niepoprawne wspolrzedne, wprowadz poprawne dane" << endl;
        }
    }
    return plansza;
};

static Kierunek randomowyKierunek() {
    int x = (rand() % 2);
    if (x == 0) {
        return Kierunek::DOWN;
    }
    else {
        return Kierunek::RIGHT;
    }
}

static string randomowaKolumna() {
    return Pomocnicza::kolumny[rand() % 10];
}

static string randomowyKlucz() {
    return randomowaKolumna() + to_string((rand() % 10) + 1);
}

Plansza randomowaPlansza() {
    int rozmiarStatku = 4;
    Plansza plansza = Plansza();
    while (rozmiarStatku > 0) {
        try {
            plansza.utworzStatek(rozmiarStatku, randomowyKlucz(), randomowyKierunek());
            rozmiarStatku--;
        }
        catch (...) {

        }
    }
    return plansza;
}

bool czyZawiera(vector <string> strzaly, string klucz) {
    for (int i = 0; i < strzaly.size(); i++) {
        if (strzaly[i] == klucz) {
            return true;
        }
    }
    return false;
};

void timer(bool& x, int& y) {
    while (x == true) {
        Sleep(1000);
        y++;
    }
    cout << "Czas rozgrywki: " << y << " sekund" << endl;
};

void stop(thread& t, bool& x) {
    x = false;
    t.join();
};

int main()
{
    srand(time(NULL));
    cout << "GRA W STATKI" << endl << endl;
    Plansza planszaGracza = inicjalizujPlansze();
    cout << endl;
    cout << "PLANSZA GRACZA:" << endl << endl;
    planszaGracza.wypisz();
    cout << endl;
    Plansza planszaPrzeciwnika = randomowaPlansza();
    cout << endl;
    cout << "PLANSZA PRZECIWNIKA:" << endl << endl;
    planszaPrzeciwnika.wypiszDlaPrzeciwnika();
    cout << endl;
    vector <string> strzalyPrzeciwnika;
    vector <string> strzalyGracza;
    bool kolejGracza = true;
    bool x = true;
    int i = 0;
    thread licznik(timer, ref(x), ref(i));
    while (!(planszaGracza.czyWszystkieZatopione() || planszaPrzeciwnika.czyWszystkieZatopione())) {
        if (kolejGracza) {
            while (kolejGracza != false) {
                try {
                    cout << endl;
                    cout << "Twoja kolej" << endl;
                    string klucz;
                    cin >> klucz;
                    if (czyZawiera(strzalyGracza, klucz)) {
                        throw invalid_argument("Blad");
                    }
                    strzalyGracza.push_back(klucz);
                    string odp = planszaPrzeciwnika.strzal(klucz);
                    cout << endl;
                    cout << "PLANSZA PRZECIWNIKA:" << endl << endl;
                    planszaPrzeciwnika.wypiszDlaPrzeciwnika();
                    cout << endl;
                    cout << odp;
                    cout << endl;
                    if (odp == "Pudlo") {
                        kolejGracza = false;
                    }
                    if (planszaPrzeciwnika.czyWszystkieZatopione()) {
                        break;
                    }
                }
                catch (...) {
                    cout << endl;
                    cout << "Wspolrzedne sa niepoprawne lub zostaly juz wprowadzone, podaj poprawne dane" << endl << endl;
                }
            }
        }
        else {
            while (kolejGracza == false) {
                cout << endl;
                cout << "Kolej przeciwnika" << endl;
                Sleep(2000);
                string klucz;
                do {
                    klucz = randomowyKlucz();
                } while (czyZawiera(strzalyPrzeciwnika, klucz));
                strzalyPrzeciwnika.push_back(klucz);
                cout << endl;
                cout << "Przeciwnik strzelil w pole " + klucz << endl << endl;
                string odp = planszaGracza.strzal(klucz);
                cout << "PLANSZA GRACZA:" << endl << endl;
                planszaGracza.wypisz();
                cout << endl;
                cout << odp;
                cout << endl;
                if (odp == "Pudlo") {
                    kolejGracza = true;
                }
                if (planszaGracza.czyWszystkieZatopione()) {
                    break;
                }
            }
        }
    }
    string nazwaPliku = "Wyniki";
    nazwaPliku = nazwaPliku + ".txt";
    filesystem::path nazwa{ "Wyniki Gry w Statki" };
    filesystem::create_directories(nazwa);
    nazwa.append(nazwaPliku);
    if (planszaGracza.czyWszystkieZatopione()) {
        cout << endl;
        cout << "Przegrana :((" << endl << endl;
        stop(licznik, x);
        fstream plikwe;
        plikwe.open(nazwa, ios::app);
        plikwe << "Przegrana gracza" << endl;
        plikwe.close();
    }
    else {
        cout << endl;
        cout << "Zwyciestwo! :DD" << endl << endl;
        stop(licznik, x);
        fstream plikwe;
        plikwe.open(nazwa, ios::app);
        plikwe << "Wygrana gracza" << endl;
        plikwe.close();
    }
    cout << endl << endl;
    cout << "Wyniki ostatnich rozgrywek:" << endl << endl;
    vector<string> w;
    string record;
    ifstream sstream(nazwa);
    if (sstream.is_open()) {
        while (getline(sstream, record)) {
            w.insert(w.begin(), record);
        }
        for (auto i : w | ranges::views::take(3)) {
            cout << i << endl;
        }
    }
}

