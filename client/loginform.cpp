#include "loginform.h"
#include "ui_loginform.h"
#include "global_objs.h"
#include <QMessageBox>

LoginForm::LoginForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);
    this->parent = parent;
}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::on_pushButton_clicked()
{
    Mbox = new QMessageBox();

    if (ui->lineEdit->text() == "")
    {
        Mbox->setText("Invalid username");
        Mbox->show();
    }

    if (ui->lineEdit_2->text() == "")
    {
        Mbox->setText("Invalid password");
        Mbox->show();
    }

    bool status = um.login_user(ui->lineEdit->text().toUtf8().constData(),
                                ui->lineEdit_2->text().toUtf8().constData());

    if (!status)
    {
        Mbox->setText("Login failed, meybe you should check your username/password pair");
        Mbox->show();
    }
    else
    {
        Mbox->setText("Login successfull");
        Mbox->show();

        sm.set_username(ui->lineEdit->text().toUtf8().constData());

        userPanel = new UserPanel(this);
        this->ui->pushButton->hide();
        this->ui->label_2->hide();
        this->ui->label->hide();
        this->ui->lineEdit->hide();
        this->ui->lineEdit_2->hide();
        userPanel->show();
    }

}
