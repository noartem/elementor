//
// Created by noartem on 30.05.2022.
//

#ifndef GALLERY_SCROLL_H
#define GALLERY_SCROLL_H

#include "utility.h"

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

#endif //GALLERY_SCROLL_H
