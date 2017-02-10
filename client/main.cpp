#include "mainwindow.h"
#include "sessionmanager.h"
#include "clsock.h"
#include "usermanager.h"
#include <QApplication>
#include <QDebug>
#include "global_objs.h"


int main(int argc, char *argv[])
{
    qSetMessagePattern("%{file}(%{line}): %{message}");
    clsock.connect_serv();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
