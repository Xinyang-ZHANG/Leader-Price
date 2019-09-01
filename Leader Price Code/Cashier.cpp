//
// Created by MAC on 2019/6/5.
//

#include <iostream>
#include <vector>
#include <sstream>
#include <QTextBrowser>
#include <QObject>

using namespace std;

#include "Cashier.h"
#include "ListCashier.h"
#include "Houseware.h"
#include "Clothing.h"
#include "Food.h"
#include "Drink.h"
#include "Merchandise.h"
#include "MyException.h"
#include "Manager.h"
#include "Account.h"


void Cashier::delay()
{
    clock_t delay = 1 * CLOCKS_PER_SEC;
    clock_t start = clock();
    while ((clock() - start) < delay) {}
}
int Cashier::pop_up(string title, string output)
{
    QTextBrowser *showText = new QTextBrowser;
    showText->setText(QString::fromStdString(output));
    showText->setWindowTitle(QString::fromStdString(title));
    showText->show();
}
Cashier::Cashier(string prenom, string nom, int numeroTravail, float salaire)
{
    Firstname = prenom;
    Lastname = nom;
    numBadge = numeroTravail;
    wage = salaire;
    turnover = 0;
}
Cashier::Cashier(){}
void Cashier::readEntrepot()
{
    Purchase_DP purchaseTemps;
    purchaseTemps.ReadList();
    entrepotH = purchaseTemps.getHouseware();
    entrepotC = purchaseTemps.getClothing();
    entrepotF = purchaseTemps.getFood();
    entrepotD = purchaseTemps.getDrink();
}
void Cashier::receiveMoneyH(Houseware H, int num)
{
    turnover += (num * (H.getPrice() - H.getCost()));
    //pop_up("提示", "已售出！");
}
void Cashier::receiveMoneyC(Clothing C, int num)
{
    turnover += (num * (C.getPrice() - C.getCost()));
    //pop_up("提示", "已售出！");
}
void Cashier::receiveMoneyF(Food F, int num)
{
    turnover += (num * (F.getPrice() - F.getCost()));
    //pop_up("提示", "已售出！");
}
void Cashier::receiveMoneyD(Drink D, int num)
{
    turnover += (num * (D.getPrice() - D.getCost()));
    //pop_up("提示", "已售出！");
}


