#include "Sygnal.h"
#include <math.h>
Sygnal::Sygnal() {
	//konstruktor
}
double Sygnal::unit(double A) {
	//sygnal jednostkowa
	return A;
}
double  Sygnal::sinusoidal(double A,int i, int t = 60) {
	double wynik = A * sin((i % t / t) * 2 * 3.14);
	return wynik;
}
double Sygnal::rectangular(double A, double p, int t, int i) {
	if (i%t >= p*t ) {
		return A;
	}
	return 0;
}
double  Sygnal::generateSignal() {
	// generowanie sygnalu
	return 0;
}