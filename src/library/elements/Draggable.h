//
// Created by noartem on 18.05.2022.
//

#ifndef ELEMENTOR_DRAGGABLE_H
#define ELEMENTOR_DRAGGABLE_H

#include "../Element.h"
#include "../Event.h"

#include <functional>

namespace elementor::elements {
    class Draggable : public Element, public WithOnMouseButton, public WithOnMouseMove, public WithChild {
    public:
        Draggable *onStart(std::function<bool (Position position, Position absolutePosition)> callback);
        Draggable *onStart(std::function<void ()> callback);

        Draggable *onEnd(std::function<void (Position position, Position absolutePosition)> callback);
        Draggable *onEnd(std::function<void ()> callback);

        Draggable *onMove(std::function<void (Position position, Position absolutePosition, Position diff)> callback);
        Draggable *onMove(std::function<void ()> callback);

        Draggable *setChild(Element *child);

        Size getSize(ApplicationContext *ctx, Window *window, Boundaries boundaries) override;

        void paintBackground(ApplicationContext *ctx, Window *window, SkCanvas *canvas, ElementRect rect) override;

        std::vector <RenderElement> getChildren(ApplicationContext *ctx, Window *window, ElementRect rect) override;

        EventCallbackResponse onEvent(EventMouseMove *event) override;

        EventCallbackResponse onEvent(EventMouseButton *event) override;

    private:
        ElementRect rect;
        Position cursorPosition;
        Position cursorAbsolutePosition;
        Position previousCursorAbsolutePosition;
        bool hovered;
        bool dragging;

        std::function<bool (Position position, Position absolutePosition)> callbackStart;
        std::function<void (Position position, Position absolutePosition)> callbackEnd;
        std::function<void (Position position, Position absolutePosition, Position diff)> callbackMove;
    };

    Draggable *draggable();
}


#endif //ELEMENTOR_DRAGGABLE_H
