#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
using namespace std;

class BuforDanych {
private:
    double zaklucenie;
    int ID;
    static int licznikInstancji; //licznik ile jest danych
    vector<double> b;
    vector<double>a;
    double ster;
    double y;
    int i;
public:
    
    BuforDanych();//konstruktor jak tworzy sie pierwszy to nullptr
    //setery
    void setZaklucenie(double data);
    void setID(int id);
    void setB(const std::string& data);
    void setA(const std::string& data);
    void setSter(double data);
    //Getter
    double getZaklucenie() const;
    int getID() const;
    int getI()const;
    double getA(int e);
    double getb(int e);
    double getY();

    void wypisztabele(); //wypisuje na ekran pojedyncza tablice
    
};