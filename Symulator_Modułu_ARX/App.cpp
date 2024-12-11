#include "App.h"
#include <iostream>
using namespace std;

App::App()
    : run(false),
    data(0),
    arx(nullptr) {};

App::~App() {
 
}

void App::clikrun() {
    run = !run;
}

void App::symulacja() {
    double i = 0;
    run = true;
    int max = 20;
    bool oddczytaj = true;
    while (run) {
   //     std::cout << "Iteracja: " << i << "\n";

       
        
        if (oddczytaj) {
             // Czyszczenie wektora przed wczytaniem danych
            odczytajDaneZPliku();
            i = data.size();
            max+= data.size();
            oddczytaj = false;
            wypiszDane();
           
        }
        else {
            BuforDanych* nowaBaza = new BuforDanych();
            const std::string input = "2.34;2.60;3.14;5.0";
            nowaBaza->setB(input);
            nowaBaza->setA(input);

            nowaBaza->setZaklucenie(arx->generateDisturbance());

            data.push_back(nowaBaza);
            if (i <= 20) {
                nowaBaza->setU(0.5);
            }if (i > 20) {

            nowaBaza->setU(1.0);
            }
            double wynikCalcAll = arx->calcAll(data);
            nowaBaza->setY(wynikCalcAll);
         //   cout << wynikCalcAll << " ddd\n";
        }
        

        i++;

        if (i >= max) {
            run = false;
        }
    }

    std::cout << "Symulacja zakoñczona.\n";
}

void App::wypiszDane() {
    std::cout << "Rozmiar danych: " << data.size() << "\n";
    std::cout << "ID\tZaklucenie\tB\tA\tY\tU\n";
    std::cout << "------------------------\n";

    for (const auto& elem : data) {
        if (elem) {
            elem->wypisztabele();
        }
        else {
            std::cout << "B³¹d: pusty wskaŸnik w danych.\n";
        }
    }
}

void App::zapisBazydanychdopliku() {
    ofstream file("example.txt", std::ios::out | std::ios::trunc);
    if (file.is_open()) {
        for (const auto& elem : data) {
           // cout << elem->getID() << "\n";
            if (elem) {
                file << elem->getID() << "\t" << elem->getZaklucenie() << "\t";
                //file << elem->getb(0) << elem->getb(1);
                for (const auto data : elem->getvectorB()) {
                    file << data << ";";
                }
                file << "\t";
                for (const auto data : elem->getvectorA()) {
                    file << data << ";";
                }
                file << "\t";
                file << elem->getY() << "\t" << elem->getU() << "\n";
            }
            else {
                std::cout << "B³¹d: pusty wskaŸnik w danych.\n";
            }
        }
    }
    file.close();
}
