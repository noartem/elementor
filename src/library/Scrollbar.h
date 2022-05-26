//
// Created by noartem on 26.05.2022.
//

#ifndef ELEMENTOR_SCROLLBAR_H
#define ELEMENTOR_SCROLLBAR_H

#include "Element.h"
#include "Scrollable.h"

#include <functional>

namespace elementor {

    class Scrollbar : public Element {
    public:
        Scrollbar *setScrollTrack(std::function<Element *()> scrollTrack);

        std::function<Element *()> getScrollTrack();

        Scrollbar *setScrollThumb(std::function<Element *()> scrollThumb);

        std::function<Element *()> getScrollThumb();

        Scrollbar *setChild(Scrollable *child);

        Scrollbar *setChild(Element *child);

        Scrollable *getChild();

        Size getSize(ApplicationContext *ctx, Boundaries boundaries) override;

        std::vector <RenderElement> getChildren(ApplicationContext *ctx, Size size) override;

    private:
        Scrollable *child;
        std::function<Element *()> scrollTrack;
        std::function<Element *()> scrollThumb;
    };

    Scrollbar *scrollbar();
}


#endif //ELEMENTOR_SCROLLBAR_H
