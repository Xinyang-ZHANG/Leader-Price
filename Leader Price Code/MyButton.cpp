//
// Created by MAC on 2019/6/22.
//

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
#include <QToolBar>
#include <QFormLayout>
#include <QSpinBox>
#include <QDialogButtonBox>
#include <iostream>

using namespace std;

#include "MyButton.h"
#include "Manager.h"

MyButton::MyButton(const QString& text, QWidget* parent, int choice, int argc, char **argv, Manager *manager) :QPushButton(text, parent)
{
    this->setFixedSize(130, 30);
    this->setText(text);
    this->argc = argc;
    this->argv = argv;
    this->choice = choice;
    this->manager = manager;
    connect(this, SIGNAL(clicked()), this, SLOT(selectFunction()), Qt::DirectConnection);
}
MyButton::MyButton(const QString& text, QWidget* parent, int choice, int argc, char **argv, Manager *manager, int num) :QPushButton(text, parent)
{
    this->setText(text);
    this->argc = argc;
    this->argv = argv;
    this->choice = choice;
    this->manager = manager;
    this->num = num;
    connect(this, SIGNAL(clicked()), this, SLOT(selectFunction()), Qt::DirectConnection);
}
//void MyButton::sendtext(string text){}
void MyButton::selectFunction()
{
    switch (choice){
        case 0: showAllMerchandise();
            break;
        case 1: addMerchandise();
            break;
        case 2: removeMerchandise();
            break;
        case 3: showMerchandise();
            break;
        case 4: showSoldMerchandise();
            break;
        case 5: showLogedEmployees();
            break;
        case 6: modifysalary();
            break;
        case 7: showManagerInfo();
            break;
        case 8: STOCK();
            break;
        case 9: sell();
            break;
        case 10: showmywarehouse();
            break;
        case 11: showCashier();
            break;
        default:
            break;
    }
}
void MyButton::showAllMerchandise() { manager->showAllMerchandise(); }
void MyButton::showSoldMerchandise() { manager->showTodaySoldMerchandise(); }
void MyButton::showMerchandise()
{
    QRadioButton *buttonH = new QRadioButton("Houseware");
    QRadioButton *buttonC = new QRadioButton("Clothing");
    QRadioButton *buttonF = new QRadioButton("Food");
    QRadioButton *buttonD = new QRadioButton("Drink");
    QLineEdit *inputcode = new QLineEdit;
    QDialog *dialog = new QDialog;
    QFormLayout form(dialog);
    form.addRow(new QLabel("请选择要展示的商品: "));
    form.addRow(buttonH);
    form.addRow(buttonC);
    form.addRow(buttonF);
    form.addRow(buttonD);
    form.addRow("请输入商品码code: ", inputcode);
    QDialogButtonBox buttonBoxA(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                                Qt::Horizontal, dialog);  //Qt::Horizonta横向排列按钮
    form.addRow(&buttonBoxA);
    QObject::connect(&buttonBoxA, SIGNAL(accepted()), dialog, SLOT(accept()));
    QObject::connect(&buttonBoxA, SIGNAL(rejected()), dialog, SLOT(reject()));

    if (dialog->exec() == QDialog::Accepted)
    {
        string code = string((const char*)inputcode->text().toLocal8Bit());
        if (buttonH->isChecked())
            manager->showHouseware(code);
        else if (buttonC->isChecked())
            manager->showClothing(code);
        else if (buttonF->isChecked())
            manager->showFood(code);
        else if (buttonD->isChecked())
            manager->showDrink(code);
    }
}
void MyButton::addMerchandise() { manager->addManually(); }
void MyButton::removeMerchandise()
{
    string categorie;
    //cout<<"Please put in a category: "<<endl;

    QRadioButton *buttonCATEH = new QRadioButton("Houseware");
    QRadioButton *buttonCATEC = new QRadioButton("Clothing");
    QRadioButton *buttonCATEF = new QRadioButton("Food");
    QRadioButton *buttonCATED = new QRadioButton("Drink");
    QDialog *dialogAdd = new QDialog;
    QFormLayout formA(dialogAdd);
    formA.addRow(new QLabel("请选择要输入的商品: "));
    formA.addRow(buttonCATEH);
    formA.addRow(buttonCATEC);
    formA.addRow(buttonCATEF);
    formA.addRow(buttonCATED);
    QDialogButtonBox buttonBoxA(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, dialogAdd);  //Qt::Horizonta横向排列按钮
    formA.addRow(&buttonBoxA);
    QObject::connect(&buttonBoxA, SIGNAL(accepted()), dialogAdd, SLOT(accept()));
    QObject::connect(&buttonBoxA, SIGNAL(rejected()), dialogAdd, SLOT(reject()));

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

    QDialog *dialog = new QDialog;
    QLineEdit *inputcode = new QLineEdit;
    QSpinBox *inputnum = new QSpinBox;
    QFormLayout formB(dialog);
    formB.addRow(QString::fromStdString("请输入商品码code: "), inputcode);
    formB.addRow(QString::fromStdString("请输入商品数目num: "), inputnum);

    QDialogButtonBox buttonBoxB(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, dialog);  //Qt::Horizonta横向排列按钮
    formB.addRow(&buttonBoxB);
    QObject::connect(&buttonBoxB, SIGNAL(accepted()), dialog, SLOT(accept()));
    QObject::connect(&buttonBoxB, SIGNAL(rejected()), dialog, SLOT(reject()));

    if (dialog->exec() == QDialog::Accepted)
    {
        if (categorie == "H")
            manager->removeHousewareFromAMManually(string((const char*)inputcode->text().toLocal8Bit()), inputnum->text().toInt());
        else if (categorie == "C")
            manager->removeClothingFromAMManually(string((const char*)inputcode->text().toLocal8Bit()), inputnum->text().toInt());
        else if (categorie == "F")
            manager->removeFoodFromAMManually(string((const char*)inputcode->text().toLocal8Bit()), inputnum->text().toInt());
        else if (categorie == "D")
            manager->removeDrinkFromAMManually(string((const char*)inputcode->text().toLocal8Bit()), inputnum->text().toInt());
    }
}
void MyButton::showLogedEmployees() { manager->showMyEmployees(); }
void MyButton::modifysalary()
{
    QDialog *dialog = new QDialog;
    QRadioButton *buttonUPDOWN = new QRadioButton;
    QLineEdit *howmuch = new QLineEdit;
    howmuch->setValidator(new QRegExpValidator(QRegExp("[0-9]+$+.")));
    QSpinBox *numbadge = new QSpinBox;
    QFormLayout form(dialog);
    form.addRow(QString::fromLocal8Bit("请输入员工码："), numbadge);
    form.addRow(QString::fromLocal8Bit("请输入修改金额："), howmuch);
    form.addRow(QString::fromLocal8Bit("是否为增加工资："), buttonUPDOWN);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                                Qt::Horizontal, dialog);  //Qt::Horizonta横向排列按钮
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), dialog, SLOT(reject()));
    bool updown = false;
    int numBadge = 0;
    float HOWMUCH = 0;
    if (dialog->exec() == QDialog::Accepted)
    {
        updown = buttonUPDOWN->isChecked();
        numBadge = numbadge->text().toInt();
        HOWMUCH = howmuch->text().toFloat();
        manager->modifyCashiersSalary(numBadge, HOWMUCH, updown);
    }
}
void MyButton::showManagerInfo() { manager->showme(); }
void MyButton::STOCK() { manager->StockToday(); }

void MyButton::sell()
{
    bool finish = false; bool success = false;
    FINI_REUSSI fini_reussi;
    while (!finish)
    {
        fini_reussi = manager->sell(argc, argv, num);
        success = fini_reussi.success;
        finish = fini_reussi.finish;
        string text = "已售出！";
        if (success)
            emit sendtext(text.data());
    }
}
void MyButton::showmywarehouse() { manager->showwarehouse(num); }
void MyButton::showCashier() { manager->MyEmployee.getList()[num]->show(); }