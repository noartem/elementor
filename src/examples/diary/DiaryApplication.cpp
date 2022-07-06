//
// Created by noartem on 27.06.2022.
//

#include "DiaryApplication.h"

#include "PageTodayEntries.h"
#include "PageTomorrowEntries.h"
#include "PageAllEntries.h"

#include "portable-file-dialogs.h"

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

std::vector<Page *> DiaryApplication::makePages() {
    auto pageChanger = [this] (Page *page) { this->activePageElement->setChild(page->makeElement()); };
    return {
        new PageTodayEntries(this->diaryService, pageChanger),
        new PageTomorrowEntries(this->diaryService, pageChanger),
        new PageAllEntries(this->diaryService, pageChanger),
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
                ->onClick([this, page] () { this->activePageElement->setChild(page->makeElement()); }));
    }
    return pagesList;
}

Element *DiaryApplication::makeLoadControl() {
    return clickable()
        ->onClick([this] () {
            auto f = pfd::open_file("Choose file", "", {"CSV Files", "*.csv"});
            if (f.result().size() > 0) {
                this->diaryService->add(readEntriesFromFile(f.result()[0]));
            }
        })
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
        ->onClick([this] () {
            auto f = pfd::save_file("Choose file", pfd::path::separator() + "diary.csv", {"CSV Files", "*.csv"}, pfd::opt::force_overwrite);
            if (f.result().size() > 0) {
                this->diaryService->saveToFile(f.result());
            }
        })
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
    return flex()
        ->setSpacing(8)
        ->appendChild(flexible()
            ->setChild(this->makeLoadControl()))
        ->appendChild(flexible()
            ->setChild(this->makeSaveControl()));
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
