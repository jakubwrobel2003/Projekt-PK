#pragma once
#include <vector>
#include "BuforDanych.h"
class PID {
private:
    double wzmocnienieProporcjonalne; // Wzmocnienie proporcjonalne (Kp)
    double wzmocnienieCalkujace;      // Wzmocnienie calkujace (Ki)
    double wzmocnienieRowniczkujace;  // Wzmocnienie ró¿niczkujace (Kd)
    double Ti = 0;
    double odchylenieLiniowe;         // Zamiast ca³ki, linijne odejmowanie lub dodawanie
    bool resetujOdchylenie;           // Flaga resetu odchylenia
    double poprzedniUchyb = 0;
    double poprzednia = 0;      // Flaga resetu calkowania

public:
   
    PID(double kp, double ki, double kd);
    void resetPamieci(); 

    void ustawWzmocnienieProporcjonalne(double wartosc);
    void ustawWzmocnienieCalkujace(double wartosc);
    void ustawWzmocnienieRowniczkujace(double wartosc);

    double oblicz(double uchyb); // Oblicz wyjscie regulatora
    double obliczSprzezenie(double wartoscZadana, double wartoscMierzona);

    // Funkcja sumatora
    double sumator(double wartoscZadana, double wartoscMierzona);
};

