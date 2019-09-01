//
// Created by MAC on 2019/5/31.
//

#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>

using namespace std;

#include "Purchase_DP.h"
#include "Houseware.h"
#include "Clothing.h"
#include "Food.h"
#include "Drink.h"


bool Purchase_DP::compareDate(Date date)
{
    bool perime = false;

    if (today.annee > date.annee)
        perime = true;
    else if (today.annee == date.annee)
    {
        if (today.moi > date.moi)
            perime = true;
        else if (today.moi == date.moi)
        {
            if (today.jour > date.jour)
                perime = true;
        }
    }
    return perime;
}
void Purchase_DP::clearPerishables()
{
    vector<Houseware>::iterator itclearH;
    vector<Clothing>::iterator itclearC;
    vector<Food>::iterator itclearF;
    vector<Drink>::iterator itclearD;
    int count = 0;
    for (itclearH = H.begin(); itclearH != H.end(); itclearH++)
    {
        if (compareDate(H[count].getDateConsomme()))
        {
            H.erase(itclearH);
            break;
        }
        count++;
    }

    count = 0;
    for (itclearC = C.begin(); itclearC != C.end(); itclearC++)
    {
        if (compareDate(C[count].getDateConsomme()))
        {
            C.erase(itclearC);
            break;
        }
        count++;
    }

    count = 0;
    for (itclearF = F.begin(); itclearF != F.end(); itclearF++)
    {
        if (compareDate(F[count].getDateConsomme()))
        {
            F.erase(itclearF);
            break;
        }
        count++;
    }

    count = 0;
    for (itclearD = D.begin(); itclearD != D.end(); itclearD++)
    {
        if (compareDate(D[count].getDateConsomme()))
        {
            D.erase(itclearD);
            break;
        }
        count++;
    }
}

Purchase_DP::Purchase_DP()
{
    time_t now = time(0);
    tm* TN = gmtime(&now);
    today = {TN->tm_mday, 1 + TN->tm_mon, 1900 + TN->tm_year};
}
Color Purchase_DP::chooseColor(string colort)
{
    Color color;
    if (colort == "RED")
        color = RED;
    else if (colort == "GREEN")
        color = GREEN;
    else if (colort == "BLUE")
        color = BLUE;
    else if (colort == "YELLOW")
        color = YELLOW;
    else if (colort == "BLACK")
        color = BLACK;
    else if (colort == "WHITE")
        color = WHITE;
    else if (colort == "GREY")
        color = GREY;
    else if (colort == "ORANGE")
        color = ORANGE;
    else
        color = WRONGCOLOR;
    return color;
}
void Purchase_DP::ReadList()
{
    string numero, categorie, marque, nom, colortemps;
    Date date{00, 00, 0000};
    int num;
    float cot, prix;
    Color color;
    bool frais;
    float volu;
    bool finished;

    ifstream fileIN;
    fileIN.open("/Users/mac/Desktop/après/C++/Leader Price/Houseware.txt");
    if (!fileIN)
        cout<<"erreur lecture!"<<endl;
    finished = false;
    while(!finished)
    {
        fileIN>>numero>>marque>>date.jour>>date.moi>>date.annee>>nom>>num>>cot>>prix>>categorie;
        Houseware Htemps(numero, marque, date, nom, num, cot, prix, categorie);
        if (!fileIN.eof())
            H.push_back(Htemps);
        else
            finished = true;
    }
    fileIN.close();


    fileIN.open("/Users/mac/Desktop/après/C++/Leader Price/Clothing.txt");
    if (!fileIN)
        cout<<"erreur lecture!"<<endl;
    finished = false;
    while(!finished)
    {
        fileIN>>numero>>marque>>date.jour>>date.moi>>date.annee>>nom>>num>>cot>>prix>>categorie>>colortemps;
        color = chooseColor(colortemps);
        Clothing Ctemps(numero, marque, date, nom, num, cot, prix, categorie, color);
        if (!fileIN.eof())
            C.push_back(Ctemps);
        else
            finished = true;
    }
    fileIN.close();


    fileIN.open("/Users/mac/Desktop/après/C++/Leader Price/Food.txt");
    if (!fileIN)
        cout<<"erreur lecture!"<<endl;
    finished = false;
    while(!finished)
    {
        fileIN>>numero>>marque>>date.jour>>date.moi>>date.annee>>nom>>num>>cot>>prix>>categorie>>frais;
        Food Ftemps(numero, marque, date, nom, num, cot, prix, categorie, frais);
        if (!fileIN.eof())
            F.push_back(Ftemps);
        else
            finished = true;
    }
    fileIN.close();


    fileIN.open("/Users/mac/Desktop/après/C++/Leader Price/Drink.txt");
    if (!fileIN)
        cout<<"erreur lecture!"<<endl;
    finished = false;
    while(!finished)
    {
        fileIN>>numero>>marque>>date.jour>>date.moi>>date.annee>>nom>>num>>cot>>prix>>categorie>>volu;
        Drink Dtemps(numero, marque, date, nom, num, cot, prix, categorie, volu);
        if (!fileIN.eof())
            D.push_back(Dtemps);
        else
            finished = true;
    }
    fileIN.close();

    clearPerishables();
}


vector<Houseware> Purchase_DP::getHouseware() { return H; }
vector<Clothing> Purchase_DP::getClothing() { return C; }
vector<Food> Purchase_DP::getFood() { return F; }
vector<Drink> Purchase_DP::getDrink() { return D; }



