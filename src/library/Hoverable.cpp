//
// Created by noartem on 18.05.2022.
//

#include "Hoverable.h"

namespace elementor {
    Hoverable *hoverable() {
        return new Hoverable();
    }

    Hoverable *Hoverable::onEnter(std::function<void()> callback) {
        this->callbackEnter = callback;
        return this;
    }

    Hoverable *Hoverable::onLeave(std::function<void()> callback) {
        this->callbackLeave = callback;
        return this;
    }

    Hoverable *Hoverable::setChild(Element *child) {
        child->context = this->context;
        this->updateChild(child);
        return this;
    }

    Size Hoverable::getSize(Boundaries boundaries) {
        if (this->hasChild()) {
            return this->getChild(this->context)->getSize(boundaries);
        } else {
            return boundaries.max;
        }
    }

    void Hoverable::paintBackground(SkCanvas *canvas, Size size, Rect rect) {
        this->rect = rect;
    }

    std::vector <RenderElement> Hoverable::getRenderChildren(Size size) {
        std::vector <RenderElement> children;

        if (this->hasChild()) {
            RenderElement child;
            child.element = this->getChild(this->context);
            child.position = {0, 0};
            child.size = size;

            children.push_back(child);
        }

        return children;
    }

    EventCallbackResponse Hoverable::onEvent(EventMouseMove *event) {
        if (
            this->rect.position.x < event->x &&
            this->rect.position.x + this->rect.size.width > event->x &&
            this->rect.position.y < event->y &&
            this->rect.position.y + this->rect.size.height > event->y
        ) {
            this->hovered = true;
            if (this->callbackEnter) {
                this->callbackEnter();
            }
        } else if (this->hovered) {
            this->hovered = false;
            if (this->callbackLeave) {
                this->callbackLeave();
            }
        }

        return EventCallbackResponse::None;
    }
}
