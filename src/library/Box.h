//
// Created by noartem on 13.04.2022.
//

#ifndef ELEMENTOR_BOX_H
#define ELEMENTOR_BOX_H

#include "IElement.h"

namespace elementor {
    class Box : public IElement {
    public:
        int paddings;
        IElement *child;

        IElementRenderer* render();
    };

    class BoxRenderer : public IElementRenderer {
    public:
        int paddings;
        IElement *child;

        RenderSize getSize(Boundaries boundaries);

        void paintBackground(RenderSize size, SkCanvas *canvas);

        std::vector <RenderChild> getChildren(RenderSize size);
    };
}


#endif //ELEMENTOR_BOX_H
