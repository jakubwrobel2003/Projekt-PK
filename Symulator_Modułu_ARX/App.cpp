#include "App.h"
#include <iostream>
using namespace std;

App::App()
    : run(false),
    data(0),
    arx(nullptr) {};

App::~App() {
    this->data.clear();
   
}

void App::clikrun() {
    run = !run;
}

void App::symulacja() {
    double i = 0;
    run = true;

    while (run) {
        std::cout << "Iteracja: " << i << "\n";

        
        BuforDanych* nowaBaza = new BuforDanych();
        
        nowaBaza->setZaklucenie(arx->generateDisturbance());
        
        data.push_back(nowaBaza);

       // std::cout << "Dodano element o ID: " << nowaBaza->getID() << ", Zaklucenie: " << nowaBaza->getZaklucenie() << "\n";

        i++;

       
        if (i >= 10) {
            run = false;
        }
    }

    std::cout << "Symulacja zakoñczona.\n";
}

void App::wypiszDane() {
    std::cout << "Rozmiar danych: " << data.size() << "\n";
    std::cout << "ID\tZaklucenie\n";
    std::cout << "------------------------\n";

    for (const auto& elem : data) {
        if (elem) {
            elem->wypisztabele();
        }
        else {
            std::cout << "B³¹d: pusty wskaŸnik w danych.\n";
        }
    }
} void App::zapisBazydanychdopliku() {
   ofstream file("example.txt", std::ios::out | std::ios::trunc);
   if (file.is_open()) {
    file<< "ID\tZaklucenie\n";
       for (const auto& elem : data) {
           if (elem) {
               file << elem->getID() << "\t"<<elem->getZaklucenie()<<"\n";

           }
           else {
               std::cout << "B³¹d: pusty wskaŸnik w danych.\n";
           }
   }
   } file.close();

}