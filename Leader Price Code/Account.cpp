//
// Created by MAC on 2019/6/6.
//

#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>

#include <QApplication>
#include <QMainWindow>
#include <QString>
#include <QLineEdit>
#include <QTextEdit>
#include <QInputDialog>
#include <QLabel>
#include <QPushButton>
#include <QMenuBar>
#include <QMessageBox>
#include <QFormLayout>
#include <QSpinBox>
#include <QDialogButtonBox>
#include <QRadioButton>
#include <QTextBrowser>
#include <QGroupBox>
#include <QCheckBox>
#include <QToolBar>

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

int AccountManager::pop_up(string title, string output)
{
    QTextBrowser *showText = new QTextBrowser;
    showText->setText(QString::fromStdString(output));
    showText->setWindowTitle(QString::fromStdString(title));
    showText->show();
}
Color AccountManager::chooseColor(string colort)
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
vector<Houseware> AccountManager::minusH()
{
    vector<Houseware> vecH1 = H;
    vector<Houseware> vecH2 = soldH;
    vector<Houseware>::iterator itH1, itH2;
    int countH1 = 0;
    for (itH1 = vecH1.begin(); itH1 != vecH1.end(); itH1++)
    {
        int countH2 = 0;
        for (itH2 = vecH2.begin(); itH2 != vecH2.end(); itH2++)
        {
            if (vecH1[countH1].getCode() == vecH2[countH2].getCode()) //有时操作失误，仓库盒子销售后才手动增减，会导致仓库盒子没有售出盒子中的商品。此时无所谓，存货中本应清零，但已经没有
            {
                if (vecH1[countH1].getNumber() <= vecH2[countH2].getNumber())  //有时操作失误，仓库盒子销售后才手动增减，会导致仓库盒子的某商品比售出盒子少，此时应当清零
                    vecH1.erase(itH1);
                else if (vecH1[countH1].getNumber() > vecH2[countH2].getNumber())
                    vecH1[countH1].modifyNumber(vecH2[countH2].getNumber(), false);
                break;
            }  //有特殊情况，手动删除或保质期过删除之后结果卖出怎么办，需要报错
            countH2++;
        }
        countH1++;
    }
    return vecH1;
}

vector<Clothing> AccountManager::minusC()
{
    vector<Clothing> vecC1 = C;
    vector<Clothing> vecC2 = soldC;
    vector<Clothing>::iterator itC1, itC2;
    int countC1 = 0;
    for (itC1 = vecC1.begin(); itC1 != vecC1.end(); itC1++)
    {
        int countC2 = 0;
        for (itC2 = vecC2.begin(); itC2 != vecC2.end(); itC2++)
        {
            if (vecC1[countC1].getCode() == vecC2[countC2].getCode())
            {
                if (vecC1[countC1].getNumber() <= vecC2[countC2].getNumber())
                    vecC1.erase(itC1);
                else
                    vecC1[countC1].modifyNumber(vecC2[countC2].getNumber(), false);
                break;  //此处不可能售出盒子中包含仓库盒子中没有的商品，因此没有特殊情况
            }
            countC2++;
        }
        countC1++;
    }
    return vecC1;
}

vector<Food> AccountManager::minusF()
{
    vector<Food> vecF1 = F;
    vector<Food> vecF2 = soldF;
    vector<Food>::iterator itF1, itF2;
    int countF1 = 0;
    for (itF1 = vecF1.begin(); itF1 != vecF1.end(); itF1++)
    {
        int countF2 = 0;
        for (itF2 = vecF2.begin(); itF2 != vecF2.end(); itF2++)
        {
            if (vecF1[countF1].getCode() == vecF2[countF2].getCode())
            {
                if (vecF1[countF1].getNumber() <= vecF2[countF2].getNumber())
                    vecF1.erase(itF1);
                else
                    vecF1[countF1].modifyNumber(vecF2[countF2].getNumber(), false);
                break;  //此处不可能售出盒子中包含仓库盒子中没有的商品，因此没有特殊情况
            }
            countF2++;
        }
        countF1++;
    }
    return vecF1;
}

