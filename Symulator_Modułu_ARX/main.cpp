#include "BuforDanych.h"
#include "Sygnal.h"
#include "App.h"
#include "Sprzezenie.h"
#include "PID.h"
#include "ARX.h"
#include <iostream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <stdexcept>
#include <random>
#include <cmath>

using namespace std;

void raportBleduSekwencji(const std::vector<double>& spodz, const std::vector<double>& fakt) {
    constexpr size_t PREC = 3;
    std::cerr << std::fixed << std::setprecision(PREC);
    std::cerr << "  Spodziewany:\t";
    for (auto& el : spodz)
        std::cerr << el << ", ";
    std::cerr << "\n  Faktyczny:\t";
    for (auto& el : fakt)
        std::cerr << el << ", ";
    std::cerr << std::endl << std::endl;
}

bool porownanieSekwencji(const std::vector<double>& spodz, const std::vector<double>& fakt) {
    constexpr double TOL = 1e-3;
    if (fakt.size() != spodz.size()) return false;
    for (size_t i = 0; i < fakt.size(); i++) {
        if (std::fabs(fakt[i] - spodz[i]) >= TOL) {
            return false;
        }
    }
    return true;
}

void test_RegulatorPID_skokJednostkowy()
{
    //Sygnatura testu:
    std::cerr << "RegPID (k = 0.5, TI = 10.0, TD = 0.2) -> test skoku jednostkowego: ";

    try
    {
        // Przygotowanie danych:
        PID instancjaTestowa(0.5, 10.0, 0.2);
        constexpr size_t LICZ_ITER = 30;
        std::vector<double> sygWe(LICZ_ITER);      // pobudzenie modelu 
        std::vector<double> spodzSygWy(LICZ_ITER); // spodziewana sekwencja wy 
        std::vector<double> faktSygWy(LICZ_ITER);  // faktyczna sekwencja wy

        // Symulacja skoku jednostkowego w chwili 1. (!!i - daje 1 dla i != 0);
        for (int i = 0; i < LICZ_ITER; i++)
        {
            sygWe[i] = !!i;
            cout << sygWe[i];
        }
        spodzSygWy = { 0, 0.8, 0.7, 0.8, 0.9, 1, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2, 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9, 3, 3.1, 3.2, 3.3, 3.4 };

        // Symulacja modelu:
        for (int i = 0; i < LICZ_ITER; i++)
            faktSygWy[i] = instancjaTestowa.oblicz(sygWe[i]);

        // Walidacja poprawności i raport:
        if (porownanieSekwencji(spodzSygWy, faktSygWy))
            std::cerr << "OK!\n";
        else
        {
            std::cerr << "FAIL!\n";
            raportBleduSekwencji(spodzSygWy, faktSygWy);
        }
    }
    catch (...)
    {
        std::cerr << "INTERUPTED! (niespodziwany wyjatek)\n";
    }
}
void test_RegulatorP_skokJednostkowy()
{
    //Sygnatura testu:
    std::cerr << "RegP (k = 0.5) -> test skoku jednostkowego: ";

    try
    {
        // Przygotowanie danych:
        PID instancjaTestowa(0.5, 0, 0);
        constexpr size_t LICZ_ITER = 30;
        std::vector<double> sygWe(LICZ_ITER);      // pobudzenie modelu 
        std::vector<double> spodzSygWy(LICZ_ITER); // spodziewana sekwencja wy 
        std::vector<double> faktSygWy(LICZ_ITER);  // faktyczna sekwencja wy

        // Symulacja skoku jednostkowego w chwili 1. (!!i - daje 1 dla i != 0);
        for (int i = 0; i < LICZ_ITER; i++)
            sygWe[i] = !!i;
        spodzSygWy = { 0.0, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5 };

        // Symulacja modelu:
        for (int i = 0; i < LICZ_ITER; i++)
            faktSygWy[i] = instancjaTestowa.oblicz(sygWe[i]);

        // Walidacja poprawności i raport:
        if (porownanieSekwencji(spodzSygWy, faktSygWy))
            std::cerr << "OK!\n";
        else
        {
            std::cerr << "FAIL!\n";
            raportBleduSekwencji(spodzSygWy, faktSygWy);
        }
    }
    catch (...)
    {
        std::cerr << "INTERUPTED! (niespodziwany wyjatek)\n";
    }
}
void test_RegulatorP_brakPobudzenia()
{
    //Sygnatura testu:
    std::cerr << "RegP (k = 0.5) -> test zerowego pobudzenia: ";
    try
    {
        // Przygotowanie danych:
        PID instancjaTestowa(0.5, 0, 0);
        constexpr size_t LICZ_ITER = 30;
        std::vector<double> sygWe(LICZ_ITER);      // pobudzenie modelu (tu same 0)
        std::vector<double> spodzSygWy(LICZ_ITER); // spodziewana sekwencja wy (tu same 0)
        std::vector<double> faktSygWy(LICZ_ITER);  // faktyczna sekwencja wy

        // Symulacja modelu:

        for (int i = 0; i < LICZ_ITER; i++)
            faktSygWy[i] = instancjaTestowa.oblicz(sygWe[i]);

        // Walidacja poprawności i raport:
        if (porownanieSekwencji(spodzSygWy, faktSygWy))
            std::cerr << "OK!\n";
        else
        {
            std::cerr << "FAIL!\n";
            raportBleduSekwencji(spodzSygWy, faktSygWy);
        }
    }
    catch (...)
    {
        std::cerr << "INTERUPTED! (niespodziwany wyjatek)\n";
    }
}



