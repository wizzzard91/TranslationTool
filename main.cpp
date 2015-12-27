// EU4TranslationTool

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("wizzzard");
    QCoreApplication::setOrganizationDomain("vk.com/wizzzard");
    QCoreApplication::setApplicationName("EU4TranslationTool");

    MainWindow w;
    w.show();

    return a.exec();
}
