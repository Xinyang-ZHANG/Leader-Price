//
// Created by MAC on 2019/6/23.
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
#include <QFormLayout>
#include <QSpinBox>
#include <QDialogButtonBox>
#include <QRadioButton>
#include <QGroupBox>
#include <QCheckBox>
#include <QTextBrowser>
#include <QStatusBar>
#include <QToolBar>
#include <QTimer>
#include <iostream>
#include <sstream>

using namespace std;

#include "Interface.h"
#include "Manager.h"
#include "MyButton.h"
#include "LabelTimer.h"
#include "MyException.h"

Interface::Interface(){}

void Interface::chooseToLogin(int argc, char **argv, Manager &managerTemp)
{
    QApplication app(argc, argv);

    QDialog *dialog = new QDialog;
    QFormLayout form(dialog);
    form.addRow(new QLabel("请选择你的职业: "));

    QRadioButton *IamManager = new QRadioButton(QString("我是管理者"));
    QRadioButton *IamCashier = new QRadioButton(QString("我是收银员"));
    QRadioButton *Minscrire = new QRadioButton(QString("管理员注册"));
    IamCashier->setText(QString("我是收银员"));
    IamManager->setText(QString("我是管理者"));
    Minscrire->setText(QString("管理员注册"));
    form.addRow(IamCashier);
    form.addRow(IamManager);
    form.addRow(Minscrire);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, dialog);  //Qt::Horizonta横向排列按钮
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), dialog, SLOT(reject()));

    int whoIam = 0;
    if (dialog->exec() == QDialog::Accepted)
    {
        whoIam = 4;
        if (IamCashier->isChecked())
            whoIam = 1;
        else if (IamManager->isChecked())
            whoIam = 2;
        else if (Minscrire->isChecked())
            whoIam = 3;
    }

    Result result;
    Inscrire meInscrire;
    if (whoIam == 1)
    {
        result.usercode = CashierLogin(argc, argv);
        managerTemp.LoginCashier(result.usercode, argc, argv, managerTemp);
    }
    else if (whoIam == 2)
    {
        result = ManagerLogin(argc, argv);
        managerTemp.Login(result.usercode, result.password, argc, argv, managerTemp);
    }
    else if (whoIam == 3)
    {
        meInscrire = ManagerRegister(argc, argv, managerTemp);
        managerTemp.Register(meInscrire.Firstname, meInscrire.Lastname, meInscrire.password, meInscrire.code, argc, argv, managerTemp);
    }
    else if (whoIam == 4)
    {
        wrongdialog(argc, argv);
        chooseToLogin(argc, argv, managerTemp);
    }
    else
        exit(0);
}

Inscrire Interface::ManagerRegister(int argc, char **argv, Manager &managerTemp)
{
    QApplication app(argc, argv);

    string Firstname, Lastname, password;
    int code;
    QDialog *dialog = new QDialog;
    dialog->setWindowTitle("管理员注册");
    QString *lastname = new QString("请输入姓氏：");
    QString *firstname = new QString("请输入名字：");
    QString *mima = new QString("请输入密码：");
    QString *badge = new QString("请输入编号");
    QSpinBox *usercode = new QSpinBox(dialog);
    QLineEdit *first = new QLineEdit;
    QLineEdit *last = new QLineEdit;
    QLineEdit *word = new QLineEdit;
    QFormLayout form(dialog);
    form.addRow(*badge, usercode);
    form.addRow(*firstname, first);
    form.addRow(*lastname, last);
    form.addRow(*mima, word);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, dialog);  //Qt::Horizonta横向排列按钮
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), dialog, SLOT(reject()));

    Inscrire inscrire;
    if (dialog->exec() == QDialog::Accepted)
    {
        Firstname = string((const char*)first->text().toLocal8Bit());
        Lastname = string((const char*)last->text().toLocal8Bit());
        password = string((const char*)word->text().toLocal8Bit());
        code = usercode->text().toInt();
        inscrire = {Firstname, Lastname, password, code};
        return inscrire;
    }
    else
        chooseToLogin(argc, argv, managerTemp);
}

Result Interface::ManagerLogin(int argc, char **argv)
{
    QApplication app(argc, argv);

    QWidget *widget = new QWidget;
    widget->setGeometry(500, 300, 200, 150);
    QDialog *dialog = new QDialog;
    QString *title = new QString("管理员登录");
    QString *notice1 = new QString("请输入用户码：");
    QString *notice2 = new QString("请输入密码：");
    QSpinBox *usercode = new QSpinBox(dialog);
    QLineEdit *password = new QLineEdit;
    QFormLayout form(dialog);

    dialog->setWindowTitle(*title);
    form.addRow(*notice1, usercode);
    form.addRow(*notice2, password);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, dialog);  //Qt::Horizonta横向排列按钮
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), dialog, SLOT(reject()));

    int output1;
    string output2;
    if (dialog->exec() == QDialog::Accepted)
    {
        output1 = usercode->text().toInt();
        output2 = string((const char*)password->text().toLocal8Bit());
    }
    Result result{output1, output2};
    return result;
}

