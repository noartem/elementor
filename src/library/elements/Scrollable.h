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

    class Scrollable
            : public Element,
              public WithOnMouseMove,
              public WithOnScroll,
              public WithChild,
              public std::enable_shared_from_this<Scrollable> {
    public:
        std::shared_ptr<Scrollable> setDirection(ScrollDirection newDirection);

        ScrollDirection getDirection();

        bool isHorizontalScroll();

        bool isVerticalScroll();

        float getHeight() const;

        float getWidth() const;

        float getMaxScrollLeft() const;

        float getMaxScrollTop() const;

        std::shared_ptr<Scrollable> setScrollTop(float newScrollTop);

        float getScrollTop() const;

        std::shared_ptr<Scrollable> setScrollLeft(float newScrollLeft);

        float getScrollLeft() const;

        float getScrollHeight() const;

        float getScrollWidth() const;

        std::shared_ptr<Scrollable> setScrollAcceleration(float newScrollAcceleration);

        float getScrollAcceleration() const;

        std::shared_ptr<Scrollable> setChild(const std::shared_ptr<Element>& child);

        Size
        getChildSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, Boundaries boundaries);

        Size getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window,
                     Boundaries boundaries) override;

        void paintBackground(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, SkCanvas *canvas,
                             ElementRect rect) override;

        std::vector<RenderElement>
        getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) override;

        ClipBehavior getClipBehaviour() override;

        EventCallbackResponse onEvent(std::shared_ptr<EventMouseMove> event) override;

        EventCallbackResponse onEvent(std::shared_ptr<EventScroll> event) override;

    private:
        std::shared_ptr<ApplicationContext> ctx;
        ElementRect rect;
        ScrollDirection direction = ScrollDirection::Both;
        float scrollLeft;
        float scrollTop;
        float scrollAcceleration = 16.0;
        Size childSize;
        bool hovered;
    };

    std::shared_ptr<Scrollable> scrollable();
}


#endif //ELEMENTOR_SCROLLABLE_H
