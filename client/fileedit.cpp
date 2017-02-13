#include "fileedit.h"
#include "ui_fileedit.h"
#include "global_objs.h"
#include "json.hpp"
#include <QString>

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

}

void FileEdit::set_filename(std::string fn)
{
    filename = fn;
}

FileEdit::~FileEdit()
{
    delete ui;
}
