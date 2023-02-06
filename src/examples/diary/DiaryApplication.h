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

    std::shared_ptr<Element> makeElement();

private:
    DiaryService *diaryService;
    std::shared_ptr<Element> child;
    std::shared_ptr<Empty> activePageElement;
    PAGE_CHANGER pageChanger = [this] (Page *page) { this->changePage(page); };

    void changePage(Page *page);

    void loadFromFile();

    void saveToFile();

    std::shared_ptr<Element> makeAboutSection();

    std::shared_ptr<Element> makeLogo();

    std::vector<Page *> makePages();

    std::shared_ptr<Element> makePagesList();

    std::shared_ptr<Element> makeNewControl();

    std::shared_ptr<Element> makeLoadControl();

    std::shared_ptr<Element> makeSaveControl();

    std::shared_ptr<Element> makeControls();
};

#endif //DIARY_APPLICATION_H
