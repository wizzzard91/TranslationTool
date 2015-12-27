#ifndef TRANSLATIONWIDGET_H
#define TRANSLATIONWIDGET_H

#include <QWidget>
#include <QMap>

#include "utils.hpp"
#include "mainwindow.h"

namespace Ui {
class TranslationWidget;
}

class TranslationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TranslationWidget(QWidget *parent = 0);
    ~TranslationWidget();

    void setChangedFile(QString filename);
    void setText(QString fieldName, QString fieldText);
    void prepareToTranslate(QString fieldName);

private slots:
    void on_btnSave_clicked();

    void on_btnGenTranslation_clicked();

private:
    Ui::TranslationWidget *ui;
    QString currentFieldName;
    QMap<QString, FIELD*> translatedFields;
    QList<QString> changedFiles;
    QString thisFile;

};

#endif // TRANSLATIONWIDGET_H
