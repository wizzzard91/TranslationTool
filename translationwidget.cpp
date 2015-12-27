#include "translationwidget.h"
#include "ui_translationwidget.h"

#include <QDebug>

TranslationWidget::TranslationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TranslationWidget)
{
    ui->setupUi(this);
}

TranslationWidget::~TranslationWidget()
{
    delete ui;
}

void TranslationWidget::setChangedFile(QString filename) {
    thisFile = filename;
}

void TranslationWidget::setText(QString fieldName, QString fieldText) {
    QString translatedText = "";
    if(translatedFields.contains(thisFile))
        translatedText = translatedFields.value(thisFile)->value(fieldName);

    if(translatedText == "")
        ui->textEdit->setText(fieldText);
    else
        ui->textEdit->setText(translatedText);
}

void TranslationWidget::prepareToTranslate(QString fieldName) {
    currentFieldName = fieldName;
    ui->textEdit->setFocus();
    ui->textEdit->selectAll();
}

void TranslationWidget::on_btnSave_clicked()
{
    if(!translatedFields.contains(thisFile)) {
        translatedFields.insert(thisFile,new FIELD());
    }
    translatedFields.value(thisFile)->insert(currentFieldName,ui->textEdit->toPlainText());
    qDebug() << "Added translation" << currentFieldName << ui->textEdit->toPlainText() << "file" << thisFile;\

    // Automatically select next field

}
void TranslationWidget::on_btnGenTranslation_clicked()
{

}
