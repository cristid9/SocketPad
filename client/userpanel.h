#ifndef USERPANEL_H
#define USERPANEL_H

#include <QWidget>
#include "fileedit.h"

namespace Ui {
class UserPanel;
}

class UserPanel : public QWidget
{
    Q_OBJECT

public:
    explicit UserPanel(QWidget *parent = 0);
    ~UserPanel();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::UserPanel *ui;
    QWidget *parent;
    FileEdit *editFile;
};

#endif // USERPANEL_H
