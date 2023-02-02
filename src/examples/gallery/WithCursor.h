//
// Created by noartem on 02.02.2023.
//

#ifndef GALLERY_WITH_CURSOR_H
#define GALLERY_WITH_CURSOR_H

#include "utility.h"

class WithCursor : public Component, public WithChild {
public:
    WithCursor();
    
    WithCursor *setCursorShape(CursorShape cursorShape);

    CursorShape getCursorShape();

    WithCursor *setChild(Element *child);

private:
    CursorShape cursorShape;
    Hoverable *hoverableElement;
};

WithCursor *withCursor();

#endif //GALLERY_WITH_CURSOR_H
