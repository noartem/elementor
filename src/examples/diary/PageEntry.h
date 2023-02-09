//
// Created by noartem on 04.07.2022.
//

#ifndef DIARY_PAGE_ENTRY_H
#define DIARY_PAGE_ENTRY_H

#include "utility.h"
#include "Page.h"
#include "DiaryService.h"

class PageEntry: public Page, public std::enable_shared_from_this<PageEntry> {
public:
    PageEntry(const std::shared_ptr<DiaryService>& service, const std::shared_ptr<DiaryEntry>& entry, const std::shared_ptr<Page>& backPage, const PAGE_CHANGER& pageChanger);

    std::string getName() override;

    std::shared_ptr<Element> makeElement() override;

private:
    std::shared_ptr<DiaryService> service;
    std::shared_ptr<DiaryEntry> entry;
    PAGE_CHANGER pageChanger;
    std::shared_ptr<Page> backPage;
    std::u32string datetime;
    std::u32string duration;
    std::u32string place;

    void saveEntry();

    void deleteEntry();

    std::shared_ptr<Element> makeDatetimeField();

    std::shared_ptr<Element> makeDurationField();

    std::shared_ptr<Element> makePlaceField();

    std::shared_ptr<Element> makeForm();

    std::shared_ptr<Element> makeSaveControl();

    std::shared_ptr<Element> makeDeleteControl();

    std::shared_ptr<Element> makeControls();
};


#endif //DIARY_PAGE_ENTRY_H
