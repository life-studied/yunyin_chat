/**
 * @file registerdialog.h
 * @author yunyin (yunyin_jayyi@qq.com)
 * @brief register dialog for login window
 * @version 0.0.1
 * @date 2024-04-09
 * 
 * @copyright Copyright (c) 2024
 * 
*/
#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>

#include "../../global.h"

namespace Ui {
class RegisterDialog;
}

/// @brief Dialog for Register, used in MainWindow by setCentralWidget
class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Construct a new Register Dialog object
     * 
     * @param parent parent object in QT object tree
    */
    explicit RegisterDialog(QWidget *parent = nullptr);

    /**
     * @brief Destroy the Register Dialog object
     * 
    */
    ~RegisterDialog();

private:
    void showTip(QString str, bool b_ok = false);
    void initHttpHandlers();
private slots:
    void on_get_code_btn_clicked();
    void slot_reg_mod_finish(ReqId id, QString res, ErrorCodes err);
    void on_confirm_btn_clicked();

private:
    QMap<ReqId, std::function<void(const QJsonObject&)>> _handlers;
    Ui::RegisterDialog *ui;     ///< ui object from designer
};

#endif // REGISTERDIALOG_H
