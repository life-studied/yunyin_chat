#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _login_dlg = new LoginDialog();
    setCentralWidget(_login_dlg);
    _login_dlg->show();

    connect(_login_dlg, &LoginDialog::switchToRegister, this, &MainWindow::SlotSwitchToRegister);
}

MainWindow::~MainWindow()
{
    delete ui;
    if(_login_dlg) delete _login_dlg;
    _login_dlg = nullptr;
    if(_reg_dlg)  delete _reg_dlg;
    _reg_dlg = nullptr;
}

void MainWindow::SlotSwitchToRegister()
{
    if(_reg_dlg == nullptr) _reg_dlg = new RegisterDialog();
    setCentralWidget(_reg_dlg);
    _login_dlg->hide();
    _reg_dlg->show();
}

