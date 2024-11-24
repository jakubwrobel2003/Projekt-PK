#pragma once
class Sygnal
{
private:
	double amplitude;
	double p;
	int ActivationTime;
	double Period;


	Sygnal();
	double unit();
	double sinusoidal();
	double rectangular();
public:
	double generateSignal();
};

