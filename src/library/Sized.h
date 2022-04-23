//
// Created by noartem on 19.04.2022.
//

#ifndef ELEMENTOR_SIZED_H
#define ELEMENTOR_SIZED_H

#include "Element.h"

namespace elementor {
    class Sized : public Element, public WithChild {
    public:
        Sized() {};

        Sized(Element *child);

        Sized(float size, Element *child);

        Sized(float width, float height, Element *child);

        void setWidth(float width);

        void setHeight(float height);

        void setSize(float width, float height);

        void setSize(float size);

        float getWidth();

        float getHeight();

        std::shared_ptr <ElementRenderer> render() override;

    private:
        float width = 0;
        float height = 0;
    };

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
