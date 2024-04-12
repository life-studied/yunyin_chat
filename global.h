/**
 * @file global.h
 * @author yunyin (yunyin_jayyi@qq.com)
 * @brief common function and data defined in this file
 * @version 0.0.1
 * @date 2024-04-09
 * 
 * @copyright Copyright (c) 2024
 * 
*/
#ifndef GLOBAL_H
#define GLOBAL_H

#include <QWidget>
#include <functional>
#include <QStyle>

/**
 * @brief for reflushing qss
 * 
*/
extern std::function<void(QWidget*)> repolish;

/**
 * @brief http request id
 * 
*/
enum ReqId{
    ID_GET_VARIFY_CODE = 1001,
    ID_REG_USER = 1002,

};

/**
 * @brief http request module name
 * 
*/
enum Modules{
    REGISTER = 0
};

enum ErrorCodes{
    SUCCESS = 0,
    ERR_JSON = 1,
    ERR_NETWORK = 2
};


#endif 
