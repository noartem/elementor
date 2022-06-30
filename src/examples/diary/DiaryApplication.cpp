//
// Created by noartem on 27.06.2022.
//

#include "DiaryApplication.h"

#include "Scroll.h"

DiaryApplication::DiaryApplication(std::vector<Page *> pages) {
    this->pages = pages;

    this->activePageElement = empty();
    this->activePageLabel = empty();
    this->activePageDescription = empty();

    this->scene = background()
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
                                        ->setChild(this->makePagesList()))))))))
            ->appendChild(flexible()
                ->setGrow(3)
                ->setChild(flex()
                    ->setDirection(FlexDirection::Column)
                    ->appendChild(padding()
                        ->setPaddings(12, 18)
                        ->setChild(column()
                            ->setSpacing(8)
                            ->appendChild(this->activePageLabel)
                            ->appendChild(this->activePageDescription)))
                    ->appendChild(flexible()
                        ->setChild(this->activePageElement)))));
}

void DiaryApplication::setActivePage(Page *page) {
    this->activePageElement
        ->setChild(page->getScene());

    this->activePageLabel
        ->setChild(height()
            ->setHeight(24)
            ->setChild(text()
                ->setFontColor("#2B1615")
                ->setFontFamily("Times New Roman")
                ->setFontSize(24)
                ->setText(page->getName())));

    this->activePageDescription
        ->setChild(text()
            ->setFontColor("#2B1615")
            ->setFontFamily("Times New Roman")
            ->setFontSize(18)
            ->setText(page->getDescription()));
}

Column *DiaryApplication::makePagesList() {
    Column *pagesList = column();
    for (Page *page : this->pages) {
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

std::vector <RenderElement> DiaryApplication::getChildren(ApplicationContext *ctx, Size size) {
    RenderElement sceneElement;
    sceneElement.element = this->scene;
    sceneElement.position = {0, 0};
    sceneElement.size = size;
    return {sceneElement};
}
