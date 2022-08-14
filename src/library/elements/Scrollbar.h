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

    class Scrollbar : public Element {
    public:
        Scrollbar *setScrollTrack(std::function<Element *()> scrollTrack);

        std::function<Element *()> getScrollTrack();

        Scrollbar *setScrollThumb(std::function<Element *()> scrollThumb);

        std::function<Element *()> getScrollThumb();

        Scrollbar *setPosition(ScrollbarPosition position);

        ScrollbarPosition getPosition();

        Scrollbar *setVisible(ScrollbarVisible visible);

        ScrollbarVisible getVisible();

        Scrollbar *setChild(Scrollable *child);

        Scrollbar *setChild(Element *child);

        Scrollable *getChild();

        Size getSize(ApplicationContext *ctx, Window *window, Boundaries boundaries) override;

        std::vector <RenderElement> getChildren(ApplicationContext *ctx, Window *window, Size size) override;

    private:
        Window *window;
        ScrollbarPosition position = ScrollbarPosition::InContent;
        ScrollbarVisible visible = ScrollbarVisible::WhenNeeded;
        Scrollable *child;
        Element *trackX;
        Element *thumbX;
        Element *trackY;
        Element *thumbY;
        std::function<Element *()> scrollTrack;
        std::function<Element *()> scrollThumb;

        void scrollToX(int x);

        void scrollToY(int y);

        void initChild();
    };

    Scrollbar *scrollbar();
}


#endif //ELEMENTOR_SCROLLBAR_H
