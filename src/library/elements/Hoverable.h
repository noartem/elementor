//
// Created by noartem on 18.05.2022.
//

#ifndef ELEMENTOR_HOVERABLE_H
#define ELEMENTOR_HOVERABLE_H

#include "../Element.h"
#include "../Event.h"

#include <functional>

// TODO: Add `ElementSingleChild` for elements like this
// TODO: Remove hover on window blur

namespace elementor::elements {
    class Hoverable : public Element, public WithOnHover, public WithOnMouseMove, public WithChild, public std::enable_shared_from_this<Hoverable> {
    public:
        std::shared_ptr<Hoverable> onEnter(const std::function<void ()>& callback);

        std::shared_ptr<Hoverable>onLeave(const std::function<void ()>& callback);

        std::shared_ptr<Hoverable> onMove(std::function<EventCallbackResponse (std::shared_ptr<EventMouseMove> event)> callback);

        std::shared_ptr<Hoverable> onMove(const std::function<void ()>& callback);

        std::shared_ptr<Hoverable>setChild(const std::shared_ptr<Element>& child);

        Size getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, Boundaries boundaries) override;

        std::vector <RenderElement> getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) override;

        EventCallbackResponse onEvent(std::shared_ptr<EventMouseMove> event) override;

        EventCallbackResponse onEvent(std::shared_ptr<EventHover> event) override;

    private:
        bool hovered;

        std::function<void ()> callbackEnter;
        std::function<void ()> callbackLeave;
        std::function<EventCallbackResponse (std::shared_ptr<EventMouseMove> event)> callbackMove;
    };

    std::shared_ptr<Hoverable>hoverable();
}


#endif //ELEMENTOR_HOVERABLE_H
