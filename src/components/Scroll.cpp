//
// Created by noartem on 30.05.2022.
//

#include "Scroll.h"

namespace elementor::components {
    Scroll *scroll() {
        return new Scroll();
    }

    Scroll::Scroll() {
        this->scrollableElement = scrollable();
        this->element = scrollbar()
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
                            ->setColor("#7FB6A4")))))
            ->setChild(this->scrollableElement
                ->setDirection(ScrollDirection::Vertical));
    }

    Scroll *Scroll::setChild(Element *child) {
        this->scrollableElement->setChild(child);
        return this;
    }
}