/**
 * @file style_helper.h
 * @author yunyin (yunyin_jayyi@qq.com)
 * @brief change the style by qss
 * @version 0.0.1
 * @date 2024-04-07
 * 
 * @copyright Copyright (c) 2024
 * 
*/
#ifndef STYLE_HELPER_H
#define STYLE_HELPER_H
#include <QApplication>
#include <QFile>

/**
 * @brief Set the style object
 * 
 * @param a application for set
*/
void set_style(QApplication& a)
{
    QFile qss_file(":/stylesheet.qss");
    if(qss_file.open(QFile::ReadOnly)){
        QString style = QLatin1String(qss_file.readAll());
        a.setStyleSheet(style);
        qss_file.close();
    }
    else{
        qDebug() << "stylesheet.qss open failed";
    }
}

#endif // STYLE_HELPER_H
