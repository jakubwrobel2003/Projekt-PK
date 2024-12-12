#include "BuforDanych.h"
#include "Sygnal.h"
#include "App.h"
#include "Sprzezenie.h"
#include "PID.h"
#include "ARX.h"
#include <iostream>

int main() {
    App aplikacja;
    ARX arx;
    Sygnal syg;
    PID pid(1, 0.05, 0.01 );
    aplikacja.setSyg(&syg);
    aplikacja.setARX(&arx);
    aplikacja.setPID(&pid);
    //gluwna petla
    aplikacja.symulacja();

    // wupisz w przyszlosci zaspis do pliku
    aplikacja.wypiszDane();
 
    aplikacja.zapisBazydanychdopliku();

    
}