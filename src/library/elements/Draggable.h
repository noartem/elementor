//
// Created by noartem on 18.05.2022.
//

#ifndef ELEMENTOR_DRAGGABLE_H
#define ELEMENTOR_DRAGGABLE_H

#include "../Element.h"
#include "../Event.h"

#include <functional>

namespace elementor::elements {
    class Draggable
            : public Element,
              public WithOnMouseButton,
              public WithOnMouseMove,
              public WithChild,
              public std::enable_shared_from_this<Draggable> {
    public:
        std::shared_ptr<Draggable> onStart(std::function<bool(Position position, Position absolutePosition)> callback);

        std::shared_ptr<Draggable> onStart(const std::function<void()>& callback);

        std::shared_ptr<Draggable> onEnd(std::function<void(Position position, Position absolutePosition)> callback);

        std::shared_ptr<Draggable> onEnd(const std::function<void()>& callback);

        std::shared_ptr<Draggable>
        onMove(std::function<void(Position position, Position absolutePosition, Position diff)> callback);

        std::shared_ptr<Draggable> onMove(const std::function<void()>& callback);

        std::shared_ptr<Draggable> setChild(const std::shared_ptr<Element>& child);

        Size getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window,
                     Boundaries boundaries) override;

        void paintBackground(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, SkCanvas *canvas,
                             ElementRect rect) override;

        std::vector<RenderElement>
        getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) override;

        EventCallbackResponse onEvent(std::shared_ptr<EventMouseMove> event) override;

        EventCallbackResponse onEvent(std::shared_ptr<EventMouseButton> event) override;

    private:
        ElementRect rect;
        Position cursorPosition;
        Position cursorAbsolutePosition;
        Position previousCursorAbsolutePosition;
        bool hovered;
        bool dragging;

        std::function<bool(Position position, Position absolutePosition)> callbackStart;
        std::function<void(Position position, Position absolutePosition)> callbackEnd;
        std::function<void(Position position, Position absolutePosition, Position diff)> callbackMove;
    };

    std::shared_ptr<Draggable> draggable();
}


#endif //ELEMENTOR_DRAGGABLE_H
