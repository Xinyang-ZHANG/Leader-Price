//
// Created by MAC on 2019/6/6.
//

#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <ctime>
#include <QTextBrowser>

using namespace std;

#include "Manager.h"
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

#include "Interface.h"


void Manager::delay()
{
    clock_t delay = 1 * CLOCKS_PER_SEC;
    clock_t start = clock();
    while ((clock() - start) < delay) {}
}
int Manager::pop_up(string title, string output)
{
    QTextBrowser *showText = new QTextBrowser;
    showText->setText(QString::fromStdString(output));
    showText->setWindowTitle(QString::fromStdString(title));
    showText->show();
}
vector<AccountManager> Manager::readAM()
{
    string prenom, nom, password;
    int worknb;
    bool finished;
    vector<AccountManager> StockAM;

    ifstream fileIN;
    fileIN.open("/Users/mac/Desktop/après/C++/Leader Price/AccountManager.txt");
    if (!fileIN)
        cout<<"erreur lecture!"<<endl;
    finished = false;
    while (!finished)
    {
        fileIN>>prenom>>nom>>password>>worknb;
        AccountManager AMtemps(prenom, nom, password, worknb);
        if (!fileIN.eof())
            StockAM.push_back(AMtemps);
        else
            finished = true;
    }
    return StockAM;
}
vector<Cashier> Manager::readMyEmployee()
{
    string prenom, nom;
    int numbadge;
    float salary;
    int employeeNumber = 0;
    vector<Cashier> cashvecTemps;
    bool finished;

    ifstream fileIN;
    fileIN.open("/Users/mac/Desktop/après/C++/Leader Price/MyEmployee.txt");
    if (!fileIN)
        cout<<"erreur lecture!"<<endl;
    finished = false;
    while (!finished)
    {
        fileIN>>prenom>>nom>>numbadge>>salary;
        Cashier cashierTemps(prenom, nom, numbadge, salary);
        if (!fileIN.eof())
        {
            cashvecTemps.push_back(cashierTemps);
            employeeNumber++;
        }
        else
            finished = true;
    }

    return cashvecTemps;
}
TYPE Manager::convert_stringtoTYPE(string str)
{
    TYPE type;
    if (str == "H")
        type = HOUSEWARE;
    else if (str == "C")
        type = CLOTHING;
    else if (str == "F")
        type = FOOD;
    else if (str == "D")
        type = DRINK;
    else
        type = WRONG;
    return type;
}
bool Manager::compareHour()
{
    bool offduty = false;
    time_t now = time(0);
    tm* TN = gmtime(&now);
    if (20 <= 2 + TN->tm_hour)
        offduty = true;

    return offduty;
}
void Manager::modifyFileMerchandiseAM() { accountManager.modifyFileMerchandise(); }
FINI_REUSSI Manager::SellPop_up(int argc, char **argv, int choose, int numBadge)
{
    QDialog *dialog = new QDialog;
    QLabel label1(QString::fromStdString("请输入商品码code: "));
    label1.setFixedSize(150, 15);
    QLineEdit *inputcode = new QLineEdit;
    inputcode->setFixedSize(150, 20);
    QLabel label2(QString::fromStdString("请输入所售商品数目num: "));
    label2.setFixedSize(150, 15);
    QSpinBox *inputnum = new QSpinBox;
    inputnum->setFixedSize(150, 20);
    QLabel label3(QString::fromStdString("结束输入"));
    label3.setFixedSize(150, 15);
    QRadioButton *finish = new QRadioButton;
    finish->setFixedSize(150, 20);
    QLabel label4(QString::fromStdString("         "));
    label4.setFixedSize(150, 15);
    QHBoxLayout form(dialog);
    QVBoxLayout formleft;
    QVBoxLayout formright;
    formleft.addWidget(&label1);
    formleft.addWidget(inputcode);
    formleft.addWidget(&label2);
    formleft.addWidget(inputnum);
    formleft.addWidget(&label3);
    formleft.addWidget(finish);
    formleft.addWidget(&label4);
//cout<<numBadge;
    string info = MyEmployee.getList()[numBadge - 1]->afficherSold();;
    info += "My turnover is:\n";
    stringstream convert;
    convert<<MyEmployee.getList()[numBadge - 1]->getTurnover();
    info += convert.str();
    QTextBrowser *textBrowser = new QTextBrowser;
    textBrowser->setFixedSize(230, 200);
    textBrowser->setText(QString::fromStdString(info));
    QLabel label5(QString::fromStdString("显示售出"));
    label5.setFixedSize(150, 15);
    formright.addWidget(&label5);
    formright.addWidget(textBrowser);
    form.addLayout(&formleft);
    form.addLayout(&formright);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, dialog);  //Qt::Horizonta横向排列按钮
    formright.addWidget(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), dialog, SLOT(reject()));

    bool finished = true;
    bool success;
    if (dialog->exec() == QDialog::Accepted)
    {
        string code; int num;
        code = string((const char*)inputcode->text().toLocal8Bit());
        num = inputnum->text().toInt();
        finished = finish->isChecked();

        if (choose == 1)
            success = MyEmployee.getList()[numBadge - 1]->SellHouseware(code, num);
        else if (choose == 2)
            success = MyEmployee.getList()[numBadge - 1]->SellClothing(code, num);
        else if (choose == 3)
            success = MyEmployee.getList()[numBadge - 1]->SellFood(code, num);
        else if (choose == 4)
            success = MyEmployee.getList()[numBadge - 1]->SellDrink(code, num);
    }
    FINI_REUSSI fini_reussi{finished, success};
    return fini_reussi;
}


