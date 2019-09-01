//
// Created by MAC on 2019/5/31.
//

#pragma once

#ifndef LEADER_PRICE_HOUSEWARE_H
#define LEADER_PRICE_HOUSEWARE_H

#endif //LEADER_PRICE_HOUSEWARE_H

#include <iostream>
#include <vector>

using namespace std;

#include "Merchandise.h"

class Houseware: public Merchandise
{
private:
    string category;
    void interf(){}
public:
    Houseware (string code, string brand, Date dateConsomme, string name, int number, float cost, float price, string category);
    string getCate();
    string afficher();
};