vector<Drink> AccountManager::minusD()
{
    vector<Drink> vecD1 = D;
    vector<Drink> vecD2 = soldD;
    vector<Drink>::iterator itD1, itD2;
    int countD1 = 0;
    for (itD1 = vecD1.begin(); itD1 != vecD1.end(); itD1++)
    {
        int countD2 = 0;
        for (itD2 = vecD2.begin(); itD2 != vecD2.end(); itD2++)
        {
            if (vecD1[countD1].getCode() == vecD2[countD2].getCode())
            {
                if (vecD1[countD1].getNumber() <= vecD2[countD2].getNumber())
                    vecD1.erase(itD1);
                else
                    vecD1[countD1].modifyNumber(vecD2[countD2].getNumber(), false);
                break;  //此处不可能售出盒子中包含仓库盒子中没有的商品，因此没有特殊情况
            }
            countD2++;
        }
        countD1++;
    }
    return vecD1;
}

void AccountManager::modifyFileMerchandise()
{
    vector<Houseware> BoxTempsH;
    vector<Clothing> BoxTempsC;
    vector<Food> BoxTempsF;
    vector<Drink> BoxTempsD;
    vector<Houseware>::iterator iterBoxTempsH;
    vector<Clothing>::iterator iterBoxTempsC;
    vector<Food>::iterator iterBoxTempsF;
    vector<Drink>::iterator iterBoxTempsD;
    int count = 0;

    string code, brand, name, category, color;
    int day, month, year, num;
    float cost, price, volume;
    Color colorTemps;
    bool fresh;
    //清空，然后输入accountmanager中仓库盒子与Soldbox的差

    BoxTempsH = minusH();
    BoxTempsC = minusC();
    BoxTempsF = minusF();
    BoxTempsD = minusD();

    fstream fileEmpty;
    fileEmpty.open("/Users/mac/Desktop/après/C++/Leader Price/Houseware.txt", ios::out);
    fileEmpty.close();
    for (iterBoxTempsH = BoxTempsH.begin(); iterBoxTempsH != BoxTempsH.end(); iterBoxTempsH++)
    {
        code = BoxTempsH[count].getCode();
        brand = BoxTempsH[count].getBrand();
        day = BoxTempsH[count].getDateConsomme().jour;
        month = BoxTempsH[count].getDateConsomme().moi;
        year = BoxTempsH[count].getDateConsomme().annee;
        name = BoxTempsH[count].getName();
        num =  BoxTempsH[count].getNumber();
        cost = BoxTempsH[count].getCost();
        price = BoxTempsH[count].getPrice();
        category = BoxTempsH[count].getCate();

        ofstream fileOUT("/Users/mac/Desktop/après/C++/Leader Price/Houseware.txt", ios::app);
        fileOUT<<code<<"  "<<brand<<"  "<<day<<" "<<month<<" "<<year<<"  "<<name<<"  "<<num<<"  "<<cost<<"  "<<price<<"  "<<category<<"\n";
        fileOUT.close();
        count++;
    }

    count = 0;
    fileEmpty.open("/Users/mac/Desktop/après/C++/Leader Price/Clothing.txt", ios::out);
    fileEmpty.close();
    for (iterBoxTempsC = BoxTempsC.begin(); iterBoxTempsC != BoxTempsC.end(); iterBoxTempsC++)
    {
        code = BoxTempsC[count].getCode();
        brand = BoxTempsC[count].getBrand();
        day = BoxTempsC[count].getDateConsomme().jour;
        month = BoxTempsC[count].getDateConsomme().moi;
        year = BoxTempsC[count].getDateConsomme().annee;
        name = BoxTempsC[count].getName();
        num =  BoxTempsC[count].getNumber();
        cost = BoxTempsC[count].getCost();
        price = BoxTempsC[count].getPrice();
        category = BoxTempsC[count].getCate();
        colorTemps = BoxTempsC[count].getColor();
        switch (colorTemps)
        {
            case RED: color = "RED";
                break;
            case GREEN: color = "GREEN";
                break;
            case BLUE: color = "BLUE";
                break;
            case YELLOW: color = "YELLOW";
                break;
            case WHITE: color = "WHITE";
                break;
            case BLACK: color = "BLACK";
                break;
            case GREY: color = "GREY";
                break;
            case ORANGE: color = "ORANGE";
                break;
            case WRONGCOLOR: color = "WRONGCOLOR";
                break;
        }

        ofstream fileOUT("/Users/mac/Desktop/après/C++/Leader Price/Clothing.txt", ios::app);
        fileOUT<<code<<"  "<<brand<<"  "<<day<<" "<<month<<" "<<year<<"  "<<name<<"  "<<num<<"  "<<cost<<"  "<<price<<"  "<<category<<"  "<<color<<"\n";
        fileOUT.close();
        count++;
    }

    count = 0;
    fileEmpty.open("/Users/mac/Desktop/après/C++/Leader Price/Food.txt", ios::out);
    fileEmpty.close();
    for (iterBoxTempsF = BoxTempsF.begin(); iterBoxTempsF != BoxTempsF.end(); iterBoxTempsF++)
    {
        code = BoxTempsF[count].getCode();
        brand = BoxTempsF[count].getBrand();
        day = BoxTempsF[count].getDateConsomme().jour;
        month = BoxTempsF[count].getDateConsomme().moi;
        year = BoxTempsF[count].getDateConsomme().annee;
        name = BoxTempsF[count].getName();
        num =  BoxTempsF[count].getNumber();
        cost = BoxTempsF[count].getCost();
        price = BoxTempsF[count].getPrice();
        category = BoxTempsF[count].getCate();
        fresh = BoxTempsF[count].FreshOrNot();

        ofstream fileOUT("/Users/mac/Desktop/après/C++/Leader Price/Food.txt", ios::app);
        fileOUT<<code<<"  "<<brand<<"  "<<day<<" "<<month<<" "<<year<<"  "<<name<<"  "<<num<<"  "<<cost<<"  "<<price<<"  "<<category<<"  "<<fresh<<"\n";
        fileOUT.close();
        count++;
    }

    count = 0;
    fileEmpty.open("/Users/mac/Desktop/après/C++/Leader Price/Drink.txt", ios::out);
    fileEmpty.close();
    for (iterBoxTempsD = BoxTempsD.begin(); iterBoxTempsD != BoxTempsD.end(); iterBoxTempsD++)
    {
        code = BoxTempsD[count].getCode();
        brand = BoxTempsD[count].getBrand();
        day = BoxTempsD[count].getDateConsomme().jour;
        month = BoxTempsD[count].getDateConsomme().moi;
        year = BoxTempsD[count].getDateConsomme().annee;
        name = BoxTempsD[count].getName();
        num =  BoxTempsD[count].getNumber();
        cost = BoxTempsD[count].getCost();
        price = BoxTempsD[count].getPrice();
        category = BoxTempsD[count].getCate();
        volume = BoxTempsD[count].getVolume();

        ofstream fileOUT("/Users/mac/Desktop/après/C++/Leader Price/Drink.txt", ios::app);
        fileOUT<<code<<"  "<<brand<<"  "<<day<<" "<<month<<" "<<year<<"  "<<name<<"  "<<num<<"  "<<cost<<"  "<<price<<"  "<<category<<"  "<<volume<<"\n";
        fileOUT.close();
        count++;
    }
}


