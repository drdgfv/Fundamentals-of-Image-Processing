#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setStyleSheet(
    "QMainWindow { background-color: #282c34; }"
    "QPushButton {"
    "    background-color: #004074ff;"
    "    color: white;"
    "    border: none;"
    "    padding: 8px 16px;"
    "    border-radius: 4px;"
    "}"
    "QPushButton:hover {" // Estilo quando o mouse está sobre o botão
    "    background-color: #035d96ff;"
    "    border: 1px solid #e6edf1ff;"
    "}"
    "QPushButton:pressed {" // Estilo quando o botão está sendo pressionado
    "    background-color: #035d96ff;"
    "}"
    "QLabel {"
    "    color: #f8f8f8ff;"
    "}"
    );
    
    MainWindow w;
    w.show();

    return a.exec();
}

