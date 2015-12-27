#ifndef UTILS_HPP
#define UTILS_HPP

#include <QFile>
#include <QString>
#include <QDebug>

#ifndef FIELD
    // FIELD contains <fieldLanguage, fieldText>
    #define FIELD QMap<QString,QString>
#endif

bool checkFile(QFile& file, QString filename);
QString processLine(QByteArray line);
void prepareTextField(QString &fieldText);

#endif // UTILS_HPP
