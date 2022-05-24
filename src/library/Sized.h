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

        Sized *setSize(float width, float height);

        Sized *setSize(float size);

        float getWidth();

        float getHeight();

        Sized *setChild(Element *child);

        Size getSize(ApplicationContext *ctx, Boundaries boundaries) override;

        std::vector <RenderElement> getChildren(ApplicationContext *ctx, Size size) override;

    private:
        float width = 0;
        float height = 0;
    };

    Sized *sized();
}


#endif //ELEMENTOR_SIZED_H
