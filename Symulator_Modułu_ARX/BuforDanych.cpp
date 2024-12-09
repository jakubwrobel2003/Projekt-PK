#include "BuforDanych.h"
#include <cstring>
#include <string>
using namespace std;
int BuforDanych::licznikInstancji = 0;

BuforDanych::BuforDanych() : ID(++licznikInstancji), zaklucenie(0) {
    
}



void BuforDanych::wypisztabele() {
    // Wyœwietlenie ID i Zaklucenie
    std::cout << this->getID() << " | " << this->getZaklucenie();

    //formacie liczba;liczba;...
    std::cout << " ";
    for (size_t i = 0; i < b.size(); ++i) {
        std::cout << b[i];
        if (i < b.size() - 1) {
            std::cout << ";"; 
        }
    }
    std::cout << "|";
    for (size_t i = 0; i < a.size(); ++i) {
        std::cout << a[i];
        if (i < b.size() - 1) {
            std::cout << ";";
        }
    }
    std::cout << " | " << this->getY() << " | " << this->getU();
    std::cout << "\n";
}
// Setery
void BuforDanych::setZaklucenie(double data) {
    zaklucenie = data;
}

void BuforDanych::setID(int id) {
    ID = id;
}
void BuforDanych::setB(const string& data1) {
    if (data1.empty()) { 
        return;
    }

    string data(data1);

    size_t pos = 0;
    while ((pos = data.find(";")) != string::npos) { 
        string token = data.substr(0, pos); 
        try {
            b.push_back(std::stod(token)); 
        }
        catch (const std::invalid_argument&) {
            cerr << "Invalid input: " << token << std::endl;
        }
        data.erase(0, pos + 1); 
    }

   
    try {
        if (!data.empty()) {
            b.push_back(std::stod(data));
        }
    }
    catch (const std::invalid_argument&) {
      cerr << "Invalid input: " << data << std::endl;
    }
}
void BuforDanych::setA(const string& data1) {
    if (data1.empty()) {
        return;
    }

    string data(data1);

    size_t pos = 0;
    while ((pos = data.find(";")) != string::npos) {
        string token = data.substr(0, pos);
        try {
            a.push_back(std::stod(token));
        }
        catch (const std::invalid_argument&) {
            cerr << "Invalid input: " << token << std::endl;
        }
        data.erase(0, pos + 1);
    }


    try {
        if (!data.empty()) {
            a.push_back(std::stod(data));
        }
    }
    catch (const std::invalid_argument&) {
        cerr << "Invalid input: " << data << std::endl;
    }
}

void BuforDanych::setSter(double data){
    ster = data;
}
// Getery
double BuforDanych::getZaklucenie() const {
    return zaklucenie;
}

int BuforDanych::getID() const {
    return ID;
}
int BuforDanych::getI()const {
    return i;
}
double BuforDanych::getA(int e) {
    if (e < 0 || e >= a.size()) {
        throw std::out_of_range("Indeks poza zakresem wektora a");
    }
    return a[e];
}

double BuforDanych::getb(int e) {
    if (e < 0 || e >= b.size()) {
        throw std::out_of_range("Indeks poza zakresem wektora b");
    }
    return b[e];
}

double BuforDanych::getY() {
    return y;
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