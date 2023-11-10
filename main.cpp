#include "mainwindow.h"

#include <QApplication>
#include "mainwindow.h"
#include "QMessageBox"
#include <windows.h>

bool isDebuggerPresent() {
    if (IsDebuggerPresent()) {
        QMessageBox::critical(nullptr, "Ошибка", "Подключен Debugger");
        return true;
    }
    return false;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    if (isDebuggerPresent()){
        exit(-1);
    }
    return a.exec();
}
