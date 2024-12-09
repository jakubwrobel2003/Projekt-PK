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
using namespace std;
class ARX;

class App {
private:
    bool run = false; // start stop
    std::vector<BuforDanych*> data;
    ARX* arx; //wsk na arx
public:
    void clikrun(); //start stop
    void symulacja(); //g³ówna fukcja programu
    void wypiszDane(); //wykonuje wypisz na wstkich obiektach bufordanyh po kolei od 1 do n na ekran piersza wersja
    void setARX(ARX* A) { this->arx = A; }
    void zapisBazydanychdopliku();
    App();
    ~App();

    void odczytajDaneZPliku() {
        const std::string nazwaPliku = "example.txt"; // Plik na sztywno
        std::ifstream file(nazwaPliku); // Otwieramy plik
        if (!file.is_open()) {
            std::cerr << "Nie mo¿na otworzyæ pliku: " << nazwaPliku << std::endl;
            return;
        }

        std::string linia;
        //// Pomijamy nag³ówek (pierwsza linia pliku)
        //if (!std::getline(file, linia)) {
        //    std::cerr << "Plik jest pusty lub brak nag³ówka!" << std::endl;
        //    return;
        //}

        // Przetwarzanie kolejnych wierszy danych
        while (std::getline(file, linia)) {
            std::istringstream iss(linia);

            int id;
            double zaklucenie;
            std::string str1, str2;
            double val1, val2;

            // Odczyt wartoœci w formacie int, double, string, string, double, double
            if (iss >> id >> zaklucenie >> str1 >> str2 >> val1 >> val2) {
                // Tworzenie obiektu BuforDanych
                BuforDanych* bufor = new BuforDanych();
                bufor->setID(id);               // Ustaw ID
                bufor->setZaklucenie(zaklucenie); // Ustaw zak³ócenie
                bufor->setB(str1);             // Ustaw pierwszy string
                cout << str1 << "sss\n";
                bufor->setA(str2);             // Ustaw drugi string
                bufor->setU(val2);              // Ustaw pierwsz¹ wartoœæ double
                bufor->setY(val1);              // Ustaw drug¹ wartoœæ double

                // Dodanie obiektu do wektora
                data.push_back(bufor);
                std::cout << "Dodano dane do BuforDanych: ID = " << id << std::endl;
            }
            else {
                std::cerr << "B³¹d odczytu wiersza danych: " << linia << std::endl;
            }
        }

        file.close();
    }
};