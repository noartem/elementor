//
// Created by noartem on 18.05.2022.
//

#ifndef ELEMENTOR_CLICKABLE_H
#define ELEMENTOR_CLICKABLE_H

#include "../Element.h"
#include "../Event.h"

#include <functional>

namespace elementor::elements {
    class Clickable
            : public Element,
              public WithOnMouseButton,
              public WithOnMouseMove,
              public WithChild,
              public std::enable_shared_from_this<Clickable> {
    public:
        std::shared_ptr<Clickable> onButton(std::function<EventCallbackResponse(std::shared_ptr<EventMouseButton> event,
                                                                                Position position)> callback);

        std::shared_ptr<Clickable> onButton(const std::function<void()>& callback);

        std::shared_ptr<Clickable> onClick(std::function<EventCallbackResponse(std::shared_ptr<EventMouseButton> event,
                                                                               Position position)> callback);

        std::shared_ptr<Clickable> onClick(const std::function<void()>& callback);

        std::shared_ptr<Clickable> onRightClick(
                std::function<EventCallbackResponse(std::shared_ptr<EventMouseButton> event,
                                                    Position position)> callback);

        std::shared_ptr<Clickable> onRightClick(const std::function<void()>& callback);

        std::shared_ptr<Clickable> setChild(const std::shared_ptr<Element>& child);

        Size getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window,
                     Boundaries boundaries) override;

        void paintBackground(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, SkCanvas *canvas,
                             ElementRect rect) override;

        std::vector<RenderElement>
        getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) override;

        EventCallbackResponse onEvent(std::shared_ptr<EventMouseMove> event) override;

        EventCallbackResponse onEvent(std::shared_ptr<EventMouseButton> event) override;

    private:
        std::shared_ptr<Window> window;
        ElementRect rect;
        Position cursorPosition;
        bool hovered;
        std::function<EventCallbackResponse(std::shared_ptr<EventMouseButton> event, Position position)> callbackButton;
        std::function<EventCallbackResponse(std::shared_ptr<EventMouseButton> event, Position position)> callbackClick;
        std::function<EventCallbackResponse(std::shared_ptr<EventMouseButton> event,
                                            Position position)> callbackRightClick;
    };

    std::shared_ptr<Clickable> clickable();
}


#endif //ELEMENTOR_CLICKABLE_H
