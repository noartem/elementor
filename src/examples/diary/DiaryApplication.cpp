//
// Created by noartem on 27.06.2022.
//

#include "DiaryApplication.h"

#include "PageTodayEntries.h"
#include "PageTomorrowEntries.h"
#include "PageAllEntries.h"
#include "PageEntry.h"

#include "portable-file-dialogs.h"

void DiaryApplication::loadFromFile() {
    auto paths = pfd::open_file("Choose file", "", {"CSV", "*.csv"}).result();
    if (!paths.empty()) {
        std::vector<DiaryEntry *> entries = readEntriesFromFile(paths[0]);
        this->diaryService->add(entries);
    }
}

void DiaryApplication::saveToFile() {
    std::string path = pfd::save_file("Choose file", pfd::path::separator() + "diary.csv", {"CSV Files", "*.csv"}).result();
    if (!path.empty()) {
        std::vector<DiaryEntry *> entries = this->diaryService->findAll();
        saveEntriesToFile(path, entries);
    }
}

Element *DiaryApplication::makeAboutSection() {
    return padding()
        ->setPaddings(24, 36)
        ->setChild(column()
            ->setSpacing(4)
            ->appendChild(text()
                ->setFontColor("#2B1615")
                ->setFontFamily("Times New Roman")
                ->setFontSize(36)
                ->setText("Diary application"))
            ->appendChild(height()->setHeight(8))
            ->appendChild(text()
                ->setFontColor("#2B1615")
                ->setFontSize(16)
                ->setText("Author: Noskov Artem"))
            ->appendChild(text()
                ->setFontColor("#2B1615")
                ->setFontSize(16)
                ->setText("Contacts: nowasmawesome@gmail.com"))
            ->appendChild(text()
                ->setFontColor("#2B1615")
                ->setFontSize(16)
                ->setText("Source code: github.com/noartem/elementor")));
}

Element *DiaryApplication::makeLogo() {
    return text()
        ->setFontColor("#2B1615")
        ->setFontFamily("Times New Roman")
        ->setFontWeight(600)
        ->setFontSize(32)
        ->setText("Diary");
}

void DiaryApplication::changePage(Page *page) {
    Element *pageElement = page == NULL ? this->makeAboutSection() : page->makeElement();
    this->activePageElement->setChild(pageElement);
}

std::vector<Page *> DiaryApplication::makePages() {
    return {
        new PageTodayEntries(this->diaryService, this->pageChanger),
        new PageTomorrowEntries(this->diaryService, this->pageChanger),
        new PageAllEntries(this->diaryService, this->pageChanger),
    };
}

Element *DiaryApplication::makePagesList() {
    Column *pagesList = column();
    for (Page *page : this->makePages()) {
        Background *buttonBackground = background();
        pagesList
            ->appendChild(clickable()
                ->setChild(hoverable()
                    ->setChild(rounded()
                        ->setRadius(24)
                        ->setChild(buttonBackground
                            ->setColor("#FFDAD8")
                            ->setChild(padding()
                                ->setPaddings(12, 18)
                                ->setChild(text()
                                    ->setFontColor("#2B1615")
                                    ->setFontFamily("Times New Roman")
                                    ->setFontSize(20)
                                    ->setText(page->getName())))))
                    ->onEnter([buttonBackground] () { buttonBackground->setColor("#E5BEBD"); })
                    ->onLeave([buttonBackground] () { buttonBackground->setColor("#FFDAD8"); }))
                ->onClick([this, page] () { this->changePage(page); }));
    }
    return pagesList;
}

Element *DiaryApplication::makeNewControl() {
    return clickable()
        ->onClick([this] () { this->changePage(new PageEntry(this->diaryService, NULL, NULL, this->pageChanger)); })
        ->setChild(rounded()
            ->setRadius(6)
            ->setChild(background()
                ->setColor("#E5BEBD")
                ->setChild(padding()
                    ->setPaddings(12, 16)
                    ->setChild(alignWidth()
                        ->setCoef(0.5, 0.5)
                        ->setChild(text()
                            ->setFontColor("#001E28")
                            ->setFontSize(18)
                            ->setText("New"))))));
}

Element *DiaryApplication::makeLoadControl() {
    return clickable()
        ->onClick([this] () { this->loadFromFile(); })
        ->setChild(rounded()
            ->setRadius(6)
            ->setChild(background()
                ->setColor("#E5BEBD")
                ->setChild(padding()
                    ->setPaddings(12, 18, 12, 16)
                    ->setChild(alignWidth()
                        ->setCoef(0.5, 0.5)
                        ->setChild(text()
                            ->setFontColor("#001E28")
                            ->setFontSize(18)
                            ->setText("Load"))))));
}

Element *DiaryApplication::makeSaveControl() {
    return clickable()
        ->onClick([this] () { this->saveToFile(); })
        ->setChild(rounded()
            ->setRadius(6)
            ->setChild(background()
                ->setColor("#E5BEBD")
                ->setChild(padding()
                    ->setPaddings(12, 18, 12, 16)
                    ->setChild(alignWidth()
                        ->setCoef(0.5, 0.5)
                        ->setChild(text()
                            ->setFontColor("#001E28")
                            ->setFontSize(18)
                            ->setText("Save"))))));
}

Element *DiaryApplication::makeControls() {
    return column()
        ->setSpacing(8)
        ->appendChild(this->makeNewControl())
        ->appendChild(flex()
            ->setSpacing(8)
            ->appendChild(flexible()
                ->setChild(this->makeLoadControl()))
            ->appendChild(flexible()
                ->setChild(this->makeSaveControl())));
}

DiaryApplication::DiaryApplication(DiaryService *diaryService) {
    this->diaryService = diaryService;
    this->activePageElement = empty()->setChild(this->makeAboutSection());
}

Element *DiaryApplication::makeElement() {
    return background()
        ->setColor("#FFFBFF")
        ->setChild(flex()
            ->appendChild(width()
                ->setWidth(256)
                ->setChild(background()
                    ->setColor("#FFDAD8")
                    ->setChild(flex()
                        ->setDirection(FlexDirection::Column)
                        ->appendChild(padding()
                            ->setPaddings(18, 24)
                            ->setChild(this->makeLogo()))
                        ->appendChild(flexible()
                            ->setChild(expandedWidth()
                                ->setChild(scroll()
                                    ->setChild(padding()
                                        ->setPaddings(12, 18)
                                        ->setChild(this->makePagesList())))))
                        ->appendChild(padding()
                            ->setPaddings(18, 24)
                            ->setChild(this->makeControls())))))
            ->appendChild(flexible()
                ->setGrow(3)
                ->setChild(this->activePageElement)));
}
