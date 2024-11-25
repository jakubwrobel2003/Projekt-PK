#include "BuforDanych.h"
#include "Sygnal.h"
#include "App.h"
#include "Sprzezenie.h"
#include "PID.h"
#include "Sumator.h"
#include "RegulatorARX.h"
#include <iostream>

int main() {
    App aplikacja;
    RegulatorARX arx;

    aplikacja.setARX(&arx);

    //gluwna petla
    aplikacja.symulacja();

    // wupisz w przyszlosci zaspis do pliku
    aplikacja.wypiszDane();
    aplikacja.zapisBazydanychdopliku();
    return 0;
}