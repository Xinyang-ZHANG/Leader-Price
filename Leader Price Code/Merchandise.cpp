//
// Created by MAC on 2019/5/31.
//

#include <iostream>
#include <sstream>

using namespace std;

#include "Merchandise.h"
#include "Houseware.h"
#include "Clothing.h"
#include "Food.h"
#include "Drink.h"
#include "MyException.h"

Merchandise::Merchandise(string code, string brand, Date dateConsomme, string name, int number, float cost, float price)
{
    this->code = code;
    this->brand = brand;
    this->dateConsomme = dateConsomme;
    this->name = name;
    this->number = number;
    this->cost = cost;
    this->price = price;
}

string Merchandise::convertnumbertostring(double num)
{
    stringstream convert;
    convert<<num;
    string numfinal = convert.str();
    return numfinal;
}
string Merchandise::getCode() { return code; }
string Merchandise::getBrand() { return brand; }
Date Merchandise::getDateConsomme() { return dateConsomme; }
string Merchandise::getName() { return name; }
int Merchandise::getNumber() { return number; }
float Merchandise::getCost() { return cost; }
float Merchandise::getPrice() { return price; }
void Merchandise::modifyNumber(int num, bool plusoumoins)
{
    if (plusoumoins)
        number += num;
    else
        number -= num;
}
string Merchandise::afficher()
{
    //cout<<"Code: "<<code<<endl;
    //cout<<"Brand: "<<brand<<endl;
    //cout<<"Date of consommation: "<<dateConsomme.jour<<"/"<<dateConsomme.moi<<"/"<<dateConsomme.annee<<endl;
    //cout<<"Name: "<<name<<endl;
    //cout<<"How many: "<<number<<endl;
    //cout<<"Cost: "<<cost<<endl;
    //cout<<"Price: "<<price<<endl;

    string CODE = "Code: " + code + "\n";
    string BRAND = "Brand: " + brand + "\n";
    string DATEOFCONSOMMATION = "Date of consommation: " + convertnumbertostring(dateConsomme.jour) + "/" +
            convertnumbertostring(dateConsomme.moi) + "/" + convertnumbertostring(dateConsomme.annee) + "\n";
    string NAME = "Name: " + name + "\n";
    string HOWMANY = "How many: " + convertnumbertostring(number) + "\n";
    string COST = "Cost: " + convertnumbertostring(cost) + "\n";
    string PRICE = "Price: " +convertnumbertostring(price) + "\n";
    string output = CODE + BRAND + DATEOFCONSOMMATION + NAME + HOWMANY + COST + PRICE;
    return output;
}