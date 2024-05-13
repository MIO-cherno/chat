#ifndef GLOBAL_H
#define GLOBAL_H

#include <QWidget>
#include <functional>
#include <QStyle>
#include <QRegularExpression>


/* 在C++中，extern关键字主要用于声明一个变量或函数是在其他文件或模块中定义的，
 * 或者用于链接到由其他编程语言（如C）编写的代码。它告诉编译器，这个实体（变量或函数）
 * 在程序的其他地方存在，并且可以在当前文件中被引用。
 *
 * function 返回值void 参数类型 QWidget*
*/
extern std::function<void(QWidget*)> repolish;//repolish用来根据属性刷新qss

#endif // GLOBAL_H
