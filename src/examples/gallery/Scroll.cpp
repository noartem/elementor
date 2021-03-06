//
// Created by noartem on 30.05.2022.
//

#include "Scroll.h"

Element *scrollTrack() {
    return width()
        ->setWidth(16)
        ->setChild(height()
            ->setHeight(16));
}

Element *scrollThumb() {
    return padding()
        ->setPaddings(4)
        ->setChild(rounded()
            ->setRadius(4)
            ->setChild(background()
                ->setColor("#BBB9AE")));
}

Scroll *scroll() {
    return new Scroll();
}

Scroll::Scroll() {
    this->childScrollable = scrollable()
        ->setDirection(ScrollDirection::Vertical);
    this->childScrollbar = scrollbar()
        ->setScrollTrack(scrollTrack)
        ->setScrollThumb(scrollThumb)
        ->setChild(this->childScrollable);
}

Scroll *Scroll::setChild(Element *child) {
    this->childScrollable->setChild(expandedWidth()->setChild(child));
    return this;
}

Size Scroll::getSize(ApplicationContext *ctx, Boundaries boundaries) {
    return this->childScrollbar->getSize(ctx, boundaries);
}

std::vector <RenderElement> Scroll::getChildren(ApplicationContext *ctx, Size size) {
    RenderElement child;
    child.element = this->childScrollbar;
    child.size = size;
    child.position = {0, 0};
    return {child};
}