#include "BuforDanych.h"

int BuforDanych::licznikInstancji = 0;

BuforDanych::BuforDanych() : ID(++licznikInstancji), zaklucenie(0) {
 
}



void BuforDanych::wypisztabele() {
    cout << this->getID() << " | " << this->getZaklucenie() << "\n";
}
// Setery
void BuforDanych::setZaklucenie(double data) {
    zaklucenie = data;
}

void BuforDanych::setID(int id) {
    ID = id;
}

// Getery
double BuforDanych::getZaklucenie() const {
    return zaklucenie;
}

int BuforDanych::getID() const {
    return ID;
}

void czyscplik(string plik) {
    std::ofstream file(plik, std::ios::trunc); //kaswoanie danych
    if (file.is_open()) {
        std::cout << "Plik " << plik << " zosta³ wyczyszczony.\n";
    }
    else {
        std::cerr << "B³¹d: Nie mo¿na otworzyæ pliku " << plik << " do czyszczenia.\n";
    }
    
}