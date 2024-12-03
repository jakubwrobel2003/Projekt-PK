#include "RegulatorARX.h"
#include "App.h"
using namespace std;
double RegulatorARX::generateDisturbance() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    return dis(gen);
}
//double RegulatorARX::policz(vector<BuforDanych*> data) {
//
//}
double RegulatorARX::calaA(vector<BuforDanych*> data) {
    if (data.empty()) {
        throw std::invalid_argument("Dane s¹ puste! Nie mo¿na wykonaæ obliczeñ.");
    }
    double sum = 0;
    int m_i = data.back()->getI();
    int licz = 0;
    for (int i = 0; i <= m_i;i++) {
        if (data.size() < i) {
            sum += 0;
        }
        else {
            sum-=data[data.size() - i]->getY() * data.back()->getA(i);
        }
       
    }
    return sum ;
}

double RegulatorARX::calcb(vector<BuforDanych*> data) {
    if (data.empty()) {
        throw std::invalid_argument("Dane s¹ puste! Nie mo¿na wykonaæ obliczeñ.");
    }
    double sum = 0;
    int m_i = data.back()->getI();
    int licz = 0;
    for (int i = 0; i <= m_i; i++) {
        if (data.size() < i) {
            sum += 0;
        }
        else {
            sum -= data[data.size() - i]->getY() * data.back()->getb(i);
        }

    }
    return sum;
}
double RegulatorARX::calaA(vector<BuforDanych*> data) {
    if (data.empty()) {
        throw std::invalid_argument("Dane s¹ puste! Nie mo¿na wykonaæ obliczeñ.");
    }
    double sum = 0;
    int m_i = data.back()->getI();
    int licz = 0;
    for (int i = 0; i <= m_i; i++) {
        if (data.size() < i) {
            sum += 0;
        }
        else {
        //zamienic mnozenie 
            //   sum -= data[data.size() - i]->getY() * data.back()->getb(i);
        }

    }
    return sum;
}