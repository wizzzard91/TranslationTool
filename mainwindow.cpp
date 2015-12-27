#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QSettings>
#include <QString>
#include <QStringListIterator>
#include <QList>
#include <QFile>
#include <QDir>

QString mainFile = "D:\\Games\\Steam\\SteamApps\\common\\Europa Universalis IV\\COPY_localisation";
QString thisLanguage = "russian";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSettings settings;

    fillTree();
    connect(ui->filesView,SIGNAL(itemExpanded(QTreeWidgetItem*)),
            this,SLOT(itemExpanded(QTreeWidgetItem*)));
    connect(ui->filesView,SIGNAL(itemClicked(QTreeWidgetItem*,int)),
            this,SLOT(itemClicked(QTreeWidgetItem*,int)));

    auto filename = QString("\\achievements_l_english.yml");
    QFile file(mainFile + filename);
    if(checkFile(file,filename)) {
        while (!file.atEnd()) {
            auto line = file.readLine();
            processLine(line);
        }
    }
}

void MainWindow::fillTree() {
    QDir dir(mainFile);
    auto unprocessedFiles = dir.entryList(QDir::Files,QDir::Name);

    originaLanguages.clear();
    QStringList files;
    for(auto unprocessedFilesIter: unprocessedFiles) {
        auto filename = unprocessedFilesIter;
        auto nameAndLang = filename.split("_l_");
        if(nameAndLang.size() == 2) {
            if(!files.contains(nameAndLang.at(0)))
                files.append(nameAndLang.at(0));
            if(!originaLanguages.contains(nameAndLang.at(1)) && thisLanguage != nameAndLang.at(1))
                originaLanguages.append(nameAndLang.at(1));
        }
    }
    for(auto filesIter: files)
        qDebug() << filesIter;
    for(auto origLangIter: originaLanguages)
        qDebug() << origLangIter;

    // Filling tree
    ui->filesView->setColumnCount(1);
    QList<QTreeWidgetItem *> items;
//    for(int i = 0; i < files.size(); i++) {
    for(auto filesIter: files) {
        auto* rootItem = new QTreeWidgetItem((QTreeWidget*)0,QStringList(filesIter));
        rootItem->setChildIndicatorPolicy(QTreeWidgetItem::ChildIndicatorPolicy::ShowIndicator);
        items.append(rootItem);
    }
    ui->filesView->insertTopLevelItems(0, items);
}

void MainWindow::itemExpanded(QTreeWidgetItem * item) {
    // Works on expanding file contents
    qDebug() << "Expanding" << item->text(0);
    if(item->childCount() != 0)
        return;
    for(int i = 0; i < originaLanguages.size(); i++) {
        auto filename = item->text(0) + "_l_" + originaLanguages.at(i);
        QFile file(mainFile + "\\" + filename);
        if(checkFile(file,filename)) {
            file.readLine(); // skipping first line with "l_<language>". Should never fall here due to checkFile()
            while (!file.atEnd()) {
                auto line = file.readLine();
                auto translationElement = processLine(line);
                translationElement = translationElement.trimmed();
                auto splittedField = translationElement.split(":");
                QString fieldName;
                QString fieldText;
                if(splittedField.size() > 1){
                    fieldName = splittedField.at(0);
                    QListIterator<QString> iter(splittedField);
                    iter.toFront();
                    iter.next();
                    while(iter.hasNext()) {
                        fieldText.append(iter.next());
                        if(iter.hasNext())
                            fieldText.append(":");
                    }
                    prepareTextField(fieldText);

                    FIELD* field = nullptr;
                    QTreeWidgetItem* fieldWidgetItem = nullptr;

                    if(!searchMap.contains(fieldName)) {   // checking if field is wasn't added to treeWidget earlier
                        fieldWidgetItem = new QTreeWidgetItem(item, QStringList(fieldName));
                        fieldWidgetItem->setChildIndicatorPolicy(QTreeWidgetItem::ChildIndicatorPolicy::DontShowIndicatorWhenChildless);
                        field = new FIELD();
                        field->insert(originaLanguages.at(i),fieldText);
                        searchMap.insert(fieldName,fieldWidgetItem);
                        fieldsMap.insert(fieldWidgetItem, field);
                    } else {    // if field is already added to treeWidget, just adding new pair in FIELD
                        fieldWidgetItem = searchMap.value(fieldName);
                        field = fieldsMap.value(fieldWidgetItem);
                        field->insert(originaLanguages.at(i),fieldText);
                    }
                }
            }
        }
    }
}

void MainWindow::itemClicked(QTreeWidgetItem *item, int column) {
    if(fieldsMap.contains(item)) {
        qDebug() << "Clicked" << item->text(0);
        auto fieldName = item->text(0);
        ui->originalView->setOriginalField("",*fieldsMap.value(item));
        ui->translationView->setChangedFile(item->parent()->text(0));
        ui->translationView->setText(fieldName,ui->originalView->getText());
        ui->translationView->prepareToTranslate(fieldName);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
