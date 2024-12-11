#pragma once
class Sygnal
{
private:
	double amplitude;
	double p;
	int ActivationTime;
	double Period;


	
	double unit(double A);
	double sinusoidal(double A,int i,int t=60);
	double rectangular(double A,double p, int t, int i);
public:
	double generateSignal();
	Sygnal();
};

