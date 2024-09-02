#include <QRegularExpression>

#include "registerdialog.h"
#include "ui_registerdialog.h"
#include "../../Network/HttpMgr.h"
#include "../../global.h"

RegisterDialog::RegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    ui->password_edit->setEchoMode(QLineEdit::Password);
    ui->pass2_edit_->setEchoMode(QLineEdit::Password);

    ui->err_tip->setProperty("state", "normal");
    repolish(ui->err_tip);

    connect(HttpMgr::getInstance().get(), &HttpMgr::sig_reg_mod_finish, this, &RegisterDialog::slot_reg_mod_finish);

    initHttpHandlers();
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::showTip(QString str, bool b_ok)
{
    ui->err_tip->setText(str);
    if(b_ok)
    {
        ui->err_tip->setProperty("state", "normal");
    }
    else
    {
        ui->err_tip->setProperty("state", "err");
    }
    repolish(ui->err_tip);
}

void RegisterDialog::initHttpHandlers()
{
    _handlers.insert(ReqId::ID_GET_VARIFY_CODE, [this](const QJsonObject& jsonObj){
        int error = jsonObj["error"].toInt();
        if(error != ErrorCodes::SUCCESS)
        {
            showTip(tr("参数错误"));
            return;
        }
        auto email = jsonObj["email"].toString();
        showTip(tr("验证码已经发送到邮箱，注意查收"), true);
        qDebug() << "email is " << email;
    });

    _handlers.insert(ReqId::ID_REG_USER, [this](QJsonObject jsonObj){
        int error = jsonObj["error"].toInt();
        if(error != ErrorCodes::SUCCESS){
            showTip(tr("参数错误"),false);
            return;
        }
        auto email = jsonObj["email"].toString();
        showTip(tr("用户注册成功"), true);
        qDebug()<< "email is " << email ;
    });
}

void RegisterDialog::on_get_code_btn_clicked()
{
    //验证邮箱的地址正则表达式
    auto email = ui->email_edit->text();
    // 邮箱地址的正则表达式
    static QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    bool match = regex.match(email).hasMatch(); // 执行正则表达式匹配
    if(match){
        //发送http请求获取验证码
        QJsonObject json_obj;
        json_obj["email"] = email;
        HttpMgr::getInstance()->PostHttpReq(QUrl(gate_url_prefix+"/get_varifycode"),
                     json_obj, ReqId::ID_GET_VARIFY_CODE,Modules::REGISTER);
    }else{
        //提示邮箱不正确
        showTip(tr("邮箱地址不正确"));
    }
}

void RegisterDialog::slot_reg_mod_finish(ReqId id, QString res, ErrorCodes err)
{
    if(err != ErrorCodes::SUCCESS)
    {
        showTip(tr("网络请求错误"), false);
        return;
    }

    QJsonDocument json = QJsonDocument::fromJson(res.toUtf8());
    if(json.isEmpty())
    {
        showTip(tr("json解析失败"), false);
        return;
    }

    if(!json.isObject())
    {
        showTip(tr("json解析失败"), false);
        return;
    }

    _handlers[id](json.object());
    return;
}


void RegisterDialog::on_confirm_btn_clicked()
{
    if(ui->user_edit->text() == ""){
        showTip(tr("用户名不能为空"), false);
        return;
    }
    if(ui->email_edit->text() == ""){
        showTip(tr("邮箱不能为空"), false);
        return;
    }
    if(ui->password_edit->text() == ""){
        showTip(tr("密码不能为空"), false);
        return;
    }
    if(ui->pass2_edit_->text() == ""){
        showTip(tr("确认密码不能为空"), false);
        return;
    }
    if(ui->pass2_edit_->text() != ui->password_edit->text()){
        showTip(tr("密码和确认密码不匹配"), false);
        return;
    }
    if(ui->varify_edit->text() == ""){
        showTip(tr("验证码不能为空"), false);
        return;
    }
    //day11 发送http请求注册用户
    QJsonObject json_obj;
    json_obj["user"] = ui->user_edit->text();
    json_obj["email"] = ui->email_edit->text();
    json_obj["passwd"] = ui->password_edit->text();
    json_obj["confirm"] = ui->pass2_edit_->text();
    json_obj["varifycode"] = ui->varify_edit->text();
    HttpMgr::getInstance()->PostHttpReq(QUrl(gate_url_prefix+"/user_register"),
                                        json_obj, ReqId::ID_REG_USER,Modules::REGISTER);
}

