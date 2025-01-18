#pragma once
#include "ARX.h"
#include <fstream>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "BuforDanych.h"
#include "Sygnal.h"
#include "PID.h"
using namespace std;
class ARX;

class App {
private:
    bool run = false; // start stop
    ARX* arx;// Relacja zale�no�ci
    PID* Pid;
public:
    Sygnal* syg;//Relacja zale�no�ci

    std::vector<BuforDanych*> data;//Relacja agregacji
    double oldY = 0;
    std::string a;
    std::string b;
    double u;
    double p;
    double t;
    double i;
    double amplituda;
    int sygnal=0;

    void clikrun(); //start stop
    void symulacja(); //g��wna fukcja programu
    //
    void symulacjaStep();
    //
    void wypiszDane(); //wykonuje wypisz na wstkich obiektach bufordanyh po kolei od 1 do n na ekran piersza wersja
    void setARX(ARX* A) { this->arx = A; }
    void setSyg(Sygnal* S) { this->syg = S; }
    void setPID(PID* p) { this->Pid = p; }
    double arxsym();
    void zapisBazydanychdopliku();
    App();
    ~App();
    void odczytajDaneZPliku() {
        const std::string nazwaPliku = "example.txt"; // Plik na sztywno
        std::ifstream file(nazwaPliku); // Otwieramy plik
        if (!file.is_open()) {
            std::cerr << "Nie mo�na otworzy� pliku: " << nazwaPliku << std::endl;
            return;
        }

        std::string linia;
       

        // Przetwarzanie kolejnych wierszy danych
        while (std::getline(file, linia)) {
            std::istringstream iss(linia);//obiekt strumienia wej�ciowego

            int id;
            double zaklucenie;
            std::string str1, str2;
            double val1, val2;

            // Odczyt warto�ci w formacie int, double, string, string, double, double
            if (iss >> id >> zaklucenie >> str1 >> str2 >> val1 >> val2) {
                // Tworzenie obiektu BuforDanych
                BuforDanych* bufor = new BuforDanych();
                bufor->setID(id);               // Ustaw ID
                bufor->setZaklucenie(zaklucenie); // Ustaw zak��cenie
                bufor->setB(str1);             // Ustaw B
              
                bufor->setA(str2);             // Ustaw A
                bufor->setU(val2);              // Ustaw Y
                bufor->setY(val1);              // Ustaw U

                // Dodanie obiektu do wektora
                data.push_back(bufor);
               //S std::cout << "Dodano dane do BuforDanych: ID = " << id << std::endl;
            }
            else {
                std::cerr << "B��d odczytu wiersza danych: " << linia << std::endl;
            }
        }

        file.close();
    }
};