//
// Created by MAC on 2019/6/5.
//

#ifndef LEADER_PRICE_LISTCASHIER_H
#define LEADER_PRICE_LISTCASHIER_H

#include <iostream>

using namespace std;

#include "Cashier.h"

#define numMAX 5

class ListCashier
{
private:
    Cashier* tabCash[numMAX];
    int numCash = 0;
public:
    ListCashier();
    string afficher() const;
    Cashier** getList();
    void addCashier(Cashier* cashier);
    void removeCashier(int numero);
    int getNumCash();
    float AllSalary();
    float AllTurnover();
};

#endif //LEADER_PRICE_LISTCASHIER_H
