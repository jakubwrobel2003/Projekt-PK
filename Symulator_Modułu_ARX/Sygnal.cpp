#include "Sygnal.h"
#include <math.h>
#include <iostream>

Sygnal::Sygnal() {
	//konstruktor
}
double Sygnal::unit(double A) {
	
	return A;
}
double  Sygnal::sinusoidal(double A,int i, int t ) {
	double wynik = A * sin((i % t / t) * 2 * 3.14);
	return wynik;
}
double Sygnal::rectangular(double A, double p, int i, int t) {
	if (i%t >= p*t ) {
		return A;
	}
	return 0;
}
double  Sygnal::generateSignal(int liczba) {
	double g;
	if (liczba == 0) {
		g = unit(A);

	}
	else if (liczba == 1) {
		g = sinusoidal(A, i, t);
	}
	else {
		g = rectangular(A, p, i, t);
	}
	// generowanie sygnalu
	return g;
}