AccountManager::AccountManager(string prenom, string nom, string password, int nb)
{
    Firstname = prenom;
    Lastname = nom;
    Password = password;
    workingNum = nb;

    time_t now = time(0);
    tm* TN = gmtime(&now);
    today = {TN->tm_mday, 1 + TN->tm_mon, 1900 + TN->tm_year};
}
AccountManager::AccountManager()
{
    time_t now = time(0);
    tm* TN = gmtime(&now);
    today = {TN->tm_mday, 1 + TN->tm_mon, 1900 + TN->tm_year};
}


void AccountManager::afficher()
{
    string output;
    stringstream convert;
    convert<<workingNum;
    string worknumfinal = convert.str();
    output += "Firstname: " + Firstname + "\n";
    output += "Lastname: " + Lastname + "\n";
    output += "Working Number: " + worknumfinal + "\n";
    pop_up("我的个人信息", output);
}
int AccountManager::getWorkingNumber() { return workingNum; }
string AccountManager::getPassword() { return Password; }
int AccountManager::getNbHouseware() { return nbHouseware; }
int AccountManager::getNbClothing() { return nbClothing; }
int AccountManager::getNbFood() { return nbFood; }
int AccountManager::getNbDrink() { return nbDrink; }

void AccountManager::getOrder()
{
    Purchase_DP P;
    P.ReadList();

    while (nbHouseware < P.getHouseware().size())
    {
        H.push_back(P.getHouseware()[nbHouseware]);
        nbHouseware++;
    }

    while  (nbClothing < P.getClothing().size())
    {
        C.push_back(P.getClothing()[nbClothing]);
        nbClothing++;
    }

    while  (nbFood < P.getFood().size())
    {
        F.push_back(P.getFood()[nbFood]);
        nbFood++;
    }

    while  (nbDrink < P.getDrink().size())
    {
        D.push_back(P.getDrink()[nbDrink]);
        nbDrink++;
    }
}
void AccountManager::pickSoldBoxs(vector<Houseware> H_fromManager, vector<Clothing> C_fromManager, vector<Food> F_fromManager, vector<Drink> D_fromManager)
{
    soldH = H_fromManager;
    soldC = C_fromManager;
    soldF = F_fromManager;
    soldD = D_fromManager;
}
void AccountManager::afficherBoxsVendu()
{
    vector<Houseware>::iterator itH;
    vector<Clothing>::iterator itC;
    vector<Food>::iterator itF;
    vector<Drink>::iterator itD;
    int i;
    i = 0;
    for (itH = soldH.begin(); itH != soldH.end(); itH++)
    {
        soldH[i].afficher();
        i++;
    }
    i = 0;
    for (itC = soldC.begin(); itC != soldC.end(); itC++)
    {
        soldC[i].afficher();
        i++;
    }
    i = 0;
    for (itF = soldF.begin(); itF != soldF.end(); itF++)
    {
        soldF[i].afficher();
        i++;
    }
    i = 0;
    for (itD = soldD.begin(); itD != soldD.end(); itD++)
    {
        soldD[i].afficher();
        i++;
    }
}


