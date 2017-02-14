#include "fileedit.h"
#include "ui_fileedit.h"
#include "global_objs.h"
#include "json.hpp"
#include "filechange.h"
#include <QString>
#include <QDebug>
#include <sstream>
#include <thread>

using json = nlohmann::json;

FileEdit::FileEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileEdit)
{
    ui->setupUi(this);
    this->parent = parent;
    propagator = false;
}

void FileEdit::init_room()
{
    QString split_container = QString::fromStdString(filename);

    QStringList parts = split_container.split("/");

    std::string author = parts.value(0).toUtf8().constData();

    std::string raw_file_name = parts.value(1).toUtf8().constData();

    json request = {
        {"action", "INIT_PEER_EDIT_FILE"},
        {"username", sm.get_username().c_str()},
        {"filename", raw_file_name.c_str()},
        {"author", author.c_str()}
    };

    clsock.write_msg(request.dump());

    json answer = json::parse(clsock.read_msg());

    Mbox = new QMessageBox();
    if (answer["action"].get<std::string>() == "ROOM_CREATED_SUCCESS")
    {
        Mbox->setText("Room created succesfully");
        Mbox->show();
    }
    else if (answer["action"].get<std::string>() == "ROOM_EXISTS")
    {

        Mbox->setText("Someone else started editing this file in peer mode");
        Mbox->show();
    }

    stringstream tmpstr;
    tmpstr << answer["room_id"].get<int>();

    file_id = answer["room_id"].get<int>();

    this->ui->label_3->setText(tmpstr.str().c_str());

}

void FileEdit::load_room_file_data()
{
    QStringList strlist = QString::fromStdString(filename).split("/");

    std::string file_text = fm.load_file(strlist.value(0).toUtf8().constData(),
                                         strlist.value(1).toUtf8().constData());

    this->ui->textEdit->setText(QString::fromStdString(file_text));
    qInfo() << QString("[TEXT LOADED] Loaded text with the value")
            << QString(file_text.c_str());

    current_file_text = file_text;
}

void FileEdit::handle_room_logic()
{
    init_room();
    load_room_file_data();
    current_file_text = this->ui->textEdit->toPlainText().toUtf8().constData();
    std::thread background_handler(&FileEdit::client_handler, this);

    background_handler.detach();
}

void FileEdit::client_handler()
{
    std::string response;

    while (true)
    {
        response = clsock.read_msg();
        json server_response = json::parse(response);

        if (server_response["action"].get<std::string>() == "PEER_EDIT_PROPAGATION")
        {
            qInfo() << "[PEER EDIT ACTION] a peer broadcasted a change";

            char target = server_response["target"].get<char>();
            ChangeType type = server_response["type"].get<ChangeType>();
            unsigned int pos = server_response["position"].get<int>();

            FileChange fl_change(pos, target, type);

            apply_change(fl_change, server_response["author"].get<std::string>());
        }
    }
}

void FileEdit::apply_change(FileChange change, std::string author)
{
    std::string tmp_txt = current_file_text;
    std::string tmp_update_info;



    switch (change.get_type())
    {
    case ChangeType::FILE_CHANGE_INSERT:
        qInfo() << "[TEXT EDIT CHANGED] insert performed "
                << change.get_pos() << " " << change.get_target();
        tmp_update_info = "User: " + author + "performed insertion";
        tmp_txt.insert(change.get_pos(), 1, change.get_target());
        break;
    case ChangeType::FILE_CHANGE_DELETE:
        qInfo() << "[TEXT EDIT CHANGED] delete perfomed";
        tmp_update_info = "User: " + author + "performed deletion";
        tmp_txt.erase(tmp_txt.begin() + change.get_pos());
        break;
    case ChangeType::FILE_CHANGE_REPLACE:
        qInfo() << "[TEXT EDIT PERFORMED] replace perfomed";
        tmp_update_info = "User: "  + author + "performed replace";
        tmp_txt[change.get_pos()] = change.get_target();
        break;
    }

    current_file_text = tmp_txt;
    update_info = tmp_update_info;

    qInfo() << "Now what"
            << QString::fromStdString(current_file_text);

    propagator = true;
    emit this->ui->pushButton_3->click();

}

void FileEdit::set_filename(std::string fn)
{
    filename = fn;
}

FileEdit::~FileEdit()
{
    delete ui;
}

void FileEdit::on_textEdit_textChanged()
{
    if (propagator)
    {
        propagator = false;
        return;
    }
    if (current_file_text == "") return;

    qInfo() << "[FILE EDIT] user has changed a character";

    std::string new_text = this->ui->textEdit->toPlainText().toUtf8().constData();

    FileChange fl_change = FileChange::detect_change(current_file_text, new_text);

    qInfo() << "[FILE EDIT] charachter "
            << QString(fl_change.get_target());

    current_file_text = new_text;

    qInfo() << "[FILE EDIT] Peer notify event broadcasted";

    json request;
    request["action"] = "PEER_NOTIFY_FILE_CHANGE";
    request["file_id"] = file_id;
    request["type"] = fl_change.get_type();
    request["position"] = fl_change.get_pos();
    request["target"] = fl_change.get_target();
    request["author"] = sm.get_username();
    // tmp hack
    request["new_text"] = new_text;

    clsock.write_msg(request.dump());
}


void FileEdit::on_pushButton_3_clicked()
{
    this->ui->textEdit->setText(QString::fromStdString(current_file_text));
}
