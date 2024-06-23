#ifndef SINGLETON_H
#define SINGLETON_H
#include <memory>
#include <mutex>
#include <iostream>
#include "global.h"

template <typename T>
class Singleton
{
protected:
    //设置为protected，确保子类可以正常构造 ?不是很懂
    Singleton() = default;
    Singleton(const Singleton<T>&) = delete;
    Singleton& operator=(const Singleton& st) = delete;
    static std::shared_ptr<T> _instance;//如果是模板类要在.h内，类外初始化；否则放在.cpp中初始化

public:

    static std::shared_ptr<T> GetInstance() {
        static std::once_flag s_flag;
        std::call_once(s_flag, [&]() {
            _instance = shared_ptr<T>(new T);
            //继承模版单例类的子类的构造会设置为private，make_shared无法访问私有的构造函数
        });

        return _instance;
    }
    // static T& getSingleton()
    // {
    //     static T instance;
    //     return instance;
    // }

    void PrintAddress() {
        std::cout << _instance.get() << endl;
    }
    ~Singleton() {
        std::cout << "this is singleton destruct" << std::endl;
    }
};

template <typename T>
std::shared_ptr<T> Singleton<T>::_instance = nullptr;

#endif // SINGLETON_H
