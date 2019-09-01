//
// Created by MAC on 2019/6/22.
//
#ifndef LEADER_PRICE_MYACTION1_H
#define LEADER_PRICE_MYACTION1_H

#pragma once

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

using namespace std;

#include "Manager.h"
#include "Interface.h"

class MyButton: public QPushButton
{
    Q_OBJECT;
public:
    MyButton(const QString& text, QWidget* parent, int choice, int argc, char **argv, Manager *manager);
    MyButton(const QString& text, QWidget* parent, int choice, int argc, char **argv, Manager *manager, int num);
    void showAllMerchandise();
    void addMerchandise();
    void removeMerchandise();
    void showMerchandise();
    void showManagerInfo();
    void showSoldMerchandise();
    void showLogedEmployees();
    void modifysalary();
    void STOCK();

    void sell();
    void showmywarehouse();
    void showCashier();

public slots:
    void selectFunction();

signals:
    void sendtext(string text);

private:
    int argc; char **argv; int choice; int num;
    Manager *manager;
};

#endif //LEADER_PRICE_MYACTION1_H