Manager::Manager(){}

void Manager::getOrderToAccount() { accountManager.getOrder(); }
void Manager::SoldBox_toAM()
{
    for (int i = 0; i < MyEmployee.getNumCash(); i++)
    {
        vector<Houseware>::iterator itH;
        int countH = 0;
        for (itH = MyEmployee.getList()[i]->getSoldBoxH().begin(); itH != MyEmployee.getList()[i]->getSoldBoxH().end(); itH++)
        {
            if (i == 0)
                SoldBoxH.push_back(MyEmployee.getList()[i]->getSoldBoxH()[countH]);  //把第一个收银员的盒子全部压入Soldbox
            else //如果之后的收银员有相同的卖出商品，则直接加上数目，不能重新存储
            {
                vector<Houseware>::iterator checkH;
                int checkcountH = 0;
                bool found = false;
                for (checkH = SoldBoxH.begin(); checkH != SoldBoxH.end(); checkH++) //每压入一个都要检查之前的所有盒子有无重复
                {
                    if (MyEmployee.getList()[i]->getSoldBoxH()[countH].getCode() == SoldBoxH[checkcountH].getCode())
                    {
                        SoldBoxH[checkcountH].modifyNumber(MyEmployee.getList()[i]->getSoldBoxH()[countH].getNumber(), true);
                        //如果我要压入的盒子与已有的Soldbox中任一个相同，则修改数字
                        found = true;
                        break;
                    }
                    checkcountH++;
                }
                if (!found)
                    SoldBoxH.push_back(MyEmployee.getList()[i]->getSoldBoxH()[countH]); //没有重复，则直接压入Soldbox
            }
            countH++;
        }

        vector<Clothing>::iterator itC;
        int countC = 0;
        for (itC = MyEmployee.getList()[i]->getSoldBoxC().begin(); itC != MyEmployee.getList()[i]->getSoldBoxC().end(); itC++)
        {
            if (i == 0)
                SoldBoxC.push_back(MyEmployee.getList()[i]->getSoldBoxC()[countC]);  //把第一个收银员的盒子全部压入Soldbox
            else //如果之后的收银员有相同的卖出商品，则直接加上数目，不能重新存储
            {
                vector<Clothing>::iterator checkC;
                int checkcountC = 0;
                bool found = false;
                for (checkC = SoldBoxC.begin(); checkC != SoldBoxC.end(); checkC++) //每压入一个都要检查之前的所有盒子有无重复
                {
                    if (MyEmployee.getList()[i]->getSoldBoxC()[countC].getCode() == SoldBoxC[checkcountC].getCode())
                    {
                        SoldBoxC[checkcountC].modifyNumber(MyEmployee.getList()[i]->getSoldBoxC()[countC].getNumber(), true);
                        //如果我要压入的盒子与已有的Soldbox中任一个相同，则修改数字
                        found = true;
                        break;
                    }
                    checkcountC++;
                }
                if (!found)
                    SoldBoxC.push_back(MyEmployee.getList()[i]->getSoldBoxC()[countC]); //没有重复，则直接压入Soldbox
            }
            countC++;
        }

        vector<Food>::iterator itF;
        int countF = 0;
        for (itF = MyEmployee.getList()[i]->getSoldBoxF().begin(); itF != MyEmployee.getList()[i]->getSoldBoxF().end(); itF++)
        {
            if (i == 0)
                SoldBoxF.push_back(MyEmployee.getList()[i]->getSoldBoxF()[countF]);  //把第一个收银员的盒子全部压入Soldbox
            else //如果之后的收银员有相同的卖出商品，则直接加上数目，不能重新存储
            {
                vector<Food>::iterator checkF;
                int checkcountF = 0;
                bool found = false;
                for (checkF = SoldBoxF.begin(); checkF != SoldBoxF.end(); checkF++) //每压入一个都要检查之前的所有盒子有无重复
                {
                    if (MyEmployee.getList()[i]->getSoldBoxF()[countF].getCode() == SoldBoxF[checkcountF].getCode())
                    {
                        SoldBoxF[checkcountF].modifyNumber(MyEmployee.getList()[i]->getSoldBoxF()[countF].getNumber(), true);
                        //如果我要压入的盒子与已有的Soldbox中任一个相同，则修改数字
                        found = true;
                        break;
                    }
                    checkcountF++;
                }
                if (!found)
                    SoldBoxF.push_back(MyEmployee.getList()[i]->getSoldBoxF()[countF]); //没有重复，则直接压入Soldbox
            }
            countF++;
        }

        vector<Drink>::iterator itD;
        int countD = 0;
        for (itD = MyEmployee.getList()[i]->getSoldBoxD().begin(); itD != MyEmployee.getList()[i]->getSoldBoxD().end(); itD++)
        {
            if (i == 0)
                SoldBoxD.push_back(MyEmployee.getList()[i]->getSoldBoxD()[countD]);  //把第一个收银员的盒子全部压入Soldbox
            else //如果之后的收银员有相同的卖出商品，则直接加上数目，不能重新存储
            {
                vector<Drink>::iterator checkD;
                int checkcountD = 0;
                bool found = false;
                for (checkD = SoldBoxD.begin(); checkD != SoldBoxD.end(); checkD++) //每压入一个都要检查之前的所有盒子有无重复
                {
                    if (MyEmployee.getList()[i]->getSoldBoxD()[countD].getCode() == SoldBoxD[checkcountD].getCode())
                    {
                        SoldBoxD[checkcountD].modifyNumber(MyEmployee.getList()[i]->getSoldBoxD()[countD].getNumber(), true);
                        //如果我要压入的盒子与已有的Soldbox中任一个相同，则修改数字
                        found = true;
                        break;
                    }
                    checkcountD++;
                }
                if (!found)
                    SoldBoxD.push_back(MyEmployee.getList()[i]->getSoldBoxD()[countD]); //没有重复，则直接压入Soldbox
            }
            countD++;
        }

        MyEmployee.getList()[i]->vider();
    }

    accountManager.pickSoldBoxs(SoldBoxH, SoldBoxC, SoldBoxF, SoldBoxD);
}


