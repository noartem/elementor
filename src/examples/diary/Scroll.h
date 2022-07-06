//
// Created by noartem on 27.06.2022.
//

#ifndef DIARY_SCROLL_H
#define DIARY_SCROLL_H

#include "elementor.h"

class Scroll : public Element {
public:
    Scroll();

    Scroll *setChild(Element *child);

    Size getSize(ApplicationContext *ctx, Boundaries boundaries) override;

    std::vector <RenderElement> getChildren(ApplicationContext *ctx, Size size) override;

private:
    Scrollbar *childScrollbar;
    Scrollable *childScrollable;
};

Scroll *scroll();

#endif //DIARY_SCROLL_H
