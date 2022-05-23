//
// Created by noartem on 22.05.2022.
//

#ifndef ELEMENTOR_SCROLLABLE_H
#define ELEMENTOR_SCROLLABLE_H

#include "Element.h"
#include "Event.h"

#include <functional>

namespace elementor {
    enum class ScrollDirection {
        Vertical,
        Horizontal,
        Both,
    };

    class Scrollable : public Element, public WithOnMouseMove, public WithOnScroll, WithChild {
    public:
        Scrollable *setDirection(ScrollDirection direction);

        ScrollDirection getDirection();

        Scrollable *setScrollTop(float scrollTop);

        float getScrollTop();

        Scrollable *setScrollLeft(float scrollTop);

        float getScrollLeft();

        Scrollable *setScrollAcceleration(float scrollAcceleration);

        float getScrollAcceleration();

        Scrollable *setChild(Element *child);

        Size getSize(Boundaries boundaries) override;

        void paintBackground(SkCanvas *canvas, ElementRect rect) override;

        std::vector <RenderElement> getRenderChildren(Size size) override;

        ClipBehavior getClipBehaviour();

        EventCallbackResponse onEvent(EventMouseMove *event);

        EventCallbackResponse onEvent(EventScroll *event);

    private:
        ScrollDirection direction = ScrollDirection::Both;
        ElementRect rect;
        float scrollLeft;
        float scrollTop;
        float scrollAcceleration = 16.0;
        Size childSize;
        bool hovered;
    };

    Scrollable *scrollable();
}


#endif //ELEMENTOR_SCROLLABLE_H
