//
// Created by noartem on 27.06.2022.
//

#ifndef DIARY_SCROLL_H
#define DIARY_SCROLL_H

#include "elementor.h"

class Scroll : public Element {
public:
    Scroll();

    Scroll *setChild(const std::shared_ptr<Element>& child);

    Size getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, Boundaries boundaries) override;

    std::vector <RenderElement> getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) override;

private:
    std::shared_ptr<Scrollbar> childScrollbar;
    std::shared_ptr<Scrollable> childScrollable;
};

Scroll *scroll();

#endif //DIARY_SCROLL_H