void raportBleduSekwencji(std::vector<double>& spodz, std::vector<double>& fakt)
{
    constexpr size_t PREC = 3;
    std::cerr << std::fixed << std::setprecision(PREC);
    std::cerr << "  Spodziewany:\t";
    for (auto& el : spodz)
        std::cerr << el << ", ";
    std::cerr << "\n  Faktyczny:\t";
    for (auto& el : fakt)
        std::cerr << el << ", ";
    std::cerr << std::endl << std::endl;
}

bool porownanieSekwencji(std::vector<double>& spodz, std::vector<double>& fakt)
{
    constexpr double TOL = 1e-3;	// tolerancja dla porównań zmiennoprzecinkowych
    bool result = fakt.size() == spodz.size();
    for (int i = 0; result && i < fakt.size(); i++)
        result = fabs(fakt[i] - spodz[i]) < TOL;
    return result;
}

void test_ModelARX_brakPobudzenia()
{
    //Sygnatura testu:
    std::cerr << "ModelARX (-0.4 | 0.6 | 1 | 0 ) -> test zerowego pobudzenia: ";
    try
    {
        // Przygotowanie danych:
        App app;
        ARX ARX;
        //app.arx = &ARX;
        app.setARX(&ARX);

        //BuforDanych data({ -0.4 }, { 0.6 }, 0);
        //app.data.push_back(&data);
        constexpr size_t LICZ_ITER = 30;
        std::vector<double> sygWe(LICZ_ITER);      // pobudzenie modelu (tu same 0)
        std::vector<double> spodzSygWy(LICZ_ITER); // spodziewana sekwencja wy (tu same 0)
        std::vector<double> faktSygWy(LICZ_ITER);  // faktyczna sekwencja wy

        // Symulacja modelu:

        for (int i = 0; i < LICZ_ITER; i++) {
            BuforDanych* nowaBaza = new BuforDanych();
            nowaBaza->setB("0.6");
            nowaBaza->setA("-0.4");
            //BuforDanych* newdata = new BuforDanych({ -0.4 }, { 0.6 }, sygWe[i]);
            nowaBaza->setU(sygWe[i]);
            app.data.push_back(nowaBaza);
            //app.data[app.data.size() - 1]->y = faktSygWy[i-1];
            
            faktSygWy[i] = ARX.calcAll(app.data);

        }

        //faktSygWy[i] = instancjaTestowa.symuluj(sygWe[i]);


    // Walidacja poprawności i raport:
        if (porownanieSekwencji(spodzSygWy, faktSygWy))
            std::cerr << "OK!\n";
        else
        {
            std::cerr << "FAIL!\n";
            raportBleduSekwencji(spodzSygWy, faktSygWy);
        }
    }
    catch (...)
    {
        std::cerr << "INTERUPTED! (niespodziwany wyjatek)\n";
    }
}

