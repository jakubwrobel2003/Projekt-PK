#pragma once
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class BuforDanych {
private:
   
public:
    double zaklucenie;
    int ID; 
    static int licznikInstancji; //licznik ile jest danych

    
    BuforDanych();//konstruktor jak tworzy sie pierwszy to nullptr
    //setery
    void setZaklucenie(double data);
    void setID(int id);

    //Getter
    double getZaklucenie() const;
    int getID() const;

    void wypisztabele(); //wypisuje na ekran pojedyncza tablice
    
};
