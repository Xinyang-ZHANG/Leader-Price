//
// Created by MAC on 2019/5/31.
//

#pragma once;

#ifndef LEADER_PRICE_FOOD_H
#define LEADER_PRICE_FOOD_H

#include <iostream>
#include <vector>

using namespace std;

#include "Merchandise.h"

class Food: public Merchandise
{
private:
    string category; bool fresh;
    void interf(){}
public:
    Food(string code, string brand, Date dateConsomme, string name, int number, float cost, float price, string category, bool fresh);
    string getCate();
    bool FreshOrNot();
    string afficher();
};

#endif //LEADER_PRICE_FOOD_H
