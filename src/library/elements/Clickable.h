//
// Created by noartem on 18.05.2022.
//

#ifndef ELEMENTOR_CLICKABLE_H
#define ELEMENTOR_CLICKABLE_H

#include "../Element.h"
#include "../Event.h"

#include <functional>

namespace elementor::elements {
    class Clickable : public Element, public WithOnMouseButton, public WithOnMouseMove, WithChild {
    public:
        Clickable *onButton(std::function<EventCallbackResponse (EventMouseButton *event, Position position)> callback);

        Clickable *onButton(std::function<void ()> callback);

        Clickable *onClick(std::function<EventCallbackResponse (EventMouseButton *event, Position position)> callback);

        Clickable *onClick(std::function<void ()> callback);

        Clickable *onRightClick(std::function<EventCallbackResponse (EventMouseButton *event, Position position)> callback);

        Clickable *onRightClick(std::function<void ()> callback);

        Clickable *setChild(Element *child);

        Size getSize(ApplicationContext *ctx, Boundaries boundaries) override;

        void paintBackground(ApplicationContext *ctx, SkCanvas *canvas, ElementRect rect) override;

        std::vector <RenderElement> getChildren(ApplicationContext *ctx, Size size) override;

        EventCallbackResponse onEvent(EventMouseMove *event) override;

        EventCallbackResponse onEvent(EventMouseButton *event) override;

    private:
        ElementRect rect;
        Position cursorPosition;
        bool hovered;
        std::function<EventCallbackResponse (EventMouseButton *event, Position position)> callbackButton;
        std::function<EventCallbackResponse (EventMouseButton *event, Position position)> callbackClick;
        std::function<EventCallbackResponse (EventMouseButton *event, Position position)> callbackRightClick;
    };

    Clickable *clickable();
}


#endif //ELEMENTOR_CLICKABLE_H
