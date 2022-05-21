//
// Created by noartem on 18.05.2022.
//

#ifndef ELEMENTOR_CLICKABLE_H
#define ELEMENTOR_CLICKABLE_H

#include "Element.h"
#include "Hoverable.h"
#include "Event.h"

#include <functional>

namespace elementor {
    class Clickable : public Element, public WithOnMouseButton {
    public:
        Clickable();

        Clickable *onButton(std::function<EventCallbackResponse(EventMouseButton *event)> callback);

        Clickable *onButton(std::function<void (EventMouseButton *event)> callback);

        Clickable *onClick(std::function<EventCallbackResponse()> callback);

        Clickable *onClick(std::function<void ()> callback);

        Clickable *onRightClick(std::function<EventCallbackResponse()> callback);

        Clickable *onRightClick(std::function<void ()> callback);

        Clickable *setChild(Element *child);

        Size getSize(Boundaries boundaries) override;

        std::vector <RenderElement> getRenderChildren(Size size) override;

        EventCallbackResponse onEvent(EventMouseButton *event);

    private:
        Rect rect;
        bool hovered;
        Hoverable *hoverable;

        std::function<EventCallbackResponse (EventMouseButton *event)> callbackButton;
        std::function<EventCallbackResponse ()> callbackClick;
        std::function<EventCallbackResponse ()> callbackRightClick;

        Hoverable *getChild();
    };

    Clickable *clickable();
}


#endif //ELEMENTOR_CLICKABLE_H
