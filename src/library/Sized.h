//
// Created by noartem on 19.04.2022.
//

#ifndef ELEMENTOR_SIZED_H
#define ELEMENTOR_SIZED_H

#include "Element.h"

namespace elementor {
    class Sized : public Element {
    public:
        int width = 0;
        int height = 0;
        Element *child;

        std::shared_ptr <ElementRenderer> render() override;
    };

    class SizedRenderer : public ElementRenderer {
    public:
        int width = 0;
        int height = 0;
        Element *child;

        RenderSize getSize(RenderBoundaries boundaries) override;

        std::vector <RenderElement> getChildren(RenderSize size) override;
    };
}


#endif //ELEMENTOR_SIZED_H
