//
// Created by noartem on 30.06.2022.
//

#ifndef DIARY_PAGE_TODAY_ENTRIES_H
#define DIARY_PAGE_TODAY_ENTRIES_H

#include "utility.h"
#include "Page.h"
#include "DiaryService.h"

class PageTodayEntries: public Page, public std::enable_shared_from_this<PageTodayEntries> {
public:
    PageTodayEntries(const std::shared_ptr<DiaryService>& service, const PAGE_CHANGER& pageChanger);

    std::string getName() override;

    std::shared_ptr<Element> makeElement() override;

private:
    std::shared_ptr<DiaryService> service;
    PAGE_CHANGER pageChanger;
};


#endif //DIARY_PAGE_TODAY_ENTRIES_H
