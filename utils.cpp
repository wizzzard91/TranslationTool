#include "utils.hpp"

bool checkFile(QFile& file, QString filename) {
    if(file.exists())
        qDebug() << "Reading file" << filename;
    else {
        qDebug() << "File" << filename << " doesn't exist";
        return false;
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Cannot read file" << filename;
        return false;
    }
    // file should have at least one line
    if(file.size() < 0)
        return false;
    return true;
}

QString processLine(QByteArray line) {
    auto str = QString(line.toStdString().c_str());
//    qDebug() << str;
    return str;
}

void prepareTextField(QString& fieldText) {
    fieldText.chop(1);
    fieldText.remove(0,2);
}
