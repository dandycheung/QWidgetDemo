﻿#include "appdata.h"
#include "qthelper.h"

QStringList AppData::Intervals = QStringList();
QStringList AppData::Datas = QStringList();
QStringList AppData::Keys = QStringList();
QStringList AppData::Values = QStringList();

QString AppData::SendFileName = "send.txt";
void AppData::readSendData()
{
    //读取发送数据列表
    AppData::Datas.clear();
    QString fileName = QString("%1/%2").arg(QtHelper::appPath()).arg(AppData::SendFileName);
    QFile file(fileName);
    if (file.size() > 0 && file.open(QFile::ReadOnly | QIODevice::Text)) {
        while (!file.atEnd()) {
            QString line = file.readLine();
            line = line.trimmed();
            line = line.replace("\r", "");
            line = line.replace("\n", "");
            if (!line.isEmpty()) {
                AppData::Datas.append(line);
            }
        }

        file.close();
    }

    //没有的时候主动添加点免得太空
    if (AppData::Datas.count() == 0) {
        AppData::Datas << "16 FF 01 01 E0 E1" << "16 FF 01 01 E1 E2";
    }
}

QString AppData::DeviceFileName = "device.txt";
void AppData::readDeviceData()
{
    //读取转发数据列表
    AppData::Keys.clear();
    AppData::Values.clear();
    QString fileName = QString("%1/%2").arg(QtHelper::appPath()).arg(AppData::DeviceFileName);
    QFile file(fileName);
    if (file.size() > 0 && file.open(QFile::ReadOnly | QIODevice::Text)) {
        while (!file.atEnd()) {
            QString line = file.readLine();
            line = line.trimmed();
            line = line.replace("\r", "");
            line = line.replace("\n", "");
            if (!line.isEmpty()) {
                QStringList list = line.split(";");
                QString key = list.at(0);
                QString value;
                for (int i = 1; i < list.count(); i++) {
                    value += QString("%1;").arg(list.at(i));
                }

                //去掉末尾分号
                value = value.mid(0, value.length() - 1);
                AppData::Keys.append(key);
                AppData::Values.append(value);
            }
        }

        file.close();
    }
}

void AppData::saveData(const QString &data)
{
    if (data.length() <= 0) {
        return;
    }

    QString fileName = QString("%1/%2.txt").arg(QtHelper::appPath()).arg(STRDATETIME);
    QFile file(fileName);
    if (file.open(QFile::WriteOnly | QFile::Text)) {
        file.write(data.toUtf8());
        file.close();
    }
}
