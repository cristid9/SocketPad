#include "userpanel.h"
#include "ui_userpanel.h"
#include "global_objs.h"
#include <QStandardItem>
#include <QStandardItemModel>

UserPanel::UserPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserPanel)
{
    ui->setupUi(this);
    this->parent = parent;

    std::vector<std::string> files = fm.get_user_files(sm.get_username());

    QStandardItemModel *listModel = new QStandardItemModel();

    for (int i = 0; i < files.size(); ++i)
    {

        std::cout << files[i] << "==" << std::endl;
        QString qstr = QString::fromStdString(files[i]);

        QStandardItem* item = new QStandardItem(qstr);
        listModel->setItem(i, item);
    }

    this->ui->listView->setModel(listModel);
}

// fuck, man plictisit


UserPanel::~UserPanel()
{
    delete ui;
}

void UserPanel::on_pushButton_2_clicked()
{
    editFile = new FileEdit(this);
    editFile->show();
    this->ui->listView->hide();
    this->ui->label->hide();
    this->ui->label_2->hide();
    this->ui->pushButton->hide();
    this->ui->pushButton_2->hide();
}
