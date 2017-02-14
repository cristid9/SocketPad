#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "regiisterform.h"
#include "global_objs.h"
#include "json.hpp"
#include <iostream>
#include <QCloseEvent>

using json = nlohmann::json;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    json request = { {"action", "QUIT"} };

    clsock.write_msg(request.dump());
    event->accept();
}

void MainWindow::on_pushButton_clicked()
{
    loginForm = new LoginForm(this);
    loginForm->show();
    ui->pushButton->hide();
    ui->pushButton_2->hide();
}

void MainWindow::openRegisterForm()
{

}

void MainWindow::on_pushButton_2_clicked()
{
    registerForm = new RegiisterForm(this);
    registerForm->show();
    ui->pushButton->hide();
    ui->pushButton_2->hide();
}
