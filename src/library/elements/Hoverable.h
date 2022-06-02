//
// Created by noartem on 18.05.2022.
//

#ifndef ELEMENTOR_HOVERABLE_H
#define ELEMENTOR_HOVERABLE_H

#include "../Element.h"
#include "../Event.h"

#include <functional>

namespace elementor::elements {
    class Hoverable : public Element, public WithOnMouseMove, WithChild {
    public:
        Hoverable *onEnter(std::function<EventCallbackResponse (EventMouseMove *event)> callback);

        Hoverable *onEnter(std::function<void ()> callback);

        Hoverable *onMove(std::function<EventCallbackResponse (EventMouseMove *event)> callback);

        Hoverable *onMove(std::function<void ()> callback);

        Hoverable *onLeave(std::function<EventCallbackResponse (EventMouseMove *event)> callback);

        Hoverable *onLeave(std::function<void ()> callback);

        Hoverable *setChild(Element *child);

        Size getSize(ApplicationContext *ctx, Boundaries boundaries) override;

        void paintBackground(ApplicationContext *ctx, SkCanvas *canvas, ElementRect rect) override;

        std::vector <RenderElement> getChildren(ApplicationContext *ctx, Size size) override;

        EventCallbackResponse onEvent(EventMouseMove *event) override;

    private:
        ElementRect rect;
        bool hovered;

        std::function<EventCallbackResponse (EventMouseMove *event)> callbackEnter;
        std::function<EventCallbackResponse (EventMouseMove *event)> callbackMove;
        std::function<EventCallbackResponse (EventMouseMove *event)> callbackLeave;
    };

    Hoverable *hoverable();
}


#endif //ELEMENTOR_HOVERABLE_H
