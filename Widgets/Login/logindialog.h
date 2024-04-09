#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui {
class LoginDialog;
}

/// @brief Dialog for Login, used in MainWindow by setCentralWidget
class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Construct a new Login Dialog object
     * 
     * @param parent parent object in QT object tree
    */
    explicit LoginDialog(QWidget *parent = nullptr);

    /**
     * @brief Destroy the Login Dialog object
     * 
    */
    ~LoginDialog();

private slots:
    /**
     * @brief register button clicked, emit signal
     * @see   switchToRegister()
    */
    void on_pushButton_3_clicked();

private:
    Ui::LoginDialog *ui;    ///< ui object from designer

signals:
    /**
     * @brief signal for switch to register dlg in mainwindow
     * @see   MainWindow::SlotSwitchToRegister()
    */
    void switchToRegister();
};

#endif // LOGINDIALOG_H
