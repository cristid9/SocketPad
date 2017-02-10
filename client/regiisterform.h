#ifndef REGIISTERFORM_H
#define REGIISTERFORM_H

#include <QWidget>
#include <QMessageBox>
#include "usermanager.h"

namespace Ui {
class RegiisterForm;
}

class RegiisterForm : public QWidget
{
    Q_OBJECT

public:
    explicit RegiisterForm(QWidget *parent = 0);
    ~RegiisterForm();

private slots:
    void on_pushButton_clicked();

private:
    Ui::RegiisterForm *ui;
    QMessageBox *Mbox;
    QWidget *parent;
};

#endif // REGIISTERFORM_H
