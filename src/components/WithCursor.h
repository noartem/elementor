//
// Created by noartem on 02.02.2023.
//

#ifndef ELEMENTOR_COMPONENTS_WITH_CURSOR_H
#define ELEMENTOR_COMPONENTS_WITH_CURSOR_H

#include "utility.h"
#include "elementor.h"

namespace elementor::components {
    class WithCursor : public Component, public std::enable_shared_from_this<WithCursor> {
    public:
        WithCursor();

        std::shared_ptr<WithCursor> setCursorShape(CursorShape newCursorShape);

        CursorShape getCursorShape();

        std::shared_ptr<WithCursor> setChild(const std::shared_ptr<Element> &child);

    private:
        CursorShape cursorShape;
        std::shared_ptr<Hoverable> hoverableElement;
    };

    std::shared_ptr<WithCursor> withCursor();
}

#endif //ELEMENTOR_COMPONENTS_WITH_CURSOR_H
