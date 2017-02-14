#include "userpanel.h"
#include "ui_userpanel.h"
#include "global_objs.h"
#include "json.hpp"
#include <QStandardItem>
#include <QStandardItemModel>
#include <QDir>
#include <QInputDialog>
#include <QDebug>

using json = nlohmann::json;

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
    editFile->set_filename(
                this->ui->listView->model()->index(
                    this->ui->listView->selectionModel()->currentIndex().row(), 0)
                .data(Qt::DisplayRole).toString().toUtf8().constData());
    editFile->handle_room_logic();
    editFile->show();
    this->ui->listView->hide();
    this->ui->label->hide();
    this->ui->label_2->hide();
    this->ui->pushButton->hide();
    this->ui->pushButton_2->hide();
    this->ui->pushButton_3->hide();
    this->ui->pushButton_4->hide();
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

void UserPanel::on_pushButton_4_clicked()
{
    // Trigger a input box to the room id

    bool ok;
    QString file_id_str = QInputDialog::getText(this, tr("Which file"),
                                         tr("Insert file id here "), QLineEdit::Normal,
                                         QDir::home().dirName(), &ok);

    std::string::size_type sz;
    int file_id = std::stoi(file_id_str.toUtf8().constData(), &sz);

    json request;
    request["action"] = "JOIN_ROOM_INTENT";
    request["file_id"] = file_id;
    request["username"] = sm.get_username();

    clsock.write_msg(request.dump());

    json answer = json::parse(clsock.read_msg());

    if (answer["action"].get<std::string>() == "ROOM_DOES_NOT_EXIST")
    {
        qInfo() << "[ROOM CONNECT] Tried to edit a file in an invalid room";

        Mbox = new QMessageBox();
        Mbox->setText("No one is editing a file in a room with this id, sorry bro");
        Mbox->show();
    }
    else if (answer["action"].get<std::string>() == "ROOM_JOIN_INTENT_OK")
    {
        qInfo() << "[ROOM CONNECT] Connected to the room successfully";

        std::string fullfilename = answer["author"].get<std::string>() + "/" +
                answer["filename"].get<std::string>();

        editFile = new FileEdit(this);
        editFile->set_filename(fullfilename);
        editFile->handle_room_logic();
        editFile->show();
        this->ui->listView->hide();
        this->ui->label->hide();
        this->ui->label_2->hide();
        this->ui->pushButton->hide();
        this->ui->pushButton_2->hide();
        this->ui->pushButton_3->hide();
        this->ui->pushButton_4->hide();

    }
}
