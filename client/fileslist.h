#ifndef FILESLIST_H
#define FILESLIST_H

#include <QWidget>

namespace Ui {
class FilesList;
}

class FilesList : public QWidget
{
    Q_OBJECT

public:
    explicit FilesList(QWidget *parent = 0);
    ~FilesList();

private:
    Ui::FilesList *ui;
    QWidget *parent;
};

#endif // FILESLIST_H
