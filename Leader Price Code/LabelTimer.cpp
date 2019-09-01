//
// Created by MAC on 2019/7/5.
//

#include <iostream>
#include <ctime>
#include <QTimer>
#include <QString>
#include <QStatusBar>

using namespace std;

#include "LabelTimer.h"

BarTimer::BarTimer() {}
void BarTimer::timer()
{
    time_t now = time(0);
    string output = ctime(&now);
    this->showMessage(QString::fromLocal8Bit(output.data()), 1000);
}
void BarTimer::successmessage(string message)
{
    this->showMessage(QString::fromLocal8Bit(message.data()), 800);
}

