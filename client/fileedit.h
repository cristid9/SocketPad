#ifndef FILEEDIT_H
#define FILEEDIT_H

#include <QWidget>
#include <QMessageBox>
#include "filechange.h"

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
    void handle_room_logic();

private slots:
    void on_textEdit_textChanged();

    void on_pushButton_3_clicked();

private:
    Ui::FileEdit *ui;
    QWidget *parent;
    std::string filename;
    bool propagator;

    /**
     * @brief Messy workaround for sharing update informations between the worker thread
     *        and the main thread.
     */
    std::string update_info;

    /**
     * @brief Stores the text displayed in the qedit box.
     */
    std::string current_file_text;
    QMessageBox *Mbox;
    /**
     * @brief file_id Id of the currently editted file.
     */
    unsigned int file_id;

    /**
     * @brief Tells the server to create a new room for editing this file.
     */
    void init_room();
    /**
     * @brief Load the text of the file that is edited.
     */
    void load_room_file_data();

    /**
     * @brief Updates the qedit according to the changes made by the peer.
     */
    void apply_change(FileChange change, std::string author);

    /**
     * @brief Spawned in a new thred, handles responses from the server.
     */
    void client_handler();
};

#endif // FILEEDIT_H
