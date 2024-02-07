//
// Created by noartem on 30.05.2022.
//

#include "Scroll.h"

namespace elementor::components {
    std::shared_ptr<Scroll> scroll() {
        return std::make_shared<Scroll>();
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

    std::shared_ptr<Scroll> Scroll::setChild(const std::shared_ptr<Element>& child) {
        this->scrollableElement->setChild(child);
        return shared_from_this();
    }
}