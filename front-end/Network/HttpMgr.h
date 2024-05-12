/**
 * @file HttpMgr.h
 * @author yunyin (yunyin_jayyi@qq.com)
 * @brief File defined Http Manager Class 
 * @version 0.0.1
 * @date 2024-04-12
 * 
 * @copyright Copyright (c) 2024
 * 
*/
#ifndef HTTP_MGR_H
#define HTTP_MGR_H

#include <QString>
#include <QUrl>
#include <QObject>
#include <QNetworkAccessManager>
#include <QJsonObject>
#include <QJsonDocument>

#include "../Singleton/Singleton.h"

class HttpMgr : public QObject, public Singleton<HttpMgr>, public std::enable_shared_from_this<HttpMgr>
{
    Q_OBJECT
public:
    ~HttpMgr() = default;
    HttpMgr();
public:
    void PostHttpReq(QUrl url, QJsonObject json, ReqId req_id, Modules mod);
private:
    QNetworkAccessManager _manager;

private slots:
    void slot_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod);

signals:
    void sig_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod);
    void sig_reg_mod_finish(ReqId id, QString res, ErrorCodes err);
};



#endif // HTTP_MGR_H
