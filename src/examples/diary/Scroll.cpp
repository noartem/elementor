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

Scroll *Scroll::setChild(const std::shared_ptr<Element>& child) {
    this->childScrollable->setChild(child);
    return shared_from_this();
}

Size Scroll::getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, Boundaries boundaries) {
    return this->childScrollbar->getSize(ctx, window, boundaries);
}

std::vector <RenderElement> Scroll::getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) {
    RenderElement childElement{this->childScrollbar, {0, 0}, rect.size};
    return {childElement};
}