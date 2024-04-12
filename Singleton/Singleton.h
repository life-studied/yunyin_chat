/**
 * @file Singleton.hpp
 * @author yunyin (yunyin_jayyi@qq.com)
 * @brief singleton template
 * @version 0.1
 * @date 2024-04-12
 * 
 * @copyright Copyright (c) 2024
 * 
*/
#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include "../global.h"
#include <memory>

/**
 * @brief Singleton template
 * 
 * @tparam T object type
*/
template<typename T>
class Singleton
{
protected:
    Singleton() = default;
    Singleton(const Singleton<T>&) = delete;
    Singleton& operator=(const Singleton<T>&) = delete;

public:
    static std::shared_ptr<T> getInstance()
    {
        static std::shared_ptr<T> instance(new T);
        return instance;
    }
};

#endif
