#include "global.h"


std::function<void(QWidget *)> repolish = [](QWidget *w){
    w->style()->unpolish(w);//去掉旧的属性
    w->style()->polish(w);
};
