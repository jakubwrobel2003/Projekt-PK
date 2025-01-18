#include "ARX.h"
#include "App.h"
#include "BuforDanych.h"
using namespace std;

double ARX::generateDisturbance() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-0.01, 0.01);
    return dis(gen);
}

double ARX::calcb(std::vector<BuforDanych*> data) {
    if (data.empty()) {
        throw std::invalid_argument("Dane s¹ puste! Nie mo¿na wykonaæ obliczeñ.");
    }

    double sum = 0.0;
    int n_b = data.back()->getvectorB().size(); // Liczba wspó³czynników b
    int k = data.back()->k; // OpóŸnienie wejœcia

    for (int i = 0; i < n_b; ++i) {
        int idx = data.size() - i - k-1;
        if (idx >= 0 && idx < data.size()) { // Upewnij siê, ¿e indeks jest w granicach
            sum += data[idx]->getU() * data.back()->getb(i);
           // std::cout << "Bcalc " << data[idx]->getU() << " U " << data.back()->getb(i) << " A " << sum << " sum\n";
        }
    }

    return sum;
}

double ARX::calaA(std::vector<BuforDanych*> data) {
    if (data.empty()) {
        throw std::invalid_argument("Dane s¹ puste! Nie mo¿na wykonaæ obliczeñ.");
    }

    double sum = 0.0;
    //int n_a = data.back()->getvectorA().size(); // Liczba wspó³czynników a
    //std::cout << "\nVERA " << n_a << "\n";

    //for (int j = 0; j < n_a; ++j) {
    //    int idx = data.size() - 1 - j; // Indeks danych wyjœciowych
    //    if (idx >= 0 && idx < data.size()) { // Sprawdzenie poprawnoœci indeksu
    //        sum += data[idx]->getY() * data.back()->getA(j);
    //        std::cout << "Acalc idx: " << idx << " Y: " << data[idx]->getY() << " A: " << data.back()->getA(j) << " Sum: " << sum << "\n";
    //    }
    //    else {
    //        std::cout << "Pominiêto iteracjê: j = " << j << ", idx = " << idx << "\n";
    //    }
    //}
    int n_b = data.back()->getvectorA().size(); // Liczba wspó³czynników b
    int k = data.back()->k; // OpóŸnienie wejœcia

    for (int i = 0; i < n_b; ++i) {
        int idx = data.size() - i  - 1;
        
        if (idx -i>= 0 && idx < data.size()) { // Upewnij siê, ¿e indeks jest w granicach
            sum += data[idx - i]->getY()* data.back()->getA(i);
           // std::cout << "Acalc " << data[idx-i]->getY() << " Y " << data.back()->getA(i) << " A " << sum << " sum\n";
        }
        else {
            sum += 0.0;
        }
    }
    return sum;
}

double ARX::calcAll(std::vector<BuforDanych*> data) {
    if (data.size() == 0) {
        return 0;
   }
	//cout << "\na-b" << calcb(data) - calaA(data) + data.back()->getZaklucenie() << "pp\n";
    return calcb(data) - calaA(data) + data.back()->getZaklucenie();
}
