//
// Created by MAC on 2019/6/6.
//

#ifndef LEADER_PRICE_MANAGER_H
#define LEADER_PRICE_MANAGER_H

#pragma once

#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <ctime>

using namespace std;

#include "Account.h"
#include "MyException.h"
#include "Merchandise.h"
#include "Houseware.h"
#include "Clothing.h"
#include "Food.h"
#include "Drink.h"
#include "Purchase_DP.h"
#include "Cashier.h"
#include "ListCashier.h"

//#include "Interface.h"

enum TYPE {HOUSEWARE, CLOTHING, FOOD, DRINK, WRONG};
struct FINI_REUSSI {bool finish; bool success;};

class Manager
{
private:
    vector<Cashier> readMyEmployee();
    vector<AccountManager> readAM();

    //relais des boîtes
    vector<Houseware> SoldBoxH;
    vector<Clothing> SoldBoxC;
    vector<Food> SoldBoxF;
    vector<Drink> SoldBoxD;
    //relais des boîtes

    float AllGain = 0;
    float AllTurnover = 0;
    TYPE convert_stringtoTYPE(string str);
    bool compareHour();
    void modifyFileMerchandiseAM();  //修改文件（在每次结束程序前修改文件，而不是每次操作之后，因此应当由时间触发，放在StockToday中）

    FINI_REUSSI SellPop_up(int argc, char **argv, int choose, int numBadge);
    int pop_up(string title, string output);
public:
    AccountManager accountManager;
    ListCashier MyEmployee;  //此处为已登录的收银员

    //***********************************//

    Manager();
    void delay(); //改善程序性能
    string showToday();
    void StockToday();  //读取MyEmployee中的卖掉盒子并装入SoldBox，修改所有list（两大部分：去除所有卖掉盒子中的商品，去除所有过期商品）
                        // （修改accountmanager以及cashier中的仓库盒子，清空cashier的卖掉盒子）
                        // 再修改商品文件
                        // ！注意：此函数自动运行不由用户操作，由时间触发 ！

    //***********************************//pour AM

    void Register(string Firstname, string Lastname, string password, int code, int argc, char **argv, Manager &managerTemp);
    void Login(int code, string password, int argc, char **argv, Manager &managerTemp);
    void getOrderToAccount();
    void SoldBox_toAM();

    void showme();
    void showHouseware(string code);
    void showClothing(string code);
    void showFood(string code);
    void showDrink(string code);
    void showAllMerchandise();  //隶属于Account，管理员账户理应拥有仓库全部信息
    void showMyEmployees();  //隶属于系统Manager，为系统的私有，管理员登入后才能查看
    void showTodaySoldMerchandise();

    void modifyCashiersSalary(int numBadge, float howmuch, bool UP);
    void removeHousewareFromAMManually(string code, int num);
    void removeClothingFromAMManually(string code, int num);
    void removeFoodFromAMManually(string code, int num);
    void removeDrinkFromAMManually(string code, int num);
    void addManually();

    //***********************************//pour caissiers

    void LoginCashier(int workingNum, int argc, char **argv, Manager &managerTemp);

    FINI_REUSSI sell(int argc, char **argv, int workingNum);
    void showwarehouse(int workingNum);
    string showTodayTurnover();
};

#endif //LEADER_PRICE_MANAGER_H
