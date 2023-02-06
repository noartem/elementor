//
// Created by noartem on 26.05.2022.
//

#ifndef ELEMENTOR_SCROLLBAR_H
#define ELEMENTOR_SCROLLBAR_H

#include "../Element.h"
#include "Scrollable.h"

#include <functional>

namespace elementor::elements {
    enum class ScrollbarPosition {
        InContent,
        OnTop,
    };

    enum class ScrollbarVisible {
        WhenNeeded,
        Always,
    };

    class Scrollbar : public Element, public std::enable_shared_from_this<Scrollbar> {
    public:
        std::shared_ptr<Scrollbar> setTrackX(std::shared_ptr<Element> trackX);

        std::shared_ptr<Scrollbar> setTrackY(std::shared_ptr<Element> trackY);

        std::shared_ptr<Scrollbar> setThumbX(std::shared_ptr<Element> thumbX);

        std::shared_ptr<Scrollbar> setThumbY(std::shared_ptr<Element> thumbY);

        std::shared_ptr<Scrollbar> setPosition(ScrollbarPosition position);

        ScrollbarPosition getPosition();

        std::shared_ptr<Scrollbar> setVisible(ScrollbarVisible visible);

        ScrollbarVisible getVisible();

        std::shared_ptr<Scrollbar> setChild(std::shared_ptr<Scrollable> child);

        std::shared_ptr<Scrollable> getChild();

        Size getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window,
                     Boundaries boundaries) override;

        std::vector<RenderElement>
        getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) override;

    private:
        ScrollbarPosition position = ScrollbarPosition::InContent;
        ScrollbarVisible visible = ScrollbarVisible::WhenNeeded;

        std::shared_ptr<Scrollable> child;

        std::shared_ptr<Element> trackX;
        std::shared_ptr<Element> trackY;
        std::shared_ptr<Element> thumbX;
        std::shared_ptr<Element> thumbY;
    };

    std::shared_ptr<Scrollbar> scrollbar();
}


#endif //ELEMENTOR_SCROLLBAR_H
