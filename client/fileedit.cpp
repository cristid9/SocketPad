#include "fileedit.h"
#include "ui_fileedit.h"

FileEdit::FileEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileEdit)
{
    ui->setupUi(this);
    this->parent = parent;
}

FileEdit::~FileEdit()
{
    delete ui;
}
