//
// Created by noartem on 27.06.2022.
//

#ifndef DIARY_APPLICATION_H
#define DIARY_APPLICATION_H

#include "utility.h"
#include "Page.h"

class DiaryApplication: public Element {
public:
    DiaryApplication(std::vector<Page *> pages);

    void setActivePage(Page *activeExample);

    Size getSize(ApplicationContext *ctx, Boundaries boundaries) override;

    std::vector <RenderElement> getChildren(ApplicationContext *ctx, Size size) override;

private:
    Element *child;
    Empty *activePageElement;

    Column *makePagesList(std::vector<Page *> pages);
};

#endif //DIARY_APPLICATION_H
