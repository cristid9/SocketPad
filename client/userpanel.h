#ifndef USERPANEL_H
#define USERPANEL_H

#include <QWidget>
#include <QMessageBox>
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
    void reload_files();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::UserPanel *ui;
    QWidget *parent;
    FileEdit *editFile;
    void load_files();
    QMessageBox *Mbox;
};

#endif // USERPANEL_H
