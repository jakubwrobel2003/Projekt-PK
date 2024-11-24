#include "BuforDanych.h"

int BuforDanych::licznikInstancji = 0;

BuforDanych::BuforDanych(BuforDanych* poprzedni) : ID(++licznikInstancji), zaklucenie(0) {
    if (poprzedni) {
        this->starszy = poprzedni;
        poprzedni->nowszy = this;
    }
}

void BuforDanych::setzaklucenie(double data) {
    zaklucenie = data;
}

void BuforDanych::wypisztabele() {
    std::cout << "ID | Zaklucenie\n";
    BuforDanych* curr = this; 
    while (curr != nullptr) {
        std::cout << curr->ID << " | " << curr->zaklucenie << "\n";
        curr = curr->nowszy; 
    }
}
