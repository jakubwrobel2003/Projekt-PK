#pragma once
class Sygnal
{
private:
	double A;
	double p;
	int t;
	double i;


	
	double unit(double A);
	double sinusoidal(double A,int i,int t=60);
	double rectangular(double A,double p, int i, int t = 60);
	
public:
	double setA(double data) {
		A = data;
	}
	double setp(double data) {
		p = data;
	}
	double sett(int data) {
		t = data;
	}
	double seti(int data) {
		i = data;
	}
	double generateSignal(int liczba=0);
	Sygnal();
};

