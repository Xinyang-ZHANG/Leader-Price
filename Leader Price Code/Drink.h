//
// Created by MAC on 2019/5/31.
//

#pragma once;

#ifndef LEADER_PRICE_DRINK_H
#define LEADER_PRICE_DRINK_H

#endif //LEADER_PRICE_DRINK_H

#include <iostream>
#include <vector>

using namespace std;

#include "Merchandise.h"

class Drink: public Merchandise
{
private:
    string category; float volume;
    string convertnumbertostring(double num);
    void interf(){}
public:
    Drink(string code, string brand, Date dateConsomme, string name, int number, float cost, float price, string category, float volume);
    string getCate();
    float getVolume();
    string afficher();
};


