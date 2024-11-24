#pragma once
#include "BuforDanych.h"
#include "RegulatorARX.h"

class App {
private:
    bool run = false; // start stop
    BuforDanych* head = nullptr; // pierwszy elmet
    BuforDanych* tail = nullptr; // ostatni
    RegulatorARX* arx; //wsk na arx

public:
    void clikrun(); //start stop
    void symulacja(); //g³ówna fukcja programu
    void wypiszDane(); //wykonuje wypisz na wstkich obiektach bufordanyh po kolei od 1 do n na ekran piersza wersja
    void setARX(RegulatorARX* Arx) { arx = Arx; }

    App();
    ~App();
};
