#pragma once
#include <iostream>
using namespace std;

class BuforDanych {
public:
    BuforDanych* nowszy = nullptr; // Wsk nowszy element kolejki
    BuforDanych* starszy = nullptr; // Wsk starszy element kolejki
    double zaklucenie;
    int ID; // Unikalny identyfikator
    static int licznikInstancji; //licznik ile jest danych

    
    BuforDanych(BuforDanych* poprzedni);//konstruktor jak tworzy sie pierwszy to nullptr
    //setery
    void setzaklucenie(double data);
    void wypisztabele(); //wypisuje na ekran pojedyncza tablice
};
