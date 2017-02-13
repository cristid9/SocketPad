#include "fileedit.h"
#include "ui_fileedit.h"
#include "global_objs.h"
#include "json.hpp"
#include "filechange.h"
#include <QString>
#include <QDebug>
#include <sstream>

using json = nlohmann::json;

FileEdit::FileEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileEdit)
{
    ui->setupUi(this);
    this->parent = parent;
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
    qInfo() << "[FILE EDIT] user has changed a character";

    std::string new_text = this->ui->textEdit->toPlainText().toUtf8().constData();

    FileChange fl_change = FileChange::detect_change(current_file_text, new_text);

    qInfo() << "[FILE EDIT] charachter "
            << QString(fl_change.get_target());

    current_file_text = new_text;

    qInfo() << "[FILE EDIT] Peer notify event broadcasted";

    std::string request_type;
    switch (fl_change.get_type())
    {
    case ChangeType::FILE_CHANGE_INSERT:
        request_type = "insert";
        break;
    case ChangeType::FILE_CHANGE_DELETE:
        request_type = "delete";
    case ChangeType::FILE_CHANGE_REPLACE:
        request_type = "replace";
    }

    json request;
    request["action"] = "PEER_NOTIFY_FILE_CHANGE";
    request["file_id"] = file_id;
    request["type"] = request_type;
    request["position"] = fl_change.get_pos();
    request["target"] = fl_change.get_target();

    clsock.write_msg(request.dump());
}
