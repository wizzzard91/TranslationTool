#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>

#include "utils.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void itemExpanded(QTreeWidgetItem * item);
    void itemClicked(QTreeWidgetItem * item, int column);

private:
    Ui::MainWindow *ui;

    QStringList originaLanguages;
    QMap<QTreeWidgetItem*,FIELD*> fieldsMap;
    QMap<QString,QTreeWidgetItem*> searchMap;

    void fillTree();
};

#endif // MAINWINDOW_H
