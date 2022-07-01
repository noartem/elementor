//
// Created by noartem on 01.07.2022.
//

#ifndef DIARY_PAGE_HOME_H
#define DIARY_PAGE_HOME_H

#include "utility.h"
#include "Page.h"

class PageHome: public Page {
public:
    std::string getName() override;

    std::string getDescription() override;

    Element *getScene() override;
};


#endif //DIARY_PAGE_HOME_H
