#include "ReadDataFile.h"
#include <QCoreApplication>
#include <QFile>
#pragma execution_character_set("utf-8")
QList<VirtualDisk*>* ReadDataFile::getList() {
    QList<VirtualDisk*>* re = new QList<VirtualDisk*>();
    foreach(QFileInfo d, QDir::drives()) {
        QString d_ = d.absoluteFilePath();
        re->append(ReadLine(d_.replace("/","").replace(":","-&mh;+")+":0"));
    }
    QString pd = QCoreApplication::applicationDirPath();
    QFile file(pd+"/data");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        while (!file.atEnd()) {
            QString s(file.readLine());
            re->append(ReadLine(s));
        }
    }
    file.close();
    return re;
}

VirtualDisk* ReadDataFile::ReadLine(QString s) {
    QStringList sl = s.split(":");
    QString name;
    yunType t;
    QStringList arg;
    for (int i = 0; i < sl.size(); i++) {
        QString l = sl.at(i);
        l = l.replace("-&mh;+",":");
        if (i == 0) {
            name = l;
        }
        else if (i == 1) {
            QString t_ = l;
            t = (yunType)t_.toInt();
        }
        else {
            arg.append(l);
        }
    }
    switch (arg.size()){
    case 0:
        return new VirtualDisk(t, name);
    case 1:
        //return new VirtualDisk(t, name, arg[0]);
    case 2:
        return new VirtualDisk(t, name, arg[0], arg[1]);
    case 3:
        return new VirtualDisk(t, name, arg[0], arg[1], arg[2]);
    case 4:
        return new VirtualDisk(t, name, arg[0], arg[1], arg[2], arg[3]);
    default:
        break;
    }
}

void ReadDataFile::setLoginData(QStringList sl) {
    QString pd = QCoreApplication::applicationDirPath();
    QFile file(pd + "/data");
    QStringList sl_;
    if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        while (!file.atEnd()) {
            QString s(file.readLine());
            if (s.trimmed() == "") { continue; }
            if (s.split(":")[0] != sl[0]) {
                sl_.append(s);
            }
            else {
                QString s_ = "";
                for each (QString v in sl) {
                    if (s_ == "") {
                        s_ = v.replace(":", "-&mh;+");;
                    }
                    else {
                        s_ += ":" + v.replace(":", "-&mh;+");
                    }
                }
                sl_.append(s_);
            }
        }
        QString data = "";
        for each (QString v in sl_) {
            if (data == "") {
                data = v.trimmed();
            }
            else {
                data += "\n" + v.trimmed();
            }
        }
        file.close();
        if (file.open(QIODevice::WriteOnly | QIODevice::Text | QFile::Truncate)) {
            file.write(data.toUtf8());
        }
        file.close();

    }
    return;
}