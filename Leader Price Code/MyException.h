//
// Created by MAC on 2019/6/4.
//

#ifndef LEADER_PRICE_MYEXCEPTION_H
#define LEADER_PRICE_MYEXCEPTION_H

#include <iostream>
#include <iomanip>
#include <ostream>
#include <fstream>

using namespace std;

class MyException
{
private:
    string str;
public:
    MyException(const string& s);
    friend ostream& operator<<(ostream& flot, const MyException& ex);
};

#endif //LEADER_PRICE_MYEXCEPTION_H
