#ifndef FILEEDIT_H
#define FILEEDIT_H

#include <QWidget>

namespace Ui {
class FileEdit;
}

class FileEdit : public QWidget
{
    Q_OBJECT

public:
    explicit FileEdit(QWidget *parent = 0);
    ~FileEdit();

private:
    Ui::FileEdit *ui;
    QWidget *parent;
};

#endif // FILEEDIT_H
