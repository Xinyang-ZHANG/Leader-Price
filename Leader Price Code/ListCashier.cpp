//
// Created by MAC on 2019/6/5.
//

#include <iostream>

using namespace std;

#include "Cashier.h"
#include "ListCashier.h"
#include "MyException.h"

ListCashier::ListCashier(){}
string ListCashier::afficher() const
{
    string output;
    for (int i = 0; i < numCash; i++)
        output += tabCash[i]->afficher();
    return output;
}
Cashier** ListCashier::getList() { return tabCash; }
void ListCashier::addCashier(Cashier* cashier)
{
    if (numCash < numMAX)
    {
        tabCash[numCash] = cashier;
        numCash++;
    }
    else
    {
        MyException ex("too many cashiers!");
        throw ex;
    }
}
void ListCashier::removeCashier(int numero)
{
    for (int i = 0; i < numCash; i++)
        if (tabCash[i]->getNumBadge() == numero)
        {
            for (int j = i; j < numCash; j++)
                tabCash[j] = tabCash[j + 1];
            numCash--;
        }
}
int ListCashier::getNumCash() { return numCash; }
float ListCashier::AllSalary()
{
    float allsalary = 0;
    for (int i = 0; i < numCash; i++)
        allsalary += tabCash[i]->getSalary();
    return allsalary;
}
float ListCashier::AllTurnover()
{
    float allturnover = 0;
    for (int i = 0; i < numCash; i++)
        allturnover += tabCash[i]->getTurnover();
    return allturnover;
}
