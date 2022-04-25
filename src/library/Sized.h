//
// Created by noartem on 19.04.2022.
//

#ifndef ELEMENTOR_SIZED_H
#define ELEMENTOR_SIZED_H

#include "Element.h"

namespace elementor {
    class Sized : public Element, public WithChild {
    public:
        Sized *setWidth(float width);

        Sized *setHeight(float height);

        Sized *setSize(float width, float height);

        Sized *setSize(float size);

        float getWidth();

        float getHeight();

        Sized *setChild(Element *child);

        std::shared_ptr <ElementRenderer> render() override;

    private:
        float width = 0;
        float height = 0;
    };

    Sized *sized();

    class SizedRenderer : public ElementRenderer {
    public:
        SizedRenderer(ApplicationContext *context, float width, float height, Element *child);

        RenderSize getSize(RenderBoundaries boundaries) override;

        std::vector <RenderElement> getChildren(RenderSize size) override;

    private:
        int width = 0;
        int height = 0;
        Element *child;
    };
}


#endif //ELEMENTOR_SIZED_H
