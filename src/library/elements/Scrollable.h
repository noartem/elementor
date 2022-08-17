//
// Created by noartem on 22.05.2022.
//

#ifndef ELEMENTOR_SCROLLABLE_H
#define ELEMENTOR_SCROLLABLE_H

#include "../Element.h"
#include "../Event.h"

namespace elementor::elements {
    enum class ScrollDirection {
        Vertical,
        Horizontal,
        Both,
    };

    class Scrollable : public Element, public WithOnMouseMove, public WithOnScroll, public WithChild {
    public:
        Scrollable *setDirection(ScrollDirection direction);

        ScrollDirection getDirection();

        bool isHorizontalScroll();

        bool isVerticalScroll();

        float getHeight();

        float getWidth();

        float getMaxScrollLeft();

        float getMaxScrollTop();

        Scrollable *setScrollTop(float scrollTop);

        float getScrollTop();

        Scrollable *setScrollLeft(float scrollTop);

        float getScrollLeft();

        float getScrollHeight();

        float getScrollWidth();

        Scrollable *setScrollAcceleration(float scrollAcceleration);

        float getScrollAcceleration();

        Scrollable *setChild(Element *child);

        Size getChildSize(ApplicationContext *ctx, Window *window, Boundaries boundaries);

        Size getSize(ApplicationContext *ctx, Window *window, Boundaries boundaries) override;

        void paintBackground(ApplicationContext *ctx, Window *window, SkCanvas *canvas, ElementRect rect) override;

        std::vector <RenderElement> getChildren(ApplicationContext *ctx, Window *window, Size size) override;

        ClipBehavior getClipBehaviour() override;

        EventCallbackResponse onEvent(EventMouseMove *event) override;

        EventCallbackResponse onEvent(EventScroll *event) override;

    private:
        ApplicationContext *ctx;
        ElementRect rect;
        ScrollDirection direction = ScrollDirection::Both;
        float scrollLeft;
        float scrollTop;
        float scrollAcceleration = 16.0;
        Size childSize;
        bool hovered;
    };

    Scrollable *scrollable();
}


#endif //ELEMENTOR_SCROLLABLE_H
