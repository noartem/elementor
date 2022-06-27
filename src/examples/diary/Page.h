//
// Created by noartem on 27.06.2022.
//

#ifndef DIARY_PAGE_H
#define DIARY_PAGE_H

#include "utility.h"

class Page {
public:
    virtual std::string getName() = 0;

    virtual std::string getDescription() = 0;

    virtual Element *getScene() = 0;
};

#endif //DIARY_PAGE_H
