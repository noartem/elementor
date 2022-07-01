//
// Created by noartem on 27.06.2022.
//

#ifndef DIARY_APPLICATION_H
#define DIARY_APPLICATION_H

#include "utility.h"
#include "Page.h"

class DiaryApplication: public Element {
public:
    DiaryApplication(Page *pageDefault, std::vector<Page *> pages);

    DiaryApplication(std::vector<Page *> pages) : DiaryApplication(NULL, pages) {};

    void setActivePage(Page *activeExample);

    std::vector <RenderElement> getChildren(ApplicationContext *ctx, Size size) override;

private:
    Element *scene;
    Page *activePage;
    Empty *activePageElement;
    Empty *activePageLabel;
    Empty *activePageDescription;
    std::vector<Page *> pages;

    Column *makePagesList();
};

#endif //DIARY_APPLICATION_H
