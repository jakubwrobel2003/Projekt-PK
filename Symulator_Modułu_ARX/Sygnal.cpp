#include "Sygnal.h"
#include <math.h>
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
	if (liczba == 0) {
		unit(A);

	}
	if (liczba==1) {
		sinusoidal(A, i, t);
	}
	else {
		rectangular(A, p, t, i);
	}
	// generowanie sygnalu
	return 0;
}