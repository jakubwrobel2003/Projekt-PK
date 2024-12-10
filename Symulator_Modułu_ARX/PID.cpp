#include "PID.h"

PID::PID(double kp, double ki, double kd)
    : wzmocnienieProporcjonalne(kp), wzmocnienieCalkujace(ki), wzmocnienieRowniczkujace(kd),
    calka(0), poprzedniUchyb(0), resetujCalke(false) {}

void PID::resetPamieci() {
    calka = 0;
    poprzedniUchyb = 0;
}

void PID::ustawWzmocnienieProporcjonalne(double wartosc) {
    wzmocnienieProporcjonalne = wartosc;
}

void PID::ustawWzmocnienieCalkujace(double wartosc) {
    wzmocnienieCalkujace = wartosc;
}

void PID::ustawWzmocnienieRowniczkujace(double wartosc) {
    wzmocnienieRowniczkujace = wartosc;
}

double PID::oblicz(double wartoscZadana, double wartoscMierzona) {
    double uchyb = wartoscZadana - wartoscMierzona;

    // Skladowa proporcjonalna
    double proporcjonalna = wzmocnienieProporcjonalne * uchyb;

    // Skladowa calkujaca
    if (!resetujCalke) {
        calka += uchyb;
    }
    else {
        resetujCalke = false;
    }
    double calkujaca = wzmocnienieCalkujace * calka;

    // Skladowa rozniczkujaca
    double rozniczkujaca = wzmocnienieRowniczkujace * (uchyb - poprzedniUchyb);

    // Aktualizacja poprzedniego uchybu
    poprzedniUchyb = uchyb;

    return proporcjonalna + calkujaca + rozniczkujaca;
}