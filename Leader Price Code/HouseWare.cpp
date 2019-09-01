//
// Created by MAC on 2019/5/31.
//

#include <iostream>

using namespace std;

#include "Merchandise.h"
#include "Houseware.h"

Houseware::Houseware(string code, string brand, Date dateConsomme, string name, int number, float cost, float price, string category)
        : Merchandise(code, brand, dateConsomme, name, number, cost, price)
{
    this->category = category;
}
string Houseware::getCate() { return category; }
string Houseware::afficher()
{
    string output = Merchandise::afficher();
    //cout<<"Category: "<<category<<endl<<endl;
    string CATEGORY = "Category: " + category + "\n";
    string outputH = output + CATEGORY + "\n";
    //cout<<outputH;
    return outputH;
}
