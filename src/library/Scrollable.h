//
// Created by noartem on 22.05.2022.
//

#ifndef ELEMENTOR_SCROLLABLE_H
#define ELEMENTOR_SCROLLABLE_H

#include "Element.h"
#include "Event.h"

#include <functional>

namespace elementor {
    class Scrollable : public Element, public WithOnMouseMove, public WithOnScroll, WithChild {
    public:
        Scrollable *setScrollableTop(float scrollableTop);

        float getScrollableTop();

        Scrollable *setScrollableLeft(float scrollableTop);

        float getScrollableLeft();

        Scrollable *setScrollableAcceleration(float scrollableAcceleration);

        float getScrollableAcceleration();

        Scrollable *setChild(Element *child);

        Size getSize(Boundaries boundaries) override;

        void paintBackground(SkCanvas *canvas, ElementRect rect) override;

        std::vector <RenderElement> getRenderChildren(Size size) override;

        ClipBehavior getClipBehaviour();

        EventCallbackResponse onEvent(EventMouseMove *event);

        EventCallbackResponse onEvent(EventScroll *event);

    private:
        ElementRect rect;
        float scrollableLeft;
        float scrollableTop;
        float scrollableAcceleration = 16.0;
        Size childSize;
        bool hovered;
    };

    Scrollable *scrollable();
}


#endif //ELEMENTOR_SCROLLABLE_H
