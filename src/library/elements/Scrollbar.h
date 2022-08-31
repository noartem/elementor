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
        Scrollbar *setTrackX(Element *trackX);
        Scrollbar *setTrackY(Element *trackY);
        Scrollbar *setThumbX(Element *thumbX);
        Scrollbar *setThumbY(Element *thumbY);

        Scrollbar *setPosition(ScrollbarPosition position);
        ScrollbarPosition getPosition();

        Scrollbar *setVisible(ScrollbarVisible visible);
        ScrollbarVisible getVisible();

        Scrollbar *setMinThumbSize(float size);
        float getMinThumbSize();

        Scrollbar *setChild(Scrollable *child);
        Scrollable *getChild();

        Size getSize(ApplicationContext *ctx, Window *window, Boundaries boundaries) override;
        std::vector <RenderElement> getChildren(ApplicationContext *ctx, Window *window, Size size) override;

    private:
        ScrollbarPosition position = ScrollbarPosition::InContent;
        ScrollbarVisible visible = ScrollbarVisible::WhenNeeded;

        Scrollable *child;

        Element *trackX;
        Element *trackY;
        Element *thumbX;
        Element *thumbY;

        float dragginLastPositionY;
        float dragginLastPositionX;
        void scrollToX(int x);
        void scrollToY(int y);

        void initChild();
    };

    Scrollbar *scrollbar();
}


#endif //ELEMENTOR_SCROLLBAR_H
