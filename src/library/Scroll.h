//
// Created by noartem on 22.05.2022.
//

#ifndef ELEMENTOR_SCROLL_H
#define ELEMENTOR_SCROLL_H

#include "Element.h"
#include "Event.h"

#include <functional>

namespace elementor {
    class Scroll : public Element, public WithOnMouseMove, public WithOnScroll, WithChild {
    public:
        Scroll *setScrollTop(float scrollTop);

        float getScrollTop();

        Scroll *setScrollLeft(float scrollTop);

        float getScrollLeft();

        Scroll *setScrollAcceleration(float scrollAcceleration);

        float getScrollAcceleration();

        Scroll *setChild(Element *child);

        Size getSize(Boundaries boundaries) override;

        void paintBackground(SkCanvas *canvas, Size size, Rect rect) override;

        std::vector <RenderElement> getRenderChildren(Size size) override;

        ClipBehavior getClipBehaviour();

        EventCallbackResponse onEvent(EventMouseMove *event);

        EventCallbackResponse onEvent(EventScroll *event);

    private:
        Rect rect;
        float scrollLeft;
        float scrollTop;
        float scrollAcceleration = 16.0;
        Size childSize;
        bool hovered;
    };

    Scroll *scroll();
}


#endif //ELEMENTOR_SCROLL_H
