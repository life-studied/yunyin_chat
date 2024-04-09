#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>

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
    Ui::RegisterDialog *ui;     ///< ui object from designer
};

#endif // REGISTERDIALOG_H
