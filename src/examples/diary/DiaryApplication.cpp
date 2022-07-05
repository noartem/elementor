//
// Created by noartem on 27.06.2022.
//

#include "DiaryApplication.h"

#include "Scroll.h"

#include "portable-file-dialogs.h"

DiaryApplication::DiaryApplication(DiaryService *diaryService, std::vector<Page *> pages) {
    this->activePageElement = empty();

    this->child = background()
        ->setColor("#FFFBFF")
        ->setChild(flex()
            ->appendChild(flexible()
                ->setGrow(1)
                ->setChild(background()
                    ->setColor("#FFDAD8")
                    ->setChild(flex()
                        ->setDirection(FlexDirection::Column)
                        ->appendChild(padding()
                            ->setPaddings(18, 24)
                            ->setChild(text()
                                ->setFontColor("#2B1615")
                                ->setFontFamily("Times New Roman")
                                ->setFontWeight(600)
                                ->setFontSize(32)
                                ->setText("Diary")))
                        ->appendChild(flexible()
                            ->setChild(expandedWidth()
                                ->setChild(scroll()
                                    ->setChild(padding()
                                        ->setPaddings(12, 18)
                                        ->setChild(this->makePagesList(pages))))))
                        ->appendChild(padding()
                            ->setPaddings(18, 24)
                            ->setChild(flex()
                                ->setSpacing(8)
                                ->appendChild(flexible()
                                    ->setChild(clickable()
                                        ->onClick([diaryService] () {
                                            auto f = pfd::open_file("Choose file", pfd::path::home(), {"CSV Files", "*.csv"});
                                            if (f.result().size() > 0) {
                                                diaryService->add(readEntriesFromFile(f.result()[0]));
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
                                                            ->setText("Load"))))))))
                            ->appendChild(flexible()
                                ->setChild(clickable()
                                    ->onClick([diaryService] () {
                                        auto f = pfd::save_file("Choose file", pfd::path::home() + pfd::path::separator() + "diary.csv", {"CSV Files", "*.csv"}, pfd::opt::force_overwrite);
                                        if (f.result().size() > 0) {
                                            diaryService->saveToFile(f.result());
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
                                                        ->setText("Save")))))))))))))
            ->appendChild(flexible()
                ->setGrow(3)
                ->setChild(this->activePageElement)));
}

Column *DiaryApplication::makePagesList(std::vector<Page *> pages) {
    Column *pagesList = column();
    for (Page *page : pages) {
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
                ->onClick([this, page] () { this->setActivePage(page); }));
    }

    return pagesList;
}

void DiaryApplication::setActivePage(Page *page) {
    page->setPageChanger([this] (Page *newPage) { this->setActivePage(newPage); });
    this->activePageElement->setChild(page->getScene());
}

Size DiaryApplication::getSize(ApplicationContext *ctx, Boundaries boundaries) {
    return this->child->getSize(ctx, boundaries);
}

std::vector <RenderElement> DiaryApplication::getChildren(ApplicationContext *ctx, Size size) {
    RenderElement sceneElement;
    sceneElement.element = this->child;
    sceneElement.position = {0, 0};
    sceneElement.size = size;
    return {sceneElement};
}