int Interface::CashierLogin(int argc, char **argv)
{
    QApplication app(argc, argv);

    QWidget *widget = new QWidget;
    widget->setGeometry(500, 300, 200, 150);
    QDialog *dialog = new QDialog;
    QString *title = new QString("售货员登录");
    QString *notice = new QString("请输入用户码：");
    QSpinBox *usercode = new QSpinBox(dialog);
    QFormLayout form(dialog);

    dialog->setWindowTitle(*title);
    form.addRow(*notice, usercode);
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, dialog);  //Qt::Horizonta横向排列按钮
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), dialog, SLOT(reject()));

    if (dialog->exec() == QDialog::Accepted)
    {
        int output;
        output = usercode->text().toInt();
        return output;
    }
}
void Interface::MainWindowForManager(int argc, char **argv, AccountManager &accountManager, Manager &manager)
{
    QApplication app(argc, argv);

    manager.accountManager = accountManager;
    manager.SoldBox_toAM();
    manager.getOrderToAccount();

    stringstream convert;
    convert<<accountManager.getWorkingNumber();
    string worknumfinal = convert.str();
    QString *title = new QString;
    title->push_back("欢迎您, 第");
    title->push_back(QString::fromStdString(worknumfinal));
    title->push_back("号管理员");
    QTextBrowser *welcome = new QTextBrowser;
    welcome->setFixedSize(150, 30);
    welcome->setText(*title);

    QWidget *centre = new QWidget;
    //centre->setFixedSize(100, 100);
    QMainWindow *mainWindow = new QMainWindow;
    mainWindow->setWindowTitle("主界面");
    mainWindow->setCentralWidget(centre);

    MyButton myButtonA(QString("我的仓库"), centre, 0, argc, argv, &manager);
    MyButton myButtonB(QString("手动添货"), centre, 1, argc, argv, &manager);
    MyButton myButtonC(QString("手动除货"), centre, 2, argc, argv, &manager);
    MyButton myButtonD(QString("精准查货"), centre, 3, argc, argv, &manager);
    MyButton myButtonE(QString("我的售出"), centre, 4, argc, argv, &manager);
    MyButton myButtonF(QString("查看雇员"), centre, 5, argc, argv, &manager);
    MyButton myButtonG(QString("修改薪水"), centre, 6, argc, argv, &manager);
    MyButton myButtonH(QString("我的信息"), centre, 7, argc, argv, &manager);
    MyButton myButtonS(QString("存储信息"), centre, 8, argc, argv, &manager);
    //QPushButton *quitButton = new QPushButton("退出", centre);
    //QObject::connect(quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
    QVBoxLayout *vboxleft = new QVBoxLayout;
    QVBoxLayout *vboxright = new QVBoxLayout;
    vboxleft->addWidget(&myButtonA);
    vboxleft->addWidget(&myButtonB);
    vboxleft->addWidget(&myButtonC);
    vboxleft->addWidget(&myButtonD);
    vboxright->addWidget(&myButtonE);
    vboxright->addWidget(&myButtonF);
    vboxright->addWidget(&myButtonG);
    vboxright->addWidget(&myButtonH);
    vboxright->addWidget(&myButtonS);
    //vbox->addWidget(quitButton);
    QGroupBox *groupBoxleft = new QGroupBox;
    QGroupBox *groupBoxright = new QGroupBox;
    groupBoxleft->setMaximumWidth(170);
    groupBoxright->setMaximumWidth(170);
    groupBoxleft->setLayout(vboxleft);
    groupBoxright->setLayout(vboxright);
    QHBoxLayout *mainlayout = new QHBoxLayout;
    QVBoxLayout *layoutleft = new QVBoxLayout;
    QVBoxLayout *layoutright = new QVBoxLayout;
    layoutleft->addWidget(welcome);
    layoutleft->addWidget(groupBoxleft);
    layoutright->addWidget(groupBoxright);
    mainlayout->addLayout(layoutleft);
    mainlayout->addLayout(layoutright);
    centre->setLayout(mainlayout);

    //mainWindow->setFixedSize(200, 200);
    BarTimer barTimer;
    QTimer *timer = new QTimer;
    timer->start(1000);
    QObject::connect(timer, SIGNAL(timeout()), &barTimer, SLOT(timer()));
    mainWindow->setStatusBar(&barTimer);
    mainWindow->show();
    app.exec();
    delete timer;
    chooseToLogin(argc, argv, manager);
}

