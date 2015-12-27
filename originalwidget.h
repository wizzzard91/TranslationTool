#ifndef ORIGINALWIDGET_H
#define ORIGINALWIDGET_H

#include <QWidget>
#include "utils.hpp"

namespace Ui {
class OriginalWidget;
}

class OriginalWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OriginalWidget(QWidget *parent = 0);
    ~OriginalWidget();

    void setOriginalField(QString fieldName, FIELD field);
    QString getText();

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_clicked();

private:
    Ui::OriginalWidget *ui;

    QString currentFieldName;
    QString currentLanguage;
    FIELD currentField;

    void showText(int pos);
};

#endif // ORIGINALWIDGET_H