bool Cashier::SellHouseware(const string &code, int num)
{
    vector<Houseware>::iterator iterEntrepotH;
    int searchH = 0;
    bool sold = false; bool success = false;
    for (iterEntrepotH = entrepotH.begin(); iterEntrepotH != entrepotH.end(); iterEntrepotH++)  //输入商品码，在仓库盒子寻找
    {
        if (code == entrepotH[searchH].getCode())  //如果找到
        {

            if (entrepotH[searchH].getNumber() < num )
            {
                delay();
                pop_up("提示", "存货不足！");
                //cout<<"Stock not sufficient!"<<endl<<endl;
                sold = true;
                break;
            }

            // 以下操作用于修改卖掉盒子 //*******************// 以上操作用于提示仓库盒子货物不够（num过大） //

            vector<Houseware>::iterator iterSoldH;
            int searchsoldH = 0;
            for (iterSoldH = soldH.begin(); iterSoldH != soldH.end(); iterSoldH++)  //在卖掉盒子中寻找是否已经卖掉过相同商品码的商品
            {
                if (code == soldH[searchsoldH].getCode())
                {
                    soldH[searchsoldH].modifyNumber(num, true);  //如果卖掉盒子中有，就修改该商品存货量
                    receiveMoneyH(soldH[searchsoldH], num);
                    sold = true; success = true;
                    break;
                }
                searchsoldH++;
            }
            if (searchsoldH == soldH.size()) //如果卖掉盒子中没有
            {
                Houseware Htemps = entrepotH[searchH];  //仓库盒子中选出此类商品，注意此时个数是仓库盒子中商品的个数
                int HnumberTemps = entrepotH[searchH].getNumber();
                Htemps.modifyNumber((num - HnumberTemps), true);  //去除仓库盒子中商品的个数，修改为num

                soldH.push_back(Htemps);  //就在卖掉盒子中加上(注意加上一个或多个)
                receiveMoneyH(soldH[soldH.size() - 1], num);  //容器中最后一个元素即为刚刚卖掉的商品
                sold = true; success = true;
            }

            // 以上操作用于修改卖掉盒子 //*******************// 以下操作用于修改仓库盒子 //

            if (entrepotH[searchH].getNumber() == num)
                entrepotH.erase(iterEntrepotH);
            else
                entrepotH[searchH].modifyNumber(num, false);

            break;
        }
        searchH++;
    }
    if(!sold)
        pop_up("提示", "商品码错误！");
    //cout<<"Wrong merchandise code!"<<endl<<endl;
    return success;
}
bool Cashier::SellClothing(const string &code, int num)
{
    vector<Clothing>::iterator iterEntrepotC;
    int searchC = 0;
    bool sold = false; bool success = false;
    for (iterEntrepotC = entrepotC.begin(); iterEntrepotC != entrepotC.end(); ++iterEntrepotC)  //输入商品码，在仓库盒子寻找
    {
        if (code == entrepotC[searchC].getCode())  //如果找到
        {
            if (entrepotC[searchC].getNumber() < num )
            {
                delay();
                pop_up("提示", "存货不足！");
                //cout<<"Stock not sufficient!"<<endl<<endl;
                sold = true;
                break;
            }

            // 以下操作用于修改卖掉盒子 //*******************// 以上操作用于提示仓库盒子货物不够（num过大） //

            vector<Clothing>::iterator iterSoldC;
            int searchsoldC = 0;
            for (iterSoldC = soldC.begin(); iterSoldC != soldC.end(); iterSoldC++)  //在卖掉盒子中寻找是否已经卖掉过相同商品码的商品
            {
                if (code == soldC[searchsoldC].getCode())
                {
                    soldC[searchsoldC].modifyNumber(num, true);  //如果卖掉盒子中有，就修改该商品存货量
                    receiveMoneyC(soldC[searchsoldC], num);
                    sold = true; success = true;
                    break;
                }
                searchsoldC++;
            }
            if (searchsoldC == soldC.size()) //如果卖掉盒子中没有
            {
                Clothing Ctemps = entrepotC[searchC];  //仓库盒子中选出此类商品，注意此时个数是仓库盒子中商品的个数
                int CnumberTemps = entrepotC[searchC].getNumber();
                Ctemps.modifyNumber((num - CnumberTemps), true);  //去除仓库盒子中商品的个数，修改为num
                soldC.push_back(Ctemps);  //就在卖掉盒子中加上(注意加上一个或多个)
                receiveMoneyC(soldC[soldC.size() - 1], num);  //容器中最后一个元素即为刚刚卖掉的商品
                sold = true; success = true;
            }

            // 以上操作用于修改卖掉盒子 //*******************// 以下操作用于修改仓库盒子 //

            if (entrepotC[searchC].getNumber() == num)
                entrepotC.erase(iterEntrepotC);
            else
                entrepotC[searchC].modifyNumber(num, false);
            break;
        }
        searchC++;
    }
    if(!sold)
        pop_up("提示", "商品码错误！");
    //cout<<"Wrong merchandise code!"<<endl<<endl;
    return success;
}
bool Cashier::SellFood(const string &code, int num)
{
    vector<Food>::iterator iterEntrepotF;
    int searchF = 0;
    bool sold = false; bool success = false;
    for (iterEntrepotF = entrepotF.begin(); iterEntrepotF != entrepotF.end(); iterEntrepotF++)  //输入商品码，在仓库盒子寻找
    {
        if (code == entrepotF[searchF].getCode())  //如果找到
        {
            if (entrepotF[searchF].getNumber() < num )
            {
                delay();
                pop_up("提示", "存货不足！");
                //cout<<"Stock not sufficient!"<<endl<<endl;
                sold = true;
                break;
            }

            // 以下操作用于修改卖掉盒子 //*******************// 以上操作用于提示仓库盒子货物不够（num过大） //

            vector<Food>::iterator iterSoldF;
            int searchsoldF = 0;
            for (iterSoldF = soldF.begin(); iterSoldF != soldF.end(); iterSoldF++)  //在卖掉盒子中寻找是否已经卖掉过相同商品码的商品
            {
                if (code == soldF[searchsoldF].getCode())
                {
                    soldF[searchsoldF].modifyNumber(num, true);  //如果卖掉盒子中有，就修改该商品存货量
                    receiveMoneyF(soldF[searchsoldF], num);
                    sold = true; success = true;
                    break;
                }
                searchsoldF++;
            }
            if (searchsoldF == soldF.size()) //如果卖掉盒子中没有
            {
                Food Ftemps = entrepotF[searchF];  //仓库盒子中选出此类商品，注意此时个数是仓库盒子中商品的个数
                int FnumberTemps = entrepotF[searchF].getNumber();
                Ftemps.modifyNumber((num - FnumberTemps), true);  //去除仓库盒子中商品的个数，修改为num
                soldF.push_back(Ftemps);  //就在卖掉盒子中加上(注意加上一个或多个)
                receiveMoneyF(soldF[soldF.size() - 1], num);  //容器中最后一个元素即为刚刚卖掉的商品
                sold = true; success = true;
            }

            // 以上操作用于修改卖掉盒子 //*******************// 以下操作用于修改仓库盒子 //

            if (entrepotF[searchF].getNumber() == num)
                entrepotF.erase(iterEntrepotF);
            else
                entrepotF[searchF].modifyNumber(num, false);

            break;
        }
        searchF++;
    }
    if(!sold)
        pop_up("提示", "商品码错误！");
    //cout<<"Wrong merchandise code!"<<endl<<endl;
    return success;
}
bool Cashier::SellDrink(const string &code, int num)
{
    vector<Drink>::iterator iterEntrepotD;
    int searchD = 0;
    bool sold = false; bool success = false;
    for (iterEntrepotD = entrepotD.begin(); iterEntrepotD != entrepotD.end(); iterEntrepotD++)  //输入商品码，在仓库盒子寻找
    {
        if (code == entrepotD[searchD].getCode())  //如果找到
        {
            if (entrepotD[searchD].getNumber() < num )
            {
                delay();
                pop_up("提示", "存货不足！");
                //cout<<"Stock not sufficient!"<<endl<<endl;
                sold = true;
                break;
            }

            // 以下操作用于修改卖掉盒子 //*******************// 以上操作用于提示仓库盒子货物不够（num过大） //

            vector<Drink>::iterator iterSoldD;
            int searchsoldD = 0;
            for (iterSoldD = soldD.begin(); iterSoldD != soldD.end(); iterSoldD++)  //在卖掉盒子中寻找是否已经卖掉过相同商品码的商品
            {
                if (code == soldD[searchsoldD].getCode())
                {
                    soldD[searchsoldD].modifyNumber(num, true);  //如果卖掉盒子中有，就修改该商品存货量
                    receiveMoneyD(soldD[searchsoldD], num);
                    sold = true; success = true;
                    break;
                }
                searchsoldD++;
            }
            if (searchsoldD == soldD.size()) //如果卖掉盒子中没有
            {
                Drink Dtemps = entrepotD[searchD];  //仓库盒子中选出此类商品，注意此时个数是仓库盒子中商品的个数
                int DnumberTemps = entrepotD[searchD].getNumber();
                Dtemps.modifyNumber((num - DnumberTemps), true);  //去除仓库盒子中商品的个数，修改为num
                soldD.push_back(Dtemps);  //就在卖掉盒子中加上(注意加上一个或多个)
                receiveMoneyD(soldD[soldD.size() - 1], num);  //容器中最后一个元素即为刚刚卖掉的商品
                sold = true; success = true;
            }

            // 以上操作用于修改卖掉盒子 //*******************// 以下操作用于修改仓库盒子 //

            if (entrepotD[searchD].getNumber() == num)
                entrepotD.erase(iterEntrepotD);
            else
                entrepotD[searchD].modifyNumber(num, false);

            break;
        }
        searchD++;
    }
    if(!sold)
        pop_up("提示", "商品码错误！");
        //cout<<"Wrong merchandise code!"<<endl<<endl;
    return success;
}
int Cashier::getNumBadge() { return numBadge; }
float Cashier::getSalary() { return wage; }
float Cashier::getTurnover() { return turnover; }
string Cashier::getMe()
{
    string output, numbadge, salary;
    stringstream convert1, convert2;
    convert1<<numBadge;
    convert2<<wage;
    numbadge = convert1.str();
    salary = convert2.str();
    output = Firstname + "  " + Lastname + "  " + numbadge + "  " + salary + "\n";
    return output;
}
vector<Houseware> Cashier::getSoldBoxH() { return soldH; }
vector<Clothing> Cashier::getSoldBoxC() { return soldC; }
vector<Food> Cashier::getSoldBoxF() { return soldF; }
vector<Drink> Cashier::getSoldBoxD() { return soldD; }

