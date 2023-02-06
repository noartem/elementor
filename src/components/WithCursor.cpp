//
// Created by noartem on 02.02.2023.
//

#include "WithCursor.h"

namespace elementor::components {
    WithCursor *withCursor() {
        return new WithCursor();
    }

    WithCursor::WithCursor() {
        this->hoverableElement = hoverable()
            ->onEnter([this] () {
                this->window->getCursor()->set(this->cursorShape);
            })
            ->onLeave([this] () {
                this->window->getCursor()->set(CursorShape::Default);
            });
        this->element = this->hoverableElement;
    }

    WithCursor *WithCursor::setCursorShape(CursorShape newCursorShape) {
        this->cursorShape = newCursorShape;
        return shared_from_this();
    }

    CursorShape WithCursor::getCursorShape() {
        return this->cursorShape;
    }

    WithCursor *WithCursor::setChild(const std::shared_ptr<Element>& child) {
        this->hoverableElement->setChild(child);
        return shared_from_this();
    }
}