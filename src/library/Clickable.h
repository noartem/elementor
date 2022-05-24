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

        Size getSize(ApplicationContext *ctx, Boundaries boundaries) override;

        void paintBackground(ApplicationContext *ctx, SkCanvas *canvas, ElementRect rect) override;

        std::vector <RenderElement> getRenderChildren(ApplicationContext *ctx, Size size) override;

        EventCallbackResponse onEvent(EventMouseMove *event);

        EventCallbackResponse onEvent(EventMouseButton *event);

    private:
        ElementRect rect;
        bool hovered;
        std::function<EventCallbackResponse (EventMouseButton *event)> callbackButton;
        std::function<EventCallbackResponse ()> callbackClick;
        std::function<EventCallbackResponse ()> callbackRightClick;
    };

    Clickable *clickable();
}


#endif //ELEMENTOR_CLICKABLE_H
