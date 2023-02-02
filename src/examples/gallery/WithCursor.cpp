//
// Created by noartem on 02.02.2023.
//

#include "WithCursor.h"

WithCursor *withCursor() {
    return new WithCursor();
}

WithCursor::WithCursor() {
    this->hoverableElement = hoverable()
        ->setChild(this->getChild())
        ->onEnter([this] () {
            this->window->getCursor()->set(this->cursorShape);
        })
        ->onLeave([this] () {
            this->window->getCursor()->set(CursorShape::Default);
        });
    this->element = this->hoverableElement;
}

WithCursor *WithCursor::setCursorShape(CursorShape cursorShape) {
    this->cursorShape = cursorShape;
    return this;
}

CursorShape WithCursor::getCursorShape() {
    return this->cursorShape;
}

WithCursor *WithCursor::setChild(Element *child) {
    this->updateChild(child);
    this->hoverableElement->setChild(child);
    return this;
}