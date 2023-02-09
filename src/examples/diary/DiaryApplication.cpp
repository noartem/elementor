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
        std::vector<std::shared_ptr<DiaryEntry>> entries = readEntriesFromFile(paths[0]);
        this->diaryService->add(entries);
    }
}

void DiaryApplication::saveToFile() {
    std::string path = pfd::save_file("Choose file", pfd::path::separator() + "diary.csv", {"CSV Files", "*.csv"}).result();
    if (!path.empty()) {
        std::vector<std::shared_ptr<DiaryEntry>> entries = this->diaryService->findAll();
        saveEntriesToFile(path, entries);
    }
}

std::shared_ptr<Element> DiaryApplication::makeAboutSection() {
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

std::shared_ptr<Element> DiaryApplication::makeLogo() {
    return text()
        ->setFontColor("#2B1615")
        ->setFontFamily("Times New Roman")
        ->setFontWeight(600)
        ->setFontSize(32)
        ->setText("Diary");
}

void DiaryApplication::changePage(const std::shared_ptr<Page>& page) {
    this->activePageElement->setChild(page != nullptr ? page->makeElement() : this->makeAboutSection());
}

std::vector<std::shared_ptr<Page>> DiaryApplication::makePages() {
    return {
        std::make_shared<PageTodayEntries>(this->diaryService, this->pageChanger),
        std::make_shared<PageTomorrowEntries>(this->diaryService, this->pageChanger),
        std::make_shared<PageAllEntries>(this->diaryService, this->pageChanger),
    };
}

std::shared_ptr<Element> DiaryApplication::makePagesList() {
    std::shared_ptr<Column> pagesList = column();
    for (const auto& page : this->makePages()) {
        std::shared_ptr<Background> buttonBackground = background();
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

std::shared_ptr<Element> DiaryApplication::makeNewControl() {
    return clickable()
        ->onClick([this] () {
            this->changePage(std::make_shared<PageEntry>(this->diaryService, nullptr, nullptr, this->pageChanger));
        })
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

std::shared_ptr<Element> DiaryApplication::makeLoadControl() {
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

std::shared_ptr<Element> DiaryApplication::makeSaveControl() {
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

std::shared_ptr<Element> DiaryApplication::makeControls() {
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

DiaryApplication::DiaryApplication(const std::shared_ptr<DiaryService>& diaryService) {
    this->diaryService = diaryService;

    this->activePageElement = empty();
    this->element = background()
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
                            ->setChild(scroll()
                                ->setChild(padding()
                                    ->setPaddings(12, 18)
                                    ->setChild(this->makePagesList()))))
                        ->appendChild(padding()
                            ->setPaddings(18, 24)
                            ->setChild(this->makeControls())))))
            ->appendChild(flexible()
                ->setGrow(3)
                ->setChild(this->activePageElement
                    ->setChild(this->makeAboutSection()))));
}
