#pragma once
#include <random>
#include "App.h"
#include "BuforDanych.h"
using namespace std;
class RegulatorARX {
public:
    double generateDisturbance();
    //double policz(std::vector<BuforDanych*> data);
    double calaA(std::vector<BuforDanych*> data);
    double calcb(std::vector<BuforDanych*> data);

    // gen zaklucen 0.0 do 1.0
};
//