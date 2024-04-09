/**
 * @file mainwindow.h
 * @author yunyin (yunyin_jayyi@qq.com)
 * @brief main window in QT
 * @version 0.0.1
 * @date 2024-04-07
 * 
 * @copyright Copyright (c) 2024
 * 
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Widgets/Login/logindialog.h"
#include "Widgets/Register/registerdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/// @brief main window for show
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    /**
     * @brief Construct a new Main Window object
     * 
     * @param parent parent object in QT object tree
    */
    MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Destroy the Main Window object
     * 
    */
    ~MainWindow();

private:
    Ui::MainWindow *ui;     ///< default ui
    LoginDialog* _login_dlg = nullptr;      ///< login dialog
    RegisterDialog* _reg_dlg = nullptr;     ///< register dialog

public slots:
    /**
     * @brief slot for window switch from login to register
     * @see   Login::SwitchToRegister()
    */
    void SlotSwitchToRegister();
};
#endif // MAINWINDOW_H
