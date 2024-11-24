#include "App.h"
#include <iostream>
using namespace std;

App::App() : head(nullptr), tail(nullptr), arx(nullptr) {}

App::~App() {
  
    while (head) {
        BuforDanych* next = head->nowszy;
        delete head;
        head = next;
    }
}

void App::clikrun() {
    run = !run;
}

void App::symulacja() {
    double i = 0;
    run = true;

    while (run) {
        std::cout << "Iteracja: " << i << "\n";

        
        BuforDanych* nowaBaza = new BuforDanych(tail);
        nowaBaza->setzaklucenie(arx->generateDisturbance());

        if (!head) {
            head = nowaBaza; //piewrszy element
        }
        tail = nowaBaza; 
        std::cout << "Dodano element o ID: " << tail->ID << ", Zaklucenie: " << tail->zaklucenie << "\n";

        i++;

       
        if (i >= 10) {
            run = false;
        }
    }

    std::cout << "Symulacja zakoñczona.\n";
}

void App::wypiszDane() {
    if (head) {
        head->wypisztabele();
    }
    else {
        std::cout << "Bufor jest pusty!\n";
    }
}