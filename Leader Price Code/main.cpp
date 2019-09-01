#include <iostream>
#include <vector>
#include <ctime>

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
#include <QCheckBox>
#include <QToolBar>

using namespace std;

#include "Merchandise.h"
#include "Houseware.h"
#include "Clothing.h"
#include "Food.h"
#include "Drink.h"
#include "Purchase_DP.h"
#include "MyException.h"
#include "Cashier.h"
#include "ListCashier.h"
#include "Account.h"
#include "Manager.h"
#include "MyButton.h"

#include "Interface.h"

void delay()
{
    clock_t delay = 1 * CLOCKS_PER_SEC;
    clock_t start = clock();
    while ((clock() - start) < delay) {}
}

int dialog2(int argc, char **argv){
    QApplication app(argc, argv);

    QDialog *dialog = new QDialog;
    QFormLayout form(dialog);
    form.addRow(new QLabel("User input:"));
// Value1
    QString value1 = QString("Value1: ");
    QSpinBox *spinbox1 = new QSpinBox(dialog);
    form.addRow(value1, spinbox1);
// Value2
    QString value2 = QString("Value2: ");
    QSpinBox *spinbox2 = new QSpinBox(dialog);
    form.addRow(value2, spinbox2);
// Text
    QString text = QString("put in text: ");
    QLineEdit *lineEdit = new QLineEdit;
    form.addRow(text, lineEdit);
// Add Cancel and OK button
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, dialog);  //Qt::Horizonta横向排列按钮
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), dialog, SLOT(reject()));

// Process when OK button is clicked
    if (dialog->exec() == QDialog::Accepted) {
        cout<<spinbox1->text().toInt();
        cout<<string((const char*)lineEdit->text().toLocal8Bit());
    }
}



void zhu(int argc, char **argv)
{
    Manager manager;
    //manager.Register("lanmao", "taoqi", "3000", 9);
    manager.Login(26, "anni961214", argc, argv, manager);
    manager.getOrderToAccount();
    //manager.showClothing("12-914");
    //manager.removeClothingFromAM("12-914", 2);
    //manager.showAllMerchandise();
    //manager.readMyEmployee();
    //manager.showMyEmployees();

    //manager.showTodayTurnover();



    manager.LoginCashier(8, argc, argv, manager);
    manager.MyEmployee.getList()[manager.MyEmployee.getNumCash() - 1]->readEntrepot();  //list的最后一个收银员
    manager.MyEmployee.getList()[manager.MyEmployee.getNumCash() - 1]->afficher_entrepot();

    delay();

    manager.LoginCashier(24, argc, argv, manager);  //Cashier中没有读取entrepot？
    manager.MyEmployee.getList()[manager.MyEmployee.getNumCash() - 1]->readEntrepot();  //登入时读取仓库
    manager.MyEmployee.getList()[manager.MyEmployee.getNumCash() - 1]->afficher_entrepot();
    //manager.getMyEmployee().getList()[m]->SellClothing("12-909", 1);
    //读仓库后要显示出来，要不然程序无法读入仓库，并且语句顺序需为（登入->读仓库->显示），每个账户的三条语句都要这么紧挨着写，不知道原因


    //manager.getMyEmployee().getList()[manager.getMyEmployee().getNumCash() - 1]->afficherSold();
    //manager.getMyEmployee().getList()[manager.getMyEmployee().getNumCash() - 1]->afficher();
    //manager.showMyEmployees();

    //manager.showTodayAM();
    manager.sell(argc, argv, 8);
    manager.sell(argc, argv, 24);
    manager.showTodayTurnover();
    delay();
    manager.addManually();
    delay();
    manager.StockToday();  //只卖掉第一个售货员的？ 因为两个售货员卖同样物品时没有累加；售货员销售不同货物时可以正常修改文件
    // 需要在stock之后的售货员时，增添对相同货物的直接添加数字功能
    delay();
    //manager.showAllMerchandise();
    manager.showTodaySoldMerchandise();  //修改getandclear_Soldbox
}

int main(int argc, char **argv)
{
    Manager manager;
    Interface anInterface;
    anInterface.chooseToLogin(argc, argv, manager);
    //zhu(argc, argv);
}

