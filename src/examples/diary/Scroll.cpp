//
// Created by noartem on 27.06.2022.
//

#include "Scroll.h"

Scroll *scroll() {
    return new Scroll();
}

Scroll::Scroll() {
    this->childScrollable = scrollable()
        ->setDirection(ScrollDirection::Vertical);
    this->childScrollbar = scrollbar()
        ->setPosition(ScrollbarPosition::OnTop)
        ->setTrackY(width()
            ->setWidth(16))
        ->setThumbY(width()
            ->setWidth(16)
            ->setChild(padding()
                ->setPaddings(4)
                ->setChild(rounded()
                    ->setRadius(4)
                    ->setChild(background()
                        ->setColor("#BBB9AE")))))
        ->setChild(this->childScrollable);
}

Scroll *Scroll::setChild(Element *child) {
    this->childScrollable->setChild(child);
    return this;
}

Size Scroll::getSize(ApplicationContext *ctx, Window *window, Boundaries boundaries) {
    return this->childScrollbar->getSize(ctx, window, boundaries);
}

std::vector <RenderElement> Scroll::getChildren(ApplicationContext *ctx, Window *window, Size size) {
    RenderElement child;
    child.element = this->childScrollbar;
    child.size = size;
    child.position = {0, 0};
    return {child};
}