void Cashier::modifySalary(float HowMuch, bool moreORless)
{
    if (moreORless)
        wage += HowMuch;
    else
        wage -= HowMuch;
}
string Cashier::afficher()
{
    string output;
    stringstream convert1, convert2, convert3;
    convert1<<numBadge;
    string numBadgefinal = convert1.str();
    convert2<<wage;
    string wagefinal = convert2.str();
    convert3<<turnover;
    string turnoverfinal = convert3.str();
    output += "Firstname: " + Firstname + "\n";
    output += "Lastname: " + Lastname + "\n";
    output += "Working number: " + numBadgefinal + "\n";
    output += "Wage: " + wagefinal + "\n";
    output += "Turnover: " + turnoverfinal + "\n" + "\n";
    return output;
}
void Cashier::show()
{
    string output;
    stringstream convert1, convert2, convert3;
    convert1<<numBadge;
    string numBadgefinal = convert1.str();
    convert2<<wage;
    string wagefinal = convert2.str();
    convert3<<turnover;
    string turnoverfinal = convert3.str();
    output += "Firstname: " + Firstname + "\n";
    output += "Lastname: " + Lastname + "\n";
    output += "Working number: " + numBadgefinal + "\n";
    output += "Wage: " + wagefinal + "\n";
    output += "Turnover: " + turnoverfinal + "\n" + "\n";
    pop_up("我的信息", output);
}
string Cashier::afficherSold()
{
    string output;
    output += "********* My houseware *********\n";
    for (int numH = 0; numH < soldH.size(); numH++)
        output += soldH[numH].afficher();
    output += "********** My clothing **********\n";
    for (int numC = 0; numC < soldC.size(); numC++)
        output += soldC[numC].afficher();
    output += "************ My food ************\n";
    for (int numF = 0; numF < soldF.size(); numF++)
        output += soldF[numF].afficher();
    output += "************ My drink ************\n";
    for (int numD = 0; numD < soldD.size(); numD++)
        output += soldD[numD].afficher();
    output += "**********************************\n";
    return output;
}
void Cashier::vider()
{
    soldH.clear();
    soldC.clear();
    soldF.clear();
    soldD.clear();
}
void Cashier::afficher_entrepot()
{
    string output;
    output += "仓库中的Houseware: \n";
    for (int num = 0; num < entrepotH.size(); num++)
        output += entrepotH[num].afficher();
    output += "仓库中的Clothing: \n";
    for (int num = 0; num < entrepotC.size(); num++)
        output += entrepotC[num].afficher();
    output += "仓库中的Food: \n";
    for (int num = 0; num < entrepotF.size(); num++)
        output += entrepotF[num].afficher();
    output += "仓库中的Drink: \n";
    for (int num = 0; num < entrepotD.size(); num++)
        output += entrepotD[num].afficher();
    pop_up("我的仓库", output);
}