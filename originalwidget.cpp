#include "originalwidget.h"
#include "ui_originalwidget.h"

QString defaultLanguage = "english.yml";

OriginalWidget::OriginalWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OriginalWidget)
{
    ui->setupUi(this);
    ui->pushButton->setEnabled(false);
    ui->pushButton->setToolTip("Current default language is " + defaultLanguage);
}

OriginalWidget::~OriginalWidget()
{
    delete ui;
}

void OriginalWidget::setOriginalField(QString fieldName, FIELD field) {
    currentLanguage = defaultLanguage;
    currentField = field;
    ui->comboBox->clear();
    QList<QString> languages = field.keys();

    if(!languages.isEmpty()) {
        ui->pushButton->setEnabled(true);
    } else
        ui->pushButton->setEnabled(false);

    ui->comboBox->insertItems(0,languages);
    int pos;
    if(languages.contains(currentLanguage))
        pos = languages.indexOf(defaultLanguage);
    else
        pos = 0;

    showText(pos);
}

void OriginalWidget::showText(int pos) {
    ui->comboBox->setCurrentIndex(pos);
    ui->textEdit->setText(currentField.value(ui->comboBox->currentText()));
}

void OriginalWidget::on_comboBox_currentIndexChanged(int index)
{
    showText(index);
}

void OriginalWidget::on_pushButton_clicked()
{
    defaultLanguage = ui->comboBox->currentText();
    ui->pushButton->setToolTip("Current default language is " + defaultLanguage);
}

QString OriginalWidget::getText() {
    return ui->textEdit->toPlainText();
}
