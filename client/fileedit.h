#ifndef FILEEDIT_H
#define FILEEDIT_H

#include <QWidget>
#include <QMessageBox>

namespace Ui {
class FileEdit;
}

class FileEdit : public QWidget
{
    Q_OBJECT

public:
    explicit FileEdit(QWidget *parent = 0);
    ~FileEdit();
    void set_filename(std::string fn);
    /**
     * @brief Tells the server to create a new room for editing this file.
     */
    void init_room();

private:
    Ui::FileEdit *ui;
    QWidget *parent;
    std::string filename;
    QMessageBox *Mbox;
};

#endif // FILEEDIT_H
