#pragma once
#include "BuforDanych.h"
#include "RegulatorARX.h"
#include <fstream>
#include <vector>
class RegulatorARX;
class App {
private:
    bool run = false; // start stop
    std::vector<BuforDanych*> data;
    RegulatorARX* arx; //wsk na arx
public:
    void clikrun(); //start stop
    void symulacja(); //g³ówna fukcja programu
    void wypiszDane(); //wykonuje wypisz na wstkich obiektach bufordanyh po kolei od 1 do n na ekran piersza wersja
    void setARX(RegulatorARX* A) { this->arx = A; }
    void zapisBazydanychdopliku();
    App();
    ~App();
};
