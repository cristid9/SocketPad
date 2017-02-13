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
    void set_filename(std::string fn);

private:
    Ui::FileEdit *ui;
    QWidget *parent;
    /**
     * @brief Tell sthe server to create a new room for editing this file.
     */
    void init_room();
    std::string filename;
};

#endif // FILEEDIT_H