void Manager::showme(){ accountManager.afficher(); }
void Manager::showHouseware(string code) { accountManager.afficherInfoHouseware(code); }
void Manager::showClothing(string code) { accountManager.affichertInfoClothing(code); }
void Manager::showFood(string code) { accountManager.afficherInfoFood(code); }
void Manager::showDrink(string code) { accountManager.afficherInfoDrink(code); }
void Manager::showAllMerchandise() { accountManager.showAll(); }
void Manager::showwarehouse(int position) { MyEmployee.getList()[position]->afficher_entrepot(); }


void Manager::modifyCashiersSalary(int numBadge, float howmuch, bool UP)
{
    vector<Cashier> listTemps = readMyEmployee();
    vector<Cashier>::iterator itCashier;
    string inputfile;
    int count = 0;
    bool found = false;
    for (itCashier = listTemps.begin(); itCashier != listTemps.end(); itCashier++)
    {
        if (numBadge == listTemps[count].getNumBadge())
        {
            listTemps[count].modifySalary(howmuch, UP);
            found = true;
        }
        inputfile += listTemps[count].getMe();
        count++;
    }
    if (!found)
        pop_up("提示", "身份牌码错误！");
        //cout<<"Wrong badge number! "<<endl<<endl;
    else
    {
        ofstream fileOUT("/Users/mac/Desktop/après/C++/Leader Price/MyEmployee.txt");
        fileOUT<<inputfile;
        fileOUT.close();
    }
}
void Manager::addManually()
{
    Interface anInterface;
    string categorie = "jiba";
    //cout<<"Please put in a category: "<<endl;

    QRadioButton *buttonCATEH = new QRadioButton("Houseware");
    QRadioButton *buttonCATEC = new QRadioButton("Clothing");
    QRadioButton *buttonCATEF = new QRadioButton("Food");
    QRadioButton *buttonCATED = new QRadioButton("Drink");
    QDialog *dialogAdd = new QDialog;
    QFormLayout form(dialogAdd);
    form.addRow(new QLabel("请选择要输入的商品: "));
    form.addRow(buttonCATEH);
    form.addRow(buttonCATEC);
    form.addRow(buttonCATEF);
    form.addRow(buttonCATED);
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, dialogAdd);  //Qt::Horizonta横向排列按钮
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), dialogAdd, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), dialogAdd, SLOT(reject()));

    if (dialogAdd->exec() == QDialog::Accepted)
    {
        if (buttonCATEH->isChecked())
            categorie = "H";
        else if (buttonCATEC->isChecked())
            categorie = "C";
        else if (buttonCATEF->isChecked())
            categorie = "F";
        else if (buttonCATED->isChecked())
            categorie = "D";
    }
    //cin>>categorie;
    TYPE category;
    category = convert_stringtoTYPE(categorie);

    switch (category)
    {
        case HOUSEWARE: accountManager.addHousewareManually();
            break;
        case CLOTHING: accountManager.addClothingManually();
            break;
        case FOOD: accountManager.addFoodManually();
            break;
        case DRINK: accountManager.addDrinkManually();
            break;
        case WRONG:
            //cout<<"Wrong category!"<<endl<<endl;
            QLabel *label = new QLabel;
            label->setWindowTitle(QString::fromStdString("错误报告"));
            label->setText(QString::fromStdString("Wrong category!"));
            label->show();
            break;
    }
}
void Manager::removeHousewareFromAMManually(string code, int num) { accountManager.removeHousewareManually(code, num); }
void Manager::removeClothingFromAMManually(string code, int num) { accountManager.removeClothingManually(code, num); }
void Manager::removeFoodFromAMManually(string code, int num) { accountManager.removeFoodManually(code, num); }
void Manager::removeDrinkFromAMManually(string code, int num) { accountManager.removeDrinkManually(code, num); }


