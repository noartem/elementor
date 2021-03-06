//
// Created by noartem on 27.06.2022.
//

#ifndef DIARY_APPLICATION_H
#define DIARY_APPLICATION_H

#include "utility.h"
#include "DiaryService.h"
#include "Page.h"

class DiaryApplication {
public:
    DiaryApplication(DiaryService *diaryService);

    Element *makeElement();

private:
    DiaryService *diaryService;
    Element *child;
    Empty *activePageElement;
    PAGE_CHANGER pageChanger = [this] (Page *page) { this->changePage(page); };

    void changePage(Page *page);

    void loadFromFile();

    void saveToFile();

    Element *makeAboutSection();

    Element *makeLogo();

    std::vector<Page *> makePages();

    Element *makePagesList();

    Element *makeNewControl();

    Element *makeLoadControl();

    Element *makeSaveControl();

    Element *makeControls();
};

#endif //DIARY_APPLICATION_H
