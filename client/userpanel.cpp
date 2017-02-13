#include "userpanel.h"
#include "ui_userpanel.h"
#include "global_objs.h"
#include <QStandardItem>
#include <QStandardItemModel>
#include <QDir>
#include <QInputDialog>
#include <QDebug>

UserPanel::UserPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserPanel)
{
    ui->setupUi(this);
    this->parent = parent;

    load_files();
}

void UserPanel::load_files()
{
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


void UserPanel::reload_files()
{
    QStandardItemModel *listModel = new QStandardItemModel();

    this->ui->listView->setModel(listModel);

    // clear the list box
    load_files();
}


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

void UserPanel::on_pushButton_3_clicked()
{
    qInfo() << QString("[CREATE FILE] create new file");

    bool ok;
    QString filename = QInputDialog::getText(this, tr("Create a new file"),
                                         tr("Insert file name here: "), QLineEdit::Normal,
                                         QDir::home().dirName(), &ok);



    bool status = fm.create_new_file(filename.toUtf8().constData());

    if (!status)
    {
        Mbox = new QMessageBox();
        Mbox->setText("File already exists");
        Mbox->show();
    }

    reload_files();
}
