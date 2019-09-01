//
// Created by MAC on 2019/6/4.
//

#include <iostream>
#include <iomanip>
#include <ostream>
#include <fstream>

using namespace std;

#include "MyException.h"

MyException::MyException(const string &s) { str = s; }
ostream& operator<< (ostream& flot, const MyException& ex)
{
    flot<<ex.str;
    return flot;
}