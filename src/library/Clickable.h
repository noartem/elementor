//
// Created by noartem on 18.05.2022.
//

#ifndef ELEMENTOR_CLICKABLE_H
#define ELEMENTOR_CLICKABLE_H

#include "Element.h"
#include "Event.h"

#include <functional>

namespace elementor {
    class Clickable : public Element, public WithOnMouseButton, public WithOnMouseMove, WithChild {
    public:
        Clickable *onButton(std::function<EventCallbackResponse(EventMouseButton *event)> callback);

        Clickable *onButton(std::function<void (EventMouseButton *event)> callback);

        Clickable *onClick(std::function<EventCallbackResponse()> callback);

        Clickable *onClick(std::function<void ()> callback);

        Clickable *onRightClick(std::function<EventCallbackResponse()> callback);

        Clickable *onRightClick(std::function<void ()> callback);

        Clickable *setChild(Element *child);

        Size getSize(Boundaries boundaries) override;

        void paintBackground(SkCanvas *canvas, Size size, Rect rect) override;

        std::vector <RenderElement> getRenderChildren(Size size) override;

        EventCallbackResponse onEvent(EventMouseMove *event);

        EventCallbackResponse onEvent(EventMouseButton *event);

    private:
        Rect rect;
        bool hovered;
        std::function<EventCallbackResponse (EventMouseButton *event)> callbackButton;
        std::function<EventCallbackResponse ()> callbackClick;
        std::function<EventCallbackResponse ()> callbackRightClick;
    };

    Clickable *clickable();
}


#endif //ELEMENTOR_CLICKABLE_H
