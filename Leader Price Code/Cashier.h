//
// Created by MAC on 2019/6/5.
//

#ifndef LEADER_PRICE_CASHIER_H
#define LEADER_PRICE_CASHIER_H

#include <iostream>
#include <vector>

using namespace std;

#include "Houseware.h"
#include "Clothing.h"
#include "Food.h"
#include "Drink.h"
#include "Merchandise.h"
#include "MyException.h"

class Cashier //Cashier不需要登录
{
private:
    string Firstname, Lastname;
    int numBadge;
    float wage, turnover;
    vector<Houseware> soldH, entrepotH;
    vector<Clothing> soldC, entrepotC;
    vector<Food> soldF, entrepotF;
    vector<Drink> soldD, entrepotD;

    void receiveMoneyH(Houseware H, int num);
    void receiveMoneyC(Clothing C, int num);
    void receiveMoneyF(Food F, int num);
    void receiveMoneyD(Drink D, int num);
    int pop_up(string title, string output);
public:
    Cashier(string prenom, string nom, int numeroTravail, float salaire);
    Cashier();
    void delay(); //改善程序性能
    void readEntrepot();
    float getSalary();
    float getTurnover();
    int getNumBadge();
    string getMe();  //仅用于存入个人数据，无turnover
    vector<Houseware> getSoldBoxH();
    vector<Clothing> getSoldBoxC();
    vector<Food> getSoldBoxF();
    vector<Drink> getSoldBoxD();

    void modifySalary(float HowMuch, bool moreORless);
    string afficher(); //本收银员所有信息传到上层
    void show(); //显示本收银员所有信息
    string afficherSold();
    void vider();

    bool SellHouseware(const string& code, int num);
    bool SellClothing(const string& code, int num);
    bool SellFood(const string& code, int num);
    bool SellDrink(const string& code, int num);  //Account登入也无法操作Cashier的销售行为

    void afficher_entrepot(); //测试用
};

#endif //LEADER_PRICE_CASHIER_H
