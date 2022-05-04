//
// Created by noartem on 04.05.2022.
//

#ifndef ELEMENTOR_SIZED_ABSOLUTE_H
#define ELEMENTOR_SIZED_ABSOLUTE_H

#include "Element.h"

namespace elementor {
    class SizedAbsolute : public Element, WithChild {
    public:
        SizedAbsolute *setWidth(int width);

        SizedAbsolute *setHeight(int height);

        SizedAbsolute *setSize(int width, int height);

        SizedAbsolute *setSize(int size);

        int getWidth();

        int getHeight();

        SizedAbsolute *setChild(Element *child);

        RenderSize getSize(RenderBoundaries boundaries) override;

        std::vector <RenderElement> getRenderChildren(RenderSize size) override;

    private:
        int width = -1;
        int height = -1;
    };

    SizedAbsolute *sizedAbsolute();
}


#endif //ELEMENTOR_SIZED_ABSOLUTE_H
