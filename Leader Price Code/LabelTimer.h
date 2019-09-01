//
// Created by MAC on 2019/7/5.
//

#ifndef LEADER_PRICE_LABELTIMER_H
#define LEADER_PRICE_LABELTIMER_H

#include <QStatusBar>
#include <QString>
#include <QTimer>
#include <iostream>
#include <ctime>

using namespace std;

class BarTimer: public QStatusBar{
    Q_OBJECT;
public:
    BarTimer();

public slots:
    void timer();
    void successmessage(string message);

};

#endif //LEADER_PRICE_LABELTIMER_H