void AccountManager::afficherInfoHouseware(string code)
{
    vector<Houseware>::iterator iterSearchH;
    int searchH = 0;
    string show;
    for (iterSearchH = H.begin(); iterSearchH != H.end(); iterSearchH++)
    {
        if (code == H[searchH].getCode())
        {
            show = H[searchH].afficher();
            pop_up("展示Houseware信息", show);
            break;
        }
        searchH++;
    }
    if (searchH == H.size())
        pop_up("提示", "该商品不存在！");
}
void AccountManager::affichertInfoClothing(string code)
{
    vector<Clothing>::iterator iterSearchC;
    int searchC = 0;
    string show;
    for (iterSearchC = C.begin(); iterSearchC != C.end(); iterSearchC++)
    {
        if (code == C[searchC].getCode())
        {
            show = C[searchC].afficher();
            pop_up("展示Clothing信息", show);
            break;
        }
        searchC++;
    }
    if (searchC == C.size())
        pop_up("提示", "该商品不存在！");
}
void AccountManager::afficherInfoFood(string code)
{
    vector<Food>::iterator iterSearchF;
    int searchF = 0;
    string show;
    for (iterSearchF = F.begin(); iterSearchF != F.end(); iterSearchF++)
    {
        if (code == F[searchF].getCode())
        {
            show = F[searchF].afficher();
            pop_up("展示Food信息", show);
            break;
        }
        searchF++;
    }
    if (iterSearchF == F.end())
        pop_up("提示", "该商品不存在！");
}
void AccountManager::afficherInfoDrink(string code)
{
    vector<Drink>::iterator iterSearchD;
    int searchD = 0;
    string show;
    for (iterSearchD = D.begin(); iterSearchD != D.end(); iterSearchD++)
    {
        if (code == D[searchD].getCode())
        {
            show = D[searchD].afficher();
            pop_up("展示Drink信息", show);
            break;
        }
        searchD++;
    }
    if (iterSearchD == D.end())
        pop_up("提示", "该商品不存在！");
}



void AccountManager::showAll()
{
    int countMerchandise = 0;
    string output;

    output += "\nAfficher tous les Housewares: \n\n";
    vector<Houseware>::iterator iterH;
    //cout<<"Afficher tous les Housewares: "<<endl<<endl;
    for (iterH = H.begin(); iterH != H.end(); iterH++)
    {
        output += H[countMerchandise].afficher();
        countMerchandise++;
    }

    countMerchandise = 0;
    output += "\nAfficher tous les Clothings: \n\n";
    vector<Clothing>::iterator iterC;
    //cout<<"Afficher tous les Clothings: "<<endl<<endl;
    for (iterC = C.begin(); iterC != C.end(); iterC++)
    {
        output += C[countMerchandise].afficher();
        countMerchandise++;
    }

    countMerchandise = 0;
    output += "\nAfficher tous les Foods: \n\n";
    vector<Food>::iterator iterF;
    //cout<<"Afficher tous les Foods: "<<endl<<endl;
    for (iterF = F.begin(); iterF != F.end(); iterF++)
    {
        output += F[countMerchandise].afficher();
        countMerchandise++;
    }

    countMerchandise = 0;
    output += "\nAfficher tous les Drinks: \n\n";
    vector<Drink>::iterator iterD;
    //cout<<"Afficher tous les Drinks: "<<endl<<endl;
    for (iterD = D.begin(); iterD != D.end(); iterD++)
    {
        output += D[countMerchandise].afficher();
        countMerchandise++;
    }
    //cout<<output;
    string title("我的仓库");
    pop_up(title, output);
}
string AccountManager::showToday()
{
    time_t now = time(0);
    return ctime(&now);
}


