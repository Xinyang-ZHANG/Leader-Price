//
// Created by MAC on 2019/5/31.
//

#include <iostream>
#include <sstream>

using namespace std;

#include "Merchandise.h"
#include "Drink.h"

Drink::Drink(string code, string brand, Date dateConsomme, string name, int number, float cost, float price, string category, float volume)
        : Merchandise(code, brand, dateConsomme, name, number, cost, price)
{
    this->category = category;
    this->volume = volume;
}
string Drink::convertnumbertostring(double num)
{
    stringstream convert;
    convert<<num;
    string numfinal = convert.str();
    return numfinal;
}
string Drink::getCate() { return category; }
float Drink::getVolume() { return volume; }
string Drink::afficher()
{
    string output = Merchandise::afficher();
    //cout<<"Category: "<<category<<endl;
    string CATEGORY = "Category: " + category + "\n";
    //cout<<"Volume: "<<volume<<"L"<<endl<<endl;
    string VOLUME = "Volume: " + convertnumbertostring(volume) + "\n";
    string outputD = output + CATEGORY + VOLUME + "\n" + "\n";
    //cout<<outputD;
    return outputD;
}

