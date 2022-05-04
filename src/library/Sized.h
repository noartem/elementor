//
// Created by noartem on 19.04.2022.
//

#ifndef ELEMENTOR_SIZED_H
#define ELEMENTOR_SIZED_H

#include "Element.h"

namespace elementor {
    class Sized : public Element, WithChild {
    public:
        Sized *setWidth(float width);

        Sized *setHeight(float height);

        Sized *setWidth(int width);

        Sized *setHeight(int height);

        Sized *setSize(float width, float height);

        Sized *setSize(int width, int height);

        Sized *setSize(float size);

        Sized *setSize(int size);

        float getWidth();

        float getHeight();

        Sized *setChild(Element *child);

        RenderSize getSize(RenderBoundaries boundaries) override;

        std::vector <RenderElement> getRenderChildren(RenderSize size) override;

    private:
        float width = -1;
        float height = -1;
        bool absWidth = false;
        bool absHeight = false;
    };

    Sized *sized();
}


#endif //ELEMENTOR_SIZED_H