void AccountManager::addHousewareManually()
{
    string code, brand, name, category;
    int day, month, year, num;
    float cost, price;
    string prompt = "Please put in a Houseware in the format as follow: \n";

    //cout<<"Please put in a Houseware in the format as follow: "<<endl;
    //cout<<"code, brand, day, month, year, name, number, cost, price, category"<<endl<<endl;
    //cin>>code>>brand>>day>>month>>year>>name>>num>>cost>>price>>category;
    QDialog *dialogADD = new QDialog;
    QFormLayout form(dialogADD);
    QLineEdit *inputcode = new QLineEdit;
    QLineEdit *inputbrand = new QLineEdit;
    QLineEdit *inputday = new QLineEdit;
    inputday->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    QLineEdit *inputmonth = new QLineEdit;
    inputmonth->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    QLineEdit *inputyear = new QLineEdit;
    inputyear->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    QLineEdit *inputname = new QLineEdit;
    QLineEdit *inputnum = new QLineEdit;
    inputnum->setValidator(new QRegExpValidator(QRegExp("[0-9]+$+.")));
    QLineEdit *inputcost = new QLineEdit;
    inputcost->setValidator(new QRegExpValidator(QRegExp("[0-9]+([.]{1}[0-9]+)$")));
    QLineEdit *inputprice = new QLineEdit;
    inputprice->setValidator(new QRegExpValidator(QRegExp("[0-9]+([.]{1}[0-9]+)$")));
    QLineEdit *inputcategory = new QLineEdit;
    dialogADD->setWindowTitle(QString::fromStdString("添加Houseware"));
    form.setObjectName(QString::fromStdString(prompt));
    form.addRow(QString::fromStdString("请输入商品码code: "), inputcode);
    form.addRow(QString::fromStdString("请输入品牌brand: "), inputbrand);
    form.addRow(QString::fromStdString("请输入天day: "), inputday);
    form.addRow(QString::fromStdString("请输入月month: "), inputmonth);
    form.addRow(QString::fromStdString("请输入年year: "), inputyear);
    form.addRow(QString::fromStdString("请输入名称name: "), inputname);
    form.addRow(QString::fromStdString("请输入数目num: "), inputnum);
    form.addRow(QString::fromStdString("请输入成本cost: "), inputcost);
    form.addRow(QString::fromStdString("请输入售价price: "), inputprice);
    form.addRow(QString::fromStdString("请输入品类category: "), inputcategory);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, dialogADD);  //Qt::Horizonta横向排列按钮
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), dialogADD, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), dialogADD, SLOT(reject()));
    dialogADD->exec();

    code = string((const char*)inputcode->text().toLocal8Bit());
    brand = string((const char*)inputbrand->text().toLocal8Bit());
    day = inputday->text().toInt();
    month = inputmonth->text().toInt();
    year = inputyear->text().toInt();
    name = string((const char*)inputname->text().toLocal8Bit());
    num = inputnum->text().toInt();
    cost = inputcost->text().toFloat();
    price = inputprice->text().toFloat();
    category = string((const char*)inputcategory->text().toLocal8Bit());

    Date dateTemps{day, month, year};
    Houseware addHouseware(code, brand, dateTemps, name, num, cost, price, category);
    vector<Houseware>::iterator itH;
    int count = 0;
    bool success = true;
    for (itH = H.begin(); itH != H.end(); itH++)
    {
        if (H[count].getCode() == code)
        {
            H[count].modifyNumber(num, true);
            success = false;
            pop_up("提示", "成功添加！");
            break;
        }
        count++;
    }
    if (success)
    {
        H.push_back(addHouseware);
        pop_up("提示", "成功添加！");
    }
    //showAll();
}
void AccountManager::addClothingManually()
{
    string code, brand, name, category, colort;
    int day, month, year, num;
    float cost, price;

    string prompt = "Please put in a Clothing in the format as follow: ";
    QDialog *dialogADD = new QDialog;
    QFormLayout form(dialogADD);
    QLineEdit *inputcode = new QLineEdit;
    QLineEdit *inputbrand = new QLineEdit;
    QLineEdit *inputday = new QLineEdit;
    inputday->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    QLineEdit *inputmonth = new QLineEdit;
    inputmonth->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    QLineEdit *inputyear = new QLineEdit;
    inputyear->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    QLineEdit *inputname = new QLineEdit;
    QLineEdit *inputnum = new QLineEdit;
    inputnum->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    QLineEdit *inputcost = new QLineEdit;
    inputcost->setValidator(new QRegExpValidator(QRegExp("[0-9]+([.]{1}[0-9]+)$")));
    QLineEdit *inputprice = new QLineEdit;
    inputprice->setValidator(new QRegExpValidator(QRegExp("[0-9]+([.]{1}[0-9]+)$")));
    QLineEdit *inputcategory = new QLineEdit;
    QLineEdit *inputcolort = new QLineEdit;
    dialogADD->setWindowTitle(QString::fromStdString("添加Clothing"));
    form.setObjectName(QString::fromStdString(prompt));
    form.addRow(QString::fromStdString("请输入商品码code: "), inputcode);
    form.addRow(QString::fromStdString("请输入品牌brand: "), inputbrand);
    form.addRow(QString::fromStdString("请输入天day: "), inputday);
    form.addRow(QString::fromStdString("请输入月month: "), inputmonth);
    form.addRow(QString::fromStdString("请输入年year: "), inputyear);
    form.addRow(QString::fromStdString("请输入名称name: "), inputname);
    form.addRow(QString::fromStdString("请输入数目num: "), inputnum);
    form.addRow(QString::fromStdString("请输入成本cost: "), inputcost);
    form.addRow(QString::fromStdString("请输入售价price: "), inputprice);
    form.addRow(QString::fromStdString("请输入品类category: "), inputcategory);
    form.addRow(QString::fromStdString("请输入颜色color（大写）"), inputcolort);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, dialogADD);  //Qt::Horizonta横向排列按钮
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), dialogADD, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), dialogADD, SLOT(reject()));
    dialogADD->exec();

    code = string((const char*)inputcode->text().toLocal8Bit());
    brand = string((const char*)inputbrand->text().toLocal8Bit());
    day = inputday->text().toInt();
    month = inputmonth->text().toInt();
    year = inputyear->text().toInt();
    name = string((const char*)inputname->text().toLocal8Bit());
    num = inputnum->text().toInt();
    cost = inputcost->text().toFloat();
    price = inputprice->text().toFloat();
    category = string((const char*)inputcategory->text().toLocal8Bit());
    colort = string((const char*)inputcolort->text().toLocal8Bit());

    Date dateTemps{day, month, year};
    Color color = chooseColor(colort);
    Clothing addClothing(code, brand, dateTemps, name, num, cost, price, category, color);
    vector<Clothing>::iterator itC;
    int count = 0;
    bool success = true;
    for (itC = C.begin(); itC != C.end(); itC++)
    {
        if (C[count].getCode() == code)
        {
            C[count].modifyNumber(num, true);
            success = false;
            pop_up("提示", "成功添加！");
            break;
        }
        count++;
    }
    if (success)
    {
        C.push_back(addClothing);
        pop_up("提示", "成功添加！");
    }
}
void AccountManager::addFoodManually()
{
    string code, brand, name, category;
    int day, month, year, num;
    float cost, price;
    bool fresh;

    string prompt = "Please put in a Food in the format as follow: ";
    QDialog *dialogADD = new QDialog;
    QFormLayout form(dialogADD);
    QLineEdit *inputcode = new QLineEdit;
    QLineEdit *inputbrand = new QLineEdit;
    QLineEdit *inputday = new QLineEdit;
    inputday->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    QLineEdit *inputmonth = new QLineEdit;
    inputmonth->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    QLineEdit *inputyear = new QLineEdit;
    inputyear->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    QLineEdit *inputname = new QLineEdit;
    QLineEdit *inputnum = new QLineEdit;
    inputnum->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    QLineEdit *inputcost = new QLineEdit;
    inputcost->setValidator(new QRegExpValidator(QRegExp("[0-9]+([.]{1}[0-9]+)$")));
    QLineEdit *inputprice = new QLineEdit;
    inputprice->setValidator(new QRegExpValidator(QRegExp("[0-9]+([.]{1}[0-9]+)$")));
    QLineEdit *inputcategory = new QLineEdit;
    QRadioButton *inputfresh = new QRadioButton;
    dialogADD->setWindowTitle(QString::fromStdString("添加Food"));
    form.setObjectName(QString::fromStdString(prompt));
    form.addRow(QString::fromStdString("请输入商品码code: "), inputcode);
    form.addRow(QString::fromStdString("请输入品牌brand: "), inputbrand);
    form.addRow(QString::fromStdString("请输入天day: "), inputday);
    form.addRow(QString::fromStdString("请输入月month: "), inputmonth);
    form.addRow(QString::fromStdString("请输入年year: "), inputyear);
    form.addRow(QString::fromStdString("请输入名称name: "), inputname);
    form.addRow(QString::fromStdString("请输入数目num: "), inputnum);
    form.addRow(QString::fromStdString("请输入成本cost: "), inputcost);
    form.addRow(QString::fromStdString("请输入售价price: "), inputprice);
    form.addRow(QString::fromStdString("请输入品类category: "), inputcategory);
    form.addRow(QString::fromStdString("请输入是否新鲜fresh: "), inputfresh);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, dialogADD);  //Qt::Horizonta横向排列按钮
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), dialogADD, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), dialogADD, SLOT(reject()));
    dialogADD->exec();

    code = string((const char*)inputcode->text().toLocal8Bit());
    brand = string((const char*)inputbrand->text().toLocal8Bit());
    day = inputday->text().toInt();
    month = inputmonth->text().toInt();
    year = inputyear->text().toInt();
    name = string((const char*)inputname->text().toLocal8Bit());
    num = inputnum->text().toInt();
    cost = inputcost->text().toFloat();
    price = inputprice->text().toFloat();
    category = string((const char*)inputcategory->text().toLocal8Bit());
    fresh = inputfresh->isChecked();

    Date dateTemps{day, month, year};
    Food addFood(code, brand, dateTemps, name, num, cost, price, category, fresh);
    vector<Food>::iterator itF;
    int count = 0;
    bool success = true;
    for (itF = F.begin(); itF != F.end(); itF++)
    {
        if (F[count].getCode() == code)
        {
            F[count].modifyNumber(num, true);
            success = false;
            pop_up("提示", "成功添加！");
            break;
        }
        count++;
    }
    if (success)
    {
        F.push_back(addFood);
        pop_up("提示", "成功添加！");
    }
}
void AccountManager::addDrinkManually()
{
    string code, brand, name, category;
    int day, month, year, num;
    float cost, price, volume;

    string prompt = "Please put in a Drink in the format as follow: ";
    QDialog *dialogADD = new QDialog;
    QFormLayout form(dialogADD);
    QLineEdit *inputcode = new QLineEdit;
    QLineEdit *inputbrand = new QLineEdit;
    QLineEdit *inputday = new QLineEdit;
    inputday->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    QLineEdit *inputmonth = new QLineEdit;
    inputmonth->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    QLineEdit *inputyear = new QLineEdit;
    inputyear->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    QLineEdit *inputname = new QLineEdit;
    QLineEdit *inputnum = new QLineEdit;
    inputnum->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    QLineEdit *inputcost = new QLineEdit;
    inputcost->setValidator(new QRegExpValidator(QRegExp("[0-9]+([.]{1}[0-9]+)$")));
    QLineEdit *inputprice = new QLineEdit;
    inputprice->setValidator(new QRegExpValidator(QRegExp("[0-9]+([.]{1}[0-9]+)$")));
    QLineEdit *inputcategory = new QLineEdit;
    QLineEdit *inputvolume = new QLineEdit;
    inputvolume->setValidator(new QRegExpValidator(QRegExp("[0-9]+$+.")));
    dialogADD->setWindowTitle(QString::fromStdString("添加Houseware"));
    form.setObjectName(QString::fromStdString(prompt));
    form.addRow(QString::fromStdString("请输入商品码code: "), inputcode);
    form.addRow(QString::fromStdString("请输入品牌brand: "), inputbrand);
    form.addRow(QString::fromStdString("请输入天day: "), inputday);
    form.addRow(QString::fromStdString("请输入月month: "), inputmonth);
    form.addRow(QString::fromStdString("请输入年year: "), inputyear);
    form.addRow(QString::fromStdString("请输入名称name: "), inputname);
    form.addRow(QString::fromStdString("请输入数目num: "), inputnum);
    form.addRow(QString::fromStdString("请输入成本cost: "), inputcost);
    form.addRow(QString::fromStdString("请输入售价price: "), inputprice);
    form.addRow(QString::fromStdString("请输入品类category: "), inputcategory);
    form.addRow(QString::fromStdString("请输入容量volume: "), inputvolume);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, dialogADD);  //Qt::Horizonta横向排列按钮
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), dialogADD, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), dialogADD, SLOT(reject()));
    dialogADD->exec();

    code = string((const char*)inputcode->text().toLocal8Bit());
    brand = string((const char*)inputbrand->text().toLocal8Bit());
    day = inputday->text().toInt();
    month = inputmonth->text().toInt();
    year = inputyear->text().toInt();
    name = string((const char*)inputname->text().toLocal8Bit());
    num = inputnum->text().toInt();
    cost = inputcost->text().toFloat();
    price = inputprice->text().toFloat();
    category = string((const char*)inputcategory->text().toLocal8Bit());
    volume = inputvolume->text().toFloat();

    Date dateTemps{day, month, year};
    Drink addDrink(code, brand, dateTemps, name, num, cost, price, category, volume);
    vector<Drink>::iterator itD;
    int count = 0;
    bool success = true;
    for (itD = D.begin(); itD != D.end(); itD++)
    {
        if (D[count].getCode() == code)
        {
            D[count].modifyNumber(num, true);
            success = false;
            pop_up("提示", "成功添加！");
            break;
        }
        count++;
    }
    if (success)
    {
        D.push_back(addDrink);
        pop_up("提示", "成功添加！");
    }
}

