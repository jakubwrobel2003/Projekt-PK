#include "PID.h"
#include "App.h"
#include "BuforDanych.h"
PID::PID(double kp, double ki, double kd)
    : wzmocnienieProporcjonalne(kp), wzmocnienieCalkujace(ki), wzmocnienieRowniczkujace(kd),
    odchylenieLiniowe(0), poprzedniUchyb(0), resetujOdchylenie(false) {
}

void PID::resetPamieci() {
    odchylenieLiniowe = 0.0;
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
    double PID::oblicz(double uchyb) {
    // cout << "poprzednia" << poprzednia << "wartosc zadana" << wartoscZadana << "uchyb" << uchyb << "\n";
     // Sk³adowa proporcjonalna
    double proporcjonalna = wzmocnienieProporcjonalne * uchyb;
    //cout << "proporcjonalna" << proporcjonalna << "\n";
    double calkujaca = 0;
    // Sk³adowa liniowego odchylenia zamiast ca³ki
    if (wzmocnienieCalkujace != 0) {
        Ti += uchyb;
        calkujaca = (1 / wzmocnienieCalkujace) * Ti;

    }
    //cout << "calkujaca" << calkujaca << "wzmocnienieCalkujace" << wzmocnienieCalkujace << "\n";
    //cout << "Ti" << Ti << "\n";
    // Sk³adowa ró¿niczkuj¹ca
    double rozniczkujaca = wzmocnienieRowniczkujace * (uchyb - poprzedniUchyb);

    // Aktualizacja poprzedniego uchybu
    poprzedniUchyb = uchyb;
    //cout << "uchyb - poprzedniUchyb" << uchyb - poprzedniUchyb << "rozniczkujaca" << rozniczkujaca << "\n";

    return proporcjonalna + calkujaca + rozniczkujaca;
}

double PID::sumator(double wartoscZadana, double wartoscMierzona) {
    // Wylicza uchyb jako rroznice miedzy wartoscia zadana a mierzona
    return wartoscZadana - wartoscMierzona;
}

double PID::obliczSprzezenie(double wartoscZadana, double wartoscMierzona) {
    // Wylicza uchyb za pomoca sumatora
  
    double uchyb = sumator(wartoscZadana, wartoscMierzona);
    cout << uchyb << "uchyb\n";
    // Oblicza sygnaa sterujacy za pomoca PID
    double sygnalSterujacy = this->oblicz(uchyb);

    //// Zaktualizuj model ARX
    //if (!dane.empty()) {
    //    dane.back()->setU(sygnalSterujacy);
    //}

    return sygnalSterujacy;
}