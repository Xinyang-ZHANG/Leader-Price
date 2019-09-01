//
// Created by MAC on 2019/5/31.
//

#include <iostream>

using namespace std;

#include "Merchandise.h"
#include "Clothing.h"
#include "MyException.h"

Clothing::Clothing(string code, string brand, Date dateConsomme, string name, int number, float cost, float price, string category, Color color)
        : Merchandise(code, brand, dateConsomme, name, number, cost, price)
{
    this->category = category;
    this->color = color;
}
string Clothing::getCate() { return category; }
Color Clothing::getColor() { return color; }
string Clothing::afficher()
{
    string output = Merchandise::afficher();
    //cout<<"Category: "<<category<<endl;
    string CATEGORY = "Category: " + category + "\n";
    string COLOR = "Color: ";
    //cout<<"Color: ";
    switch ((int)color)
    {
        case 0:
            COLOR += "ROUGE"; break;
        case 1:
            COLOR += "VERT"; break;
        case 2:
            COLOR += "BLEU"; break;
        case 3:
            COLOR += "JAUNE"; break;
        case 4:
            COLOR += "BLANC"; break;
        case 5:
            COLOR += "NOIR"; break;
        case 6:
            COLOR += "GRIS"; break;
        case 7:
            COLOR += "ORANGE"; break;
        default:
            COLOR += "NONE";
    }
    string outputC = output + CATEGORY + COLOR + "\n" + "\n";
    //cout<<outputC;
    return outputC;
}