void Manager::showMyEmployees()
{
    string output = MyEmployee.afficher();
    pop_up("已登录的雇员", output);
}
string Manager::showTodayTurnover()
{
    string output = "Today's turnover is: \n";
    output += MyEmployee.AllTurnover();
    output += "\n\n";
    return output;
}
string Manager::showToday()
{
    return accountManager.showToday();
};
void Manager::showTodaySoldMerchandise()
{
    vector<Houseware>::iterator itH;
    vector<Clothing>::iterator itC;
    vector<Food>::iterator itF;
    vector<Drink>::iterator itD;
    int count = 0;
    string output;

    output += "我售出的Houseware: \n";
    for (itH = SoldBoxH.begin(); itH != SoldBoxH.end(); itH++)
    {
        output += SoldBoxH[count].afficher();
        count++;
    }
    output += "我售出的Clothing: \n";
    count = 0;
    for (itC = SoldBoxC.begin(); itC != SoldBoxC.end(); itC++)
    {
        output += SoldBoxC[count].afficher();
        count++;
    }
    output += "我售出的Food: \n";
    count = 0;
    for (itF = SoldBoxF.begin(); itF != SoldBoxF.end(); itF++)
    {
        output += SoldBoxF[count].afficher();
        count++;
    }
    output += "我售出的Drink: \n";
    count = 0;
    for (itD = SoldBoxD.begin(); itD != SoldBoxD.end(); itD++)
    {
        output += SoldBoxD[count].afficher();
        count++;
    }
    output += "***********************\n\n";
    output += "All turnover is:\n";
    stringstream convert;
    convert<<MyEmployee.AllTurnover();
    output += convert.str();
    QTextBrowser *showText = new QTextBrowser;
    showText->setText(QString::fromStdString(output));
    showText->setWindowTitle(QString::fromStdString("我的售出"));
    showText->show();
}

