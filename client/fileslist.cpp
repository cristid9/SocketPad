#include "fileslist.h"
#include "ui_fileslist.h"
//#include "global_objs.h"

FilesList::FilesList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FilesList)
{
    ui->setupUi(this);
//    this->parent = parent;
//    std::vector<std::string> files = fm.get_user_files(sm.get_username());

//    for (auto file : files)
//    {
//        this->ui->listWidget->addItem(QString(file));
//    }
}

FilesList::~FilesList()
{
    delete ui;
}
