//
// Created by noartem on 27.06.2022.
//

#ifndef DIARY_PAGE_H
#define DIARY_PAGE_H

#include "utility.h"

#define PAGE_CHANGER std::function<void (Page *page)>

class Page {
public:
    virtual std::string getName() = 0;

    virtual Element *getScene() = 0;

    virtual void setPageChanger(PAGE_CHANGER pageChanger) {};
};

#endif //DIARY_PAGE_H
