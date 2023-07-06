//
// Created by noartem on 18.05.2022.
//

#include "Hoverable.h"

#include <utility>

namespace elementor::elements {
    std::shared_ptr <Hoverable> hoverable() {
        return std::make_shared<Hoverable>();
    }

    std::shared_ptr <Hoverable> Hoverable::onEnter(const std::function<void()> &callback) {
        this->callbackEnter = callback;
        return shared_from_this();
    }

    std::shared_ptr <Hoverable> Hoverable::onLeave(const std::function<void()> &callback) {
        this->callbackLeave = callback;
        return shared_from_this();
    }

    std::shared_ptr <Hoverable> Hoverable::onMove(
            std::function<EventCallbackResponse(std::shared_ptr < EventMouseMove > event)> callback) {
        this->callbackMove = std::move(callback);
        return shared_from_this();
    }

    std::shared_ptr <Hoverable> Hoverable::onMove(const std::function<void()> &callback) {
        this->callbackMove = [callback](const std::shared_ptr <EventMouseMove> &event) {
            callback();
            return EventCallbackResponse::None;
        };
        return shared_from_this();
    }

    std::shared_ptr <Hoverable> Hoverable::setChild(const std::shared_ptr <Element> &child) {
        this->updateChild(child);
        return shared_from_this();
    }

    Size Hoverable::getSize(std::shared_ptr <ApplicationContext> ctx, std::shared_ptr <Window> window,
                            Boundaries boundaries) {
        if (this->hasChild()) {
            return this->getChild()->getSize(ctx, window, boundaries);
        } else {
            return boundaries.max;
        }
    }

    std::vector <RenderElement> Hoverable::getChildren(std::shared_ptr <ApplicationContext> ctx,
                                                       std::shared_ptr <Window> window, ElementRect rect) {
        std::vector <RenderElement> children;

        if (this->hasChild()) {
            RenderElement childElement{this->getChild(), {0, 0}, rect.size};
            children.push_back(childElement);
        }

        return children;
    }

    EventCallbackResponse Hoverable::onEvent(std::shared_ptr <EventHover> event) {
        if (this->hovered && !event->hovered && this->callbackLeave) {
            this->callbackLeave();
        }

        if (!this->hovered && event->hovered && this->callbackEnter) {
            this->callbackEnter();
        }

        this->hovered = event->hovered;

        return EventCallbackResponse::None;
    }

    EventCallbackResponse Hoverable::onEvent(std::shared_ptr <EventMouseMove> event) {
        if (this->hovered && this->callbackMove) {
            EventCallbackResponse callbackResponse = this->callbackMove(event);
            if (callbackResponse != EventCallbackResponse::None) {
                return callbackResponse;
            }
        }

        return EventCallbackResponse::None;
    }
}
