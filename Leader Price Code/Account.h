//
// Created by MAC on 2019/6/6.
//

#ifndef LEADER_PRICE_ACCOUNT_H
#define LEADER_PRICE_ACCOUNT_H

#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>

using namespace std;

#include "MyException.h"
#include "Merchandise.h"
#include "Houseware.h"
#include "Clothing.h"
#include "Food.h"
#include "Drink.h"
#include "Purchase_DP.h"
#include "Cashier.h"
#include "ListCashier.h"

class AccountManager
{
private:
    string Firstname;
    string Lastname;
    string Password;
    int workingNum;
    vector<Houseware> soldH, H;
    vector<Clothing> soldC, C;
    vector<Food> soldF, F;
    vector<Drink> soldD, D;
    int nbHouseware = 0;
    int nbClothing = 0;
    int nbFood = 0;
    int nbDrink = 0;

    Date today;
    Color chooseColor(string colort);
    vector<Houseware> minusH();
    vector<Clothing> minusC();
    vector<Food> minusF();
    vector<Drink> minusD();

    int pop_up(string title, string output);
public:
    AccountManager(string prenom, string nom, string password, int nb);
    AccountManager();
    void modifyFileMerchandise();  //修改文件（在每次结束程序前修改文件，而不是每次操作之后，因此应当由时间触发，放在StockToday中）

    int getWorkingNumber();
    string getPassword();
    int getNbHouseware();
    int getNbClothing();
    int getNbFood();
    int getNbDrink();

    void getOrder();
    void pickSoldBoxs(vector<Houseware> H_fromManager, vector<Clothing> C_fromManager, vector<Food> F_fromManager, vector<Drink> D_fromManager);
    void afficherBoxsVendu();  //测试用

    void showAll();
    string showToday();
    void afficher();
    void afficherInfoHouseware(string code);
    void affichertInfoClothing(string code);
    void afficherInfoFood(string code);
    void afficherInfoDrink(string code);

    void addHousewareManually();
    void addClothingManually();
    void addFoodManually();
    void addDrinkManually();
    void removeHousewareManually(string code, int num);
    void removeClothingManually(string code, int num);
    void removeFoodManually(string code, int num);
    void removeDrinkManually(string code, int num);
};

#endif //LEADER_PRICE_ACCOUNT_H
