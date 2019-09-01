//
// Created by MAC on 2019/5/31.
//

#include <iostream>

using namespace std;

#include "Food.h"
#include "Merchandise.h"

Food::Food(string code, string brand, Date dateConsomme, string name, int number, float cost, float price, string category, bool fresh)
        : Merchandise(code, brand, dateConsomme, name, number, cost, price)
{
    this->category = category;
    this->fresh = fresh;
}
string Food::getCate() { return category; }
bool Food::FreshOrNot() { return fresh; }
string Food::afficher()
{
    string output = Merchandise::afficher();
    //cout<<"Category: "<<category<<endl;
    string CATEGORY = "Category: " + category + "\n";
    string FRESH;
    if (fresh)
        FRESH = "FreshOrNot: Yes!";
    else
        FRESH = "FreshOrNot: NO!";
    string outputF = output + CATEGORY + FRESH + "\n" + "\n";
    //cout<<outputF;
    return outputF;
}