void test_ModelARX_skokJednostkowy_1()
{
    //Sygnatura testu:
    std::cerr << "ModelARX (-0.4 | 0.6 | 1 | 0 ) -> test skoku jednostkowego nr 1: ";

    try
    {
        App app;
        ARX ARX;
        //app.arx = &ARX;
        app.setARX(&ARX);
        constexpr size_t LICZ_ITER = 30;

        std::vector<double> sygWe(LICZ_ITER);      // pobudzenie modelu 
        std::vector<double> spodzSygWy(LICZ_ITER); // spodziewana sekwencja wy 
        std::vector<double> faktSygWy(LICZ_ITER);  // faktyczna sekwencja wy

        // Symulacja skoku jednostkowego w chwili 1. (!!i - daje 1 dla i != 0);
        for (int i = 0; i < LICZ_ITER; i++)
            sygWe[i] = !!i;
        spodzSygWy = { 0, 0, 0.6, 0.84, 0.936, 0.9744, 0.98976, 0.995904, 0.998362, 0.999345, 0.999738, 0.999895, 0.999958, 0.999983, 0.999993, 0.999997, 0.999999, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

        // Symulacja modelu:
        for (int i = 0; i < LICZ_ITER; i++) {
           
            if (i >= 1) {
                //BuforDanych* newdata = new BuforDanych({ -0.4 }, { 0.6 }, sygWe[i], faktSygWy[i - 1]);
                

                BuforDanych* nowaBaza = new BuforDanych();
                nowaBaza->k = app.data[i - 1]->k;
                nowaBaza->setB("0.6");
                nowaBaza->setA("-0.4");
                nowaBaza->setZaklucenie(0);
                nowaBaza->setU(sygWe[i]);
                //cout << "\n" << app.data.back()->getY()<< "sssffaddddd\n";
                //nowaBaza->setY(faktSygWy[i - 1]);
                nowaBaza->setY(app.oldY);
                app.data.push_back(nowaBaza);
                
               
                faktSygWy[i] = ARX.calcAll(app.data);
                app.data.back()->setY(faktSygWy[i]);
                app.oldY = faktSygWy[i];

                /*cout << "\n" << ARX.calcAll(app.data) << "saddddd\n";
                cout << "\n" << faktSygWy[i] << "saddddd\n";
                cout << "\n" << faktSygWy[i-1] << "saddddd\n";
                cout << "\n" << app.data[i - 1]->getY() << "saddddd\n";*/
               

               
                

            }
            else {
                //BuforDanych* newdata = new BuforDanych({ -0.4 }, { 0.6 }, sygWe[i]);
               
                BuforDanych* nowaBaza = new BuforDanych();
                nowaBaza->k = 1;
                nowaBaza->setB("0.6");
                nowaBaza->setA("-0.4");
                nowaBaza->setZaklucenie(0);
                nowaBaza->setY(app.oldY);
                nowaBaza->setU(sygWe[i]);
                app.data.push_back(nowaBaza);
               

                faktSygWy[i] = app.arxsym();
               // cout << "\n" << app.arxsym() << "asda\n";

                app.data.back()->setY(faktSygWy[i]);
                app.oldY = faktSygWy[i];
            }

            //app.data.back()->y = faktSygWy[i];
           // cout << "KONIEC\n";
        }
        // Walidacja poprawności i raport:
        if (porownanieSekwencji(spodzSygWy, faktSygWy))
            std::cerr << "OK!\n";
        else
        {
            std::cerr << "FAIL!\n";
            raportBleduSekwencji(spodzSygWy, faktSygWy);
        }
    }
    catch (...)
    {
        std::cerr << "INTERUPTED! (niespodziwany wyjatek)\n";
    }
}
void test_ModelARX_skokJednostkowy_2()
{
    //Sygnatura testu:
    std::cerr << "ModelARX (-0.4 | 0.6 | 2 | 0 ) -> test skoku jednostkowego nr 2: ";

    try
    {
        // Przygotowanie danych:
        App app;
        ARX ARX;
        //app.arx = &ARX;
        app.setARX(&ARX);
        //BuforDanych* newdata = new BuforDanych({ -0.4 }, { 0.6 }, sygWe[i], faktSygWy[i - 1]);
        //app.arx = &ARX;
        
        constexpr size_t LICZ_ITER = 30;
        std::vector<double> sygWe(LICZ_ITER);      // pobudzenie modelu, 
        std::vector<double> spodzSygWy(LICZ_ITER); // spodziewana sekwencja wy
        std::vector<double> faktSygWy(LICZ_ITER);  // faktyczna sekwencja wy

        // Symulacja skoku jednostkowego w chwili 1. (!!i - daje 1 dla i != 0);
        for (int i = 0; i < LICZ_ITER; i++)
            sygWe[i] = !!i;
        spodzSygWy = { 0, 0, 0, 0.6, 0.84, 0.936, 0.9744, 0.98976, 0.995904, 0.998362, 0.999345, 0.999738, 0.999895, 0.999958, 0.999983, 0.999993, 0.999997, 0.999999, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

        // Symulacja modelu:
       

            for (int i = 0; i < LICZ_ITER; i++) {

                if (i >= 1) {
                    //BuforDanych* newdata = new BuforDanych({ -0.4 }, { 0.6 }, sygWe[i], faktSygWy[i - 1]);


                    BuforDanych* nowaBaza = new BuforDanych();
                    nowaBaza->k = app.data[i - 1]->k;
                    nowaBaza->setB("0.6");
                    nowaBaza->setA("-0.4");
                    nowaBaza->setZaklucenie(0);
                    nowaBaza->setU(sygWe[i]);
                    nowaBaza->setY(app.oldY);
                    //cout << "\n" << app.data.back()->getY()<< "sssffaddddd\n";
                    //nowaBaza->setY(faktSygWy[i - 1]);

                    app.data.push_back(nowaBaza);


                    faktSygWy[i] = ARX.calcAll(app.data);
                    app.data.back()->setY(faktSygWy[i]);
                    app.oldY = faktSygWy[i];
                    /*cout << "\n" << ARX.calcAll(app.data) << "saddddd\n";
                    cout << "\n" << faktSygWy[i] << "saddddd\n";
                    cout << "\n" << faktSygWy[i-1] << "saddddd\n";
                    cout << "\n" << app.data[i - 1]->getY() << "saddddd\n";*/





                }
                else {
                    //BuforDanych* newdata = new BuforDanych({ -0.4 }, { 0.6 }, sygWe[i]);

                    BuforDanych* nowaBaza = new BuforDanych();
                    nowaBaza->k = 2;
                    nowaBaza->setB("0.6");
                    nowaBaza->setA("-0.4");
                    nowaBaza->setZaklucenie(0);

                    nowaBaza->setU(sygWe[i]);
                    app.data.push_back(nowaBaza);
                    nowaBaza->setY(app.oldY);

                    faktSygWy[i] = app.arxsym();
                    // cout << "\n" << app.arxsym() << "asda\n";
                    app.oldY = faktSygWy[i];
                    app.data.back()->setY(faktSygWy[i]);
                }

                //app.data.back()->y = faktSygWy[i];
               // cout << "KONIEC\n";
            }

        

        // Walidacja poprawności i raport:
        if (porownanieSekwencji(spodzSygWy, faktSygWy))
            std::cerr << "OK!\n";
        else
        {
            std::cerr << "FAIL!\n";
            raportBleduSekwencji(spodzSygWy, faktSygWy);
        }
    }
    catch (...)
    {
        std::cerr << "INTERUPTED! (niespodziwany wyjatek)\n";
    }
}
void test_ModelARX_skokJednostkowy_3()
{
    //Sygnatura testu:
    std::cerr << "ModelARX (-0.4, 0.2 | 0.6, 0.3 | 2 | 0 ) -> test skoku jednostkowego nr 3: ";
    try
    {
        // Przygotowanie danych:
        //ModelARX instancjaTestowa({ -0.4,0.2 }, { 0.6, 0.3 }, 2, 0);
        App app;
        ARX ARX;
        //app.arx = &ARX;
        app.setARX(&ARX);
        constexpr size_t LICZ_ITER = 30;

        std::vector<double> sygWe(LICZ_ITER);      // pobudzenie modelu, 
        std::vector<double> spodzSygWy(LICZ_ITER); // spodziewana sekwencja wy
        std::vector<double> faktSygWy(LICZ_ITER);  // faktyczna sekwencja wy

        // Symulacja skoku jednostkowego w chwili 1. (!!i - daje 1 dla i != 0);
        for (int i = 0; i < LICZ_ITER; i++)
            sygWe[i] = !!i;
        spodzSygWy = { 0, 0, 0, 0.6, 1.14, 1.236, 1.1664, 1.11936, 1.11446, 1.12191, 1.12587, 1.12597, 1.12521, 1.12489, 1.12491, 1.12499, 1.12501, 1.12501, 1.125, 1.125, 1.125, 1.125, 1.125, 1.125, 1.125, 1.125, 1.125, 1.125, 1.125, 1.125 };

        // Symulacja modelu:
        for (int i = 0; i < LICZ_ITER; i++) {

            if (i >= 1) {
               // app.wypiszDane();
                //BuforDanych* newdata = new BuforDanych({ -0.4 }, { 0.6 }, sygWe[i], faktSygWy[i - 1]);
                BuforDanych* nowaBaza = new BuforDanych();
                nowaBaza->k = app.data[i - 1]->k;
                nowaBaza->setB("0.6;0.3");
                nowaBaza->setA("-0.4;0.2");
                nowaBaza->setZaklucenie(0);
                nowaBaza->setU(sygWe[i]);
                //cout << "\n" << app.data.back()->getY()<< "sssffaddddd\n";
                //nowaBaza->setY(faktSygWy[i - 1]);
                nowaBaza->setY(app.oldY);
                app.data.push_back(nowaBaza);
                //cout << nowaBaza->getA(0) << nowaBaza->getA(1) << "XDXDXD\n";

                faktSygWy[i] = ARX.calcAll(app.data);
                app.data.back()->setY(faktSygWy[i]);
                app.oldY = faktSygWy[i];
                /*cout << "\n" << ARX.calcAll(app.data) << "saddddd\n";
                cout << "\n" << faktSygWy[i] << "saddddd\n";
                cout << "\n" << faktSygWy[i-1] << "saddddd\n";
                cout << "\n" << app.data[i - 1]->getY() << "saddddd\n";*/
                //app.wypiszDane();
            }
            else {
                //BuforDanych* newdata = new BuforDanych({ -0.4 }, { 0.6 }, sygWe[i]);
               // app.wypiszDane();
                BuforDanych* nowaBaza = new BuforDanych();
                nowaBaza->k = 2;
                nowaBaza->setB("0.6;0.3");
                nowaBaza->setA("-0.4;0.2");
                nowaBaza->setZaklucenie(0);
                nowaBaza->setY(app.oldY);
                nowaBaza->setU(sygWe[i]);
                app.data.push_back(nowaBaza);
               // cout << nowaBaza->getA(0) << nowaBaza->getA(1)<<"XDXDXD\n";

                faktSygWy[i] = app.arxsym();
                // cout << "\n" << app.arxsym() << "asda\n";
                app.oldY = faktSygWy[i];
                app.data.back()->setY(faktSygWy[i]);
               // app.wypiszDane();
            }

            //app.data.back()->y = faktSygWy[i];
           // cout << "KONIEC\n";
        }


        // Weryfikacja poprawności i raport:
        if (porownanieSekwencji(spodzSygWy, faktSygWy))
            std::cerr << "OK!\n";
        else
        {
            std::cerr << "FAIL!\n";
            raportBleduSekwencji(spodzSygWy, faktSygWy);
        }
    }
    catch (out_of_range )
    {
        std::cerr << "INTERsadsadUPTED! (niespodziwany wyjatek)\n";
    }
    catch (...)
    {
        std::cerr << "INTERUPTED! (niespodziwany wyjatek)\n";
    }
}
//
//
void test_UAR_1_brakPobudzenia()
{
    //Sygnatura testu:
    std::cerr << "UAR_1 -> test zerowego pobudzenia: ";
    try
    {
        // Przygotowanie danych:
        PID testPID(0.5, 5.0, 0.2);
        //odelARX testARX({ -0.4 }, { 0.6 });
        App app;
        ARX ARX;
        Sygnal syg;
        app.setSyg(&syg);
        //app.arx = &ARX;
        app.setARX(&ARX);
        app.setPID(&testPID);
        //ProstyUAR instancjaTestowa(testARX, testPID);
        constexpr size_t LICZ_ITER = 30;
        std::vector<double> sygWe(LICZ_ITER);      // pobudzenie modelu (tu same 0)
        std::vector<double> spodzSygWy(LICZ_ITER); // spodziewana sekwencja wy (tu same 0)
        std::vector<double> faktSygWy(LICZ_ITER);  // faktyczna sekwencja wy

        // Symulacja UAR:

        for (int i = 0; i < LICZ_ITER; i++)
            //faktSygWy[i] = instancjaTestowa.symuluj(sygWe[i]);
        {
            app.amplituda = sygWe[i];
            app.a = "-0.4";
            app.b = "0.6";
            app.symulacjaStep();
            faktSygWy[i] = app.oldY;
        }
        // Walidacja poprawności i raport:
       // myAssert(spodzSygWy, faktSygWy);
        if (porownanieSekwencji(spodzSygWy, faktSygWy))
            std::cerr << "OK!\n";
        else
        {
            std::cerr << "FAIL!\n";
            raportBleduSekwencji(spodzSygWy, faktSygWy);
        }
    }
    catch (...)
    {
        std::cerr << "INTERUPTED! (niespodziwany wyjatek)\n";
    }
}


void test_UAR_1_skokJednostkowy()
{
    //Sygnatura testu:
    std::cerr << "UAR_1 -> test skoku jednostkowego: ";
    try
    {
        PID testPID(0.5, 5.0, 0.2);
        //odelARX testARX({ -0.4 }, { 0.6 });
        App app;
        ARX ARX;
        Sygnal syg;
        app.setSyg(&syg);
        //app.arx = &ARX;
        app.setARX(&ARX);
        app.setPID(&testPID);
        app.clikrun();// Przygotowanie danych:
        //RegulatorPID testPID(0.5, 5.0, 0.2);
        //ModelARX testARX({ -0.4 }, { 0.6 });
        //ProstyUAR instancjaTestowa(testARX, testPID);
        constexpr size_t LICZ_ITER = 30;
        std::vector<double> sygWe(LICZ_ITER);      // pobudzenie modelu (tu same 0)
        std::vector<double> spodzSygWy(LICZ_ITER); // spodziewana sekwencja wy (tu same 0)
        std::vector<double> faktSygWy(LICZ_ITER);  // faktyczna sekwencja wy

        // Symulacja skoku jednostkowego w chwili 1. (!!i - daje 1 dla i != 0);
        for (int i = 0; i < LICZ_ITER; i++)
            sygWe[i] = !!i;
        spodzSygWy = { 0, 0.9, 0.9, 0.614, 0.6196, 0.78828, 0.864728, 0.85054, 0.849231,
                       0.881775, 0.911732, 0.924077, 0.93093, 0.941192, 0.952188, 0.960156,
                       0.965694, 0.970663, 0.975398, 0.97939, 0.982546, 0.985174, 0.987472,
                       0.989446, 0.991089, 0.992459, 0.993624, 0.994616, 0.995453, 0.996157 };

        // Symulacja UAR:
        double x;
        //app.clikrun();
        
        for (int i = 0; i < LICZ_ITER; i++) {
            
            app.a = "-0.4";
            app.b = "0.6";
            app.amplituda = sygWe[i];
       

            app.symulacjaStep();
           
            faktSygWy[i] = app.oldY;
        }

        if (porownanieSekwencji(spodzSygWy, faktSygWy))
            std::cerr << "OK!\n";
        else
        {
            std::cerr << "FAIL!\n";
            raportBleduSekwencji(spodzSygWy, faktSygWy);
        }
    }
    catch (...)
    {
        std::cerr << "INTERUPTED! (niespodziwany wyjatek)\n";
    }
}

int main() {
    //App aplikacja;
    //ARX arx;
    //Sygnal syg;
    //PID pid(1, 0.05, 0.01 );
    //aplikacja.setSyg(&syg);
    //aplikacja.setARX(&arx);
    //aplikacja.setPID(&pid);
    ////gluwna petla
    //aplikacja.symulacja();

    //// wupisz w przyszlosci zaspis do pliku
    //aplikacja.wypiszDane();
 
    //aplikacja.zapisBazydanychdopliku();

    cout<<"testy\n\n";

    test_RegulatorP_brakPobudzenia();
    test_RegulatorP_skokJednostkowy();
    test_RegulatorPID_skokJednostkowy();
    cout << "XXXX\n";
    test_ModelARX_brakPobudzenia();
    test_ModelARX_skokJednostkowy_2();
   test_ModelARX_skokJednostkowy_1();
    test_ModelARX_skokJednostkowy_3();
    test_UAR_1_brakPobudzenia();
    test_UAR_1_skokJednostkowy();
}