void Interface::MainWindowForCashier(int argc, char **argv, Cashier *cashier, Manager &manager)
{
    Cashier *cashierTemps = cashier;
    manager.MyEmployee.addCashier(cashierTemps);
    int worknum = manager.MyEmployee.getNumCash();
    manager.MyEmployee.getList()[manager.MyEmployee.getNumCash() - 1]->readEntrepot();
    QApplication app(argc, argv);

    stringstream convert;
    convert<<worknum;
    string worknumfinal = convert.str();
    QString *title = new QString;
    title->push_back("欢迎您, 第");
    title->push_back(QString::fromStdString(worknumfinal));
    title->push_back("位收银员");
    QTextBrowser *welcome = new QTextBrowser;
    welcome->setFixedSize(200, 30);
    welcome->setText(*title);

    QWidget *centre = new QWidget;
    QMainWindow *mainWindow = new QMainWindow;
    mainWindow->setWindowTitle("收银界面");
    mainWindow->setCentralWidget(centre);

    MyButton myButtonI(QString("开始售卖"), centre, 9, argc, argv, &manager, worknum);
    MyButton myButtonJ(QString("我的仓库"), centre, 10, argc, argv, &manager, (manager.MyEmployee.getNumCash() - 1));
    MyButton myButtonK(QString("我的信息"), centre, 11, argc, argv, &manager, (manager.MyEmployee.getNumCash() - 1));

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(&myButtonI);
    vbox->addWidget(&myButtonJ);
    vbox->addWidget(&myButtonK);
    QGroupBox *groupBox = new QGroupBox;
    groupBox->setMaximumWidth(100);
    groupBox->setLayout(vbox);
    QVBoxLayout *mainlayout = new QVBoxLayout;
    mainlayout->addWidget(welcome);
    mainlayout->addWidget(groupBox);
    centre->setLayout(mainlayout);

    BarTimer barTimer;
    QTimer *timer = new QTimer;
    timer->start(1000);
    QObject::connect(timer, SIGNAL(timeout()), &barTimer, SLOT(timer()));
    QObject::connect(&myButtonI, SIGNAL(sendtext(string)), &barTimer, SLOT(successmessage(string)));
    mainWindow->setStatusBar(&barTimer);
    mainWindow->show();
    app.exec();
    delete timer;
    chooseToLogin(argc, argv, manager);
}

int Interface::wrongdialog(int argc, char **argv)
{
    QApplication app(argc, argv);

    QString *string1 = new QString;
    string1->push_back("请选择您的职业！");
    QString *string2 = new QString;
    string2->push_back("错误报告");

    QLabel *label = new QLabel;
    label->setFixedSize(200, 60);
    label->setText(*string1);
    label->setMargin(18);
    label->setWindowTitle(*string2);
    label->show();

    return app.exec();
}

int Interface::wrongcode(int argc, char **argv)
{
    QApplication app(argc, argv);

    QString *string1 = new QString;
    string1->push_back("用户代码不存在或未按下确认！");
    QString *string2 = new QString;
    string2->push_back("错误报告");

    QLabel *label = new QLabel;
    label->setFixedSize(200, 60);
    label->setText(*string1);
    label->setMargin(18);
    label->setWindowTitle(*string2);
    label->show();

    return app.exec();
}

int Interface::wrongpassword(int argc, char **argv)
{
    QApplication app(argc, argv);

    QString *string1 = new QString;
    string1->push_back("密码错误！");
    QString *string2 = new QString;
    string2->push_back("错误报告");

    QLabel *label = new QLabel;
    label->setFixedSize(200, 60);
    label->setText(*string1);
    label->setMargin(18);
    label->setWindowTitle(*string2);
    label->show();

    return app.exec();
}

int Interface::wrongregister(int argc, char **argv)
{
    QApplication app(argc, argv);

    QString *string1 = new QString;
    string1->push_back("管理员码重复！");
    QString *string2 = new QString;
    string2->push_back("错误报告");

    QLabel *label = new QLabel;
    label->setFixedSize(200, 60);
    label->setText(*string1);
    label->setMargin(18);
    label->setWindowTitle(*string2);
    label->show();

    return app.exec();
}
int Interface::rightregister(int argc, char **argv)
{
    QApplication app(argc, argv);

    QString *string1 = new QString;
    string1->push_back("成功注册管理员账户！");
    QString *string2 = new QString;
    string2->push_back("提示");

    QLabel *label = new QLabel;
    label->setFixedSize(200, 60);
    label->setText(*string1);
    label->setMargin(18);
    label->setWindowTitle(*string2);
    label->show();

    return app.exec();
}