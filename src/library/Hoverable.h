//
// Created by noartem on 18.05.2022.
//

#ifndef ELEMENTOR_HOVERABLE_H
#define ELEMENTOR_HOVERABLE_H

#include "Element.h"
#include "Event.h"

#include <functional>

namespace elementor {
    class Hoverable : public Element, WithChild, public WithOnMouseMove {
    public:
        Hoverable *onEnter(std::function<void()> callback);

        Hoverable *onLeave(std::function<void()> callback);

        Hoverable *setChild(Element *child);

        Size getSize(Boundaries boundaries) override;

        void paintBackground(SkCanvas *canvas, Size size, Rect rect) override;

        std::vector <RenderElement> getRenderChildren(Size size) override;

        EventCallbackResponse onEvent(EventMouseMove *event);

    private:
        Rect rect;
        bool hovered;

        std::function<void()> callbackEnter;
        std::function<void()> callbackLeave;
    };

    Hoverable *hoverable();
}


#endif //ELEMENTOR_HOVERABLE_H
