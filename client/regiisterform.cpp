#include "regiisterform.h"
#include "ui_regiisterform.h"
#include "global_objs.h"
#include <QDebug>
#include <iostream>

using namespace std;

RegiisterForm::RegiisterForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegiisterForm)
{
    ui->setupUi(this);
    Mbox = new QMessageBox();
    this->parent = parent;
}

RegiisterForm::~RegiisterForm()
{
    delete ui;
}

void RegiisterForm::on_pushButton_clicked()
{
    if (ui->lineEdit->text() == "")
    {
        Mbox->setText("Invalid Username");
        Mbox->open();
    }

    if (ui->lineEdit_2->text() == "")
    {
        Mbox->setText("Invalid password1");
        Mbox->open();
    }

    if (ui->lineEdit_3->text() == "")
    {
        Mbox->setText("Invalid password 2");
        Mbox->open();
    }

    if (ui->lineEdit_2->text() != ui->lineEdit_3->text())
    {
        Mbox->setText("Passwords don't match");
        Mbox->open();
    }

    qDebug() << "registering the user";

    bool status = um.register_user(ui->lineEdit->text().toUtf8().constData(),
                     ui->lineEdit_2->text().toUtf8().constData());

    if (!status)
    {
        Mbox->setText("User already exists try another one");
        Mbox->open();
    }
    else
    {
        Mbox->setText("Congratz, you've registered successfully");
        Mbox->open();
        parent->findChild<QWidget *>("pushButton")->show();
        parent->findChild<QWidget *>("pushButton_2")->show();
        this->close();
    }
}