FINI_REUSSI Manager::sell(int argc, char **argv, int workingNum)
{
    int numBadge = 0;
    string code, typeTemps;
    TYPE type;

    for (numBadge = 0; numBadge < MyEmployee.getNumCash(); numBadge++)
        if (workingNum == MyEmployee.getList()[numBadge]->getNumBadge())
            break;  //要求已经登录

    bool finish, success;

    QRadioButton *buttonCATEH = new QRadioButton("Houseware");
    QRadioButton *buttonCATEC = new QRadioButton("Clothing");
    QRadioButton *buttonCATEF = new QRadioButton("Food");
    QRadioButton *buttonCATED = new QRadioButton("Drink");
    QDialog *dialog = new QDialog;
    QFormLayout form(dialog);
    form.addRow(new QLabel("请选择要输入的商品: "));
    form.addRow(buttonCATEH);
    form.addRow(buttonCATEC);
    form.addRow(buttonCATEF);
    form.addRow(buttonCATED);
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, dialog);  //Qt::Horizonta横向排列按钮
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), dialog, SLOT(reject()));
    if (dialog->exec() == QDialog::Accepted)
    {
        if (buttonCATEH->isChecked())
            typeTemps = "H";
        else if (buttonCATEC->isChecked())
            typeTemps = "C";
        else if (buttonCATEF->isChecked())
            typeTemps = "F";
        else if (buttonCATED->isChecked())
            typeTemps = "D";
        else if(!buttonCATEH->isChecked() && !buttonCATEC->isChecked() && !buttonCATEF->isChecked() &&! buttonCATED->isChecked())
            typeTemps = "wrong";
    }
    else
    {
        typeTemps = "wrong";
        finish = true;
    }

    type = convert_stringtoTYPE(typeTemps);
    FINI_REUSSI fini_reussiTEMPS{ finish, success };
    //点击按钮继续来循环，不用finish
    switch (type)
    {
        case HOUSEWARE:
            fini_reussiTEMPS = SellPop_up(argc, argv, 1, numBadge);
            break;

        case CLOTHING:
            fini_reussiTEMPS = SellPop_up(argc, argv, 2, numBadge);
            break;

        case FOOD:
            fini_reussiTEMPS = SellPop_up(argc, argv, 3, numBadge);
            break;

        case DRINK:
            fini_reussiTEMPS = SellPop_up(argc, argv, 4, numBadge);
            break;
        case WRONG:
            pop_up("提示", "请选择一个类别");
            break;
    }
    return fini_reussiTEMPS;
}


