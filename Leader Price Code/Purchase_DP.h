//
// Created by MAC on 2019/5/31.
//

#pragma once;

#ifndef LEADER_PRICE_PURCHASE_DP_H
#define LEADER_PRICE_PURCHASE_DP_H

#endif //LEADER_PRICE_PURCHASE_DP_H

#include <iostream>
#include <vector>

using namespace std;

#include "Houseware.h"
#include "Clothing.h"
#include "Food.h"
#include "Drink.h"


class Purchase_DP
{
private:
    vector<Houseware> H;
    vector<Clothing> C;
    vector<Food> F;
    vector<Drink> D;
    Color chooseColor(string colort);
    Date today;
    bool compareDate(Date date);
    void clearPerishables();
public:
    Purchase_DP();
    void ReadList();
    vector<Houseware> getHouseware();
    vector<Clothing> getClothing();
    vector<Food> getFood();
    vector<Drink> getDrink();
};
