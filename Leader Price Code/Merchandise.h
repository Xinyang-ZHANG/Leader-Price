//
// Created by MAC on 2019/5/31.
//

#pragma once

#ifndef LEADER_PRICE_MERCHANDISE_H
#define LEADER_PRICE_MERCHANDISE_H


#include <iostream>

using namespace std;

#include "MyException.h"

struct Date{ int jour; int moi; int annee; };

class Merchandise
{
private:
    string code;
    string brand;
    Date dateConsomme;
    string name;
    int number;
    float cost;
    float price;
    string convertnumbertostring(double num);
    virtual void interf() = 0;
public:
    Merchandise(string code, string brand, Date dateConsomme, string name, int number, float cost, float price);
    string getCode();
    string getBrand();
    Date getDateConsomme();
    string getName();
    int getNumber();
    float getCost();
    float getPrice();
    void modifyNumber(int num, bool plusoumoins);
    virtual string afficher();
};

#endif //LEADER_PRICE_MERCHANDISE_H