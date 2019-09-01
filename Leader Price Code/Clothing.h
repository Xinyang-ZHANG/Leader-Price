//
// Created by MAC on 2019/5/31.
//

#pragma once

#ifndef LEADER_PRICE_CLOTHING_H
#define LEADER_PRICE_CLOTHING_H


#include <iostream>
#include <vector>

using namespace std;

#include "Merchandise.h"
#include "MyException.h"

enum Color {RED, GREEN, BLUE, YELLOW, WHITE, BLACK, GREY, ORANGE, WRONGCOLOR};

class Clothing: public Merchandise
{
private:
    string category;
    Color color;
    void interf(){};
public:
    Clothing(string code, string brand, Date dateConsomme, string name, int number, float cost, float price, string category, Color color);
    string getCate();
    Color getColor();
    string afficher();
};

#endif //LEADER_PRICE_CLOTHING_H
