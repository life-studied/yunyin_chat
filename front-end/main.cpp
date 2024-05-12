/**
 * @file main.cpp
 * @author yunyin (yunyin_jayyi@qq.com)
 * @brief app entrance
 * @version 0.0.1
 * @date 2024-04-07
 * 
 * @copyright Copyright (c) 2024
 * 
*/
#include "mainwindow.h"

#include <QApplication>
#include <QSettings>
#include <QDir>
#include "Widgets/Style/style_helper.h"

/// @brief main entrance
/// @param argc param count
/// @param argv param array
/// @return error code
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    set_style(a);

    // 获取当前应用程序的路径
    QString app_path = QCoreApplication::applicationDirPath();
    // 拼接文件名
    QString fileName = "config.ini";
    QString config_path = QDir::toNativeSeparators(app_path +
                            QDir::separator() + fileName);
    QSettings settings(config_path, QSettings::IniFormat);
    QString gate_host = settings.value("GateServer/host").toString();
    QString gate_port = settings.value("GateServer/port").toString();
    gate_url_prefix = "http://"+gate_host+":"+gate_port;

    MainWindow w;
    w.show();
    return a.exec();
}