void AccountManager::removeHousewareManually(string code, int num)
{
    vector<Houseware>::iterator iterSearchH;
    int searchH = 0;
    bool remove = false;
    for (iterSearchH = H.begin(); iterSearchH != H.end(); iterSearchH++)
    {
        if (code == H[searchH].getCode())
        {
            if (H[searchH].getNumber() == num)
            {
                H.erase(iterSearchH);
                remove = true;
                break;
            }
            else if (H[searchH].getNumber() > num)
            {
                H[searchH].modifyNumber(num, false);
                remove = true;
                break;
            }
            else
            {
                pop_up("提示", "输入数目过大！");
                remove = true;
                break;
            }
        }
        searchH++;
    }
    if (!remove)
        pop_up("提示", "该商品不存在！");
}
void AccountManager::removeClothingManually(string code, int num)
{
    vector<Clothing>::iterator iterSearchC;
    int searchC = 0;
    bool remove = false;
    for (iterSearchC = C.begin(); iterSearchC != C.end(); iterSearchC++)
    {
        if (code == C[searchC].getCode())
        {
            if (C[searchC].getNumber() == num)
            {
                C.erase(iterSearchC);
                remove = true;
                break;
            }
            else if (C[searchC].getNumber() > num)
            {
                C[searchC].modifyNumber(num, false);
                remove = true;
                break;
            }
            else
            {
                pop_up("提示", "输入数目过大！");
                remove = true;
                break;
            }
        }
        searchC++;
    }
    if (!remove)
        pop_up("提示", "该商品不存在！");
}
void AccountManager::removeFoodManually(string code, int num)
{
    vector<Food>::iterator iterSearchF;
    int searchF = 0;
    bool remove = false;
    for (iterSearchF = F.begin(); iterSearchF != F.end(); iterSearchF++)
    {
        if (code == F[searchF].getCode())
        {
            if (F[searchF].getNumber() == num)
            {
                F.erase(iterSearchF);
                remove = true;
                break;
            }
            else if (F[searchF].getNumber() > num)
            {
                F[searchF].modifyNumber(num, false);
                remove = true;
                break;
            }
            else
            {
                pop_up("提示", "输入数目过大！");
                remove = true;
                break;
            }
        }
        searchF++;
    }
    if (!remove)
        pop_up("提示", "该商品不存在！");
}
void AccountManager::removeDrinkManually(string code, int num)
{
    vector<Drink>::iterator iterSearchD;
    int searchD = 0;
    bool remove = false;
    for (iterSearchD = D.begin(); iterSearchD != D.end(); iterSearchD++)
    {
        if (code == D[searchD].getCode())
        {
            if (D[searchD].getNumber() == num)
            {
                D.erase(iterSearchD);
                remove = true;
                break;
            }
            else if (D[searchD].getNumber() > num)
            {
                D[searchD].modifyNumber(num, false);
                remove = true;
                break;
            }
            else
            {
                pop_up("提示", "输入数目过大！");
                remove = true;
                break;
            }
        }
        searchD++;
    }
    if (!remove)
        pop_up("提示", "该商品不存在！");
}