void Manager::StockToday()
{
    if (compareHour())
        modifyFileMerchandiseAM();
    else
        pop_up("提示", "请在工作人员下班后存储当天数据！");

}


void Manager::Register(string Firstname, string Lastname, string password, int code, int argc, char **argv, Manager &managerTemp)
{
    Interface anInterface;
    vector<AccountManager>::iterator iterAMCodeCheck;
    vector<AccountManager> AMCodeCheck = readAM();
    int countAM = 0;
    for (iterAMCodeCheck = AMCodeCheck.begin(); iterAMCodeCheck != AMCodeCheck.end(); iterAMCodeCheck++)
    {
        if (AMCodeCheck[countAM].getWorkingNumber() == code)
        {
            anInterface.wrongregister(argc, argv);
            anInterface.chooseToLogin(argc, argv, managerTemp);
        }
        countAM++;
    }

    ofstream fileOUT("/Users/mac/Desktop/après/C++/Leader Price/AccountManager.txt", ios::app);
    fileOUT<<Firstname<<"  "<<Lastname<<"  "<<password<<"  "<<code<<"\n";
    fileOUT.close();

    anInterface.rightregister(argc, argv);
    anInterface.chooseToLogin(argc, argv, managerTemp);
}
void Manager::Login(int code, string password, int argc, char **argv, Manager &managerTemp)
{
    Interface anInterface;
    while (1)
    {
        vector<AccountManager> AMtemps = readAM();
        vector<AccountManager>::iterator iterAM;
        int countAM = 0;
        for (iterAM = AMtemps.begin(); iterAM != AMtemps.end(); iterAM++)
        {
            if (code == AMtemps[countAM].getWorkingNumber())
                break;
            countAM++;
        }

        if (iterAM == AMtemps.end())
        {
            anInterface.wrongcode(argc, argv); //之后加上跳转页面
            anInterface.chooseToLogin(argc, argv, managerTemp);
        }
        else if (password == AMtemps[countAM].getPassword())
        {
            accountManager = AMtemps[countAM];
            anInterface.MainWindowForManager(argc, argv, accountManager, managerTemp);
            break;
        }
        else
        {
            anInterface.wrongpassword(argc, argv);  //之后加上跳转页面
            anInterface.chooseToLogin(argc, argv, managerTemp);
        }
    }
}
void Manager::LoginCashier(int workingNum, int argc, char **argv, Manager &managerTemp)
{
    Interface anInterface;
    vector<Cashier> vecTemps = readMyEmployee();
    ListCashier listTemps;
    vector<Cashier>::iterator iterCashTemps;
    int countCashier = 0;

    for (iterCashTemps = vecTemps.begin(); iterCashTemps != vecTemps.end(); iterCashTemps++)
    {
        listTemps.addCashier(&vecTemps[countCashier]);
        countCashier++;
    } //将所有.txt中的cashier全部放入listTemps中

    for (int i = 0; i < MyEmployee.getNumCash(); i++)
        listTemps.removeCashier(MyEmployee.getList()[i]->getNumBadge());//然后去除MyEmployee中已经登录过的收银员，避免重复登录

    while (1) //在剩下的未登录的收银员中，判断要登录的是谁
    {
        int i = 0;
        for (i = 0; i < listTemps.getNumCash(); i++)
            if (listTemps.getList()[i]->getNumBadge() == workingNum)
                break;
        if (i == listTemps.getNumCash())
        {
            anInterface.wrongcode(argc, argv); //之后加上跳转页面
            anInterface.chooseToLogin(argc, argv, managerTemp);
        }
        else
        {
            //MyEmployee.addCashier(listTemps.getList()[i]);
            anInterface.MainWindowForCashier(argc, argv, listTemps.getList()[i], managerTemp);
            break;
        }
    }
}