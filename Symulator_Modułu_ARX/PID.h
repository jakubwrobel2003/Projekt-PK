#pragma once

class PID {
private:
    double wzmocnienieProporcjonalne; // Wzmocnienie proporcjonalne (Kp)
    double wzmocnienieCalkujace;      // Wzmocnienie calkujace (Ki)
    double wzmocnienieRowniczkujace;  // Wzmocnienie różniczkujace (Kd)

    double calka;            // Suma całkowania
    double poprzedniUchyb;   // Poprzedni uchyb dla rozniczki
    bool resetujCalke;       // Flaga resetu calkowania

public:
    PID(double kp, double ki, double kd);
    void resetPamieci(); // Reset pamieci regulatora

    void ustawWzmocnienieProporcjonalne(double wartosc);
    void ustawWzmocnienieCalkujace(double wartosc);
    void ustawWzmocnienieRowniczkujace(double wartosc);

    double oblicz(double wartoscZadana, double wartoscMierzona); // Oblicz wyjscie regulatora
};

