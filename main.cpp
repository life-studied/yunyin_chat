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
#include "Widgets/Style/style_helper.h"

/// @brief main entrance
/// @param argc param count
/// @param argv param array
/// @return error code
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    set_style(a);

    MainWindow w;
    w.show();
    return a.exec();
}


