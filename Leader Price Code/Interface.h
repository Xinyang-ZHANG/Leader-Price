//
// Created by MAC on 2019/6/23.
//

#ifndef LEADER_PRICE_INTERFACE_H
#define LEADER_PRICE_INTERFACE_H

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
#include <QGroupBox>
#include <QCheckBox>
#include <QToolBar>
#include <iostream>

using namespace std;

#include "Manager.h"
//#include "MyButton.h"
#include "MyException.h"

struct Result{
    int usercode; string password;
};
struct Inscrire{
    string Firstname, Lastname, password;
    int code;
};

class Interface
{
public:
    Interface();
    void chooseToLogin(int argc, char **argv, Manager &managerTemp);
    Inscrire ManagerRegister(int argc, char **argv, Manager &managerTemp);
    Result ManagerLogin(int argc, char **argv);
    int CashierLogin(int argc, char **argv);
    void MainWindowForManager(int argc, char **argv, AccountManager &accountManager, Manager &manager);
    void MainWindowForCashier(int argc, char **argv, Cashier *cashier, Manager &manager);

    int wrongdialog(int argc, char **argv);
    int wrongcode(int argc, char **argv);
    int wrongpassword(int argc, char **argv);
    int wrongregister(int argc, char **argv);
    int rightregister(int argc, char **argv);
};

#endif //LEADER_PRICE_INTERFACE_H
