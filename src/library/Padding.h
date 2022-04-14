//
// Created by noartem on 13.04.2022.
//

#ifndef ELEMENTOR_PADDING_H
#define ELEMENTOR_PADDING_H

#include "IElement.h"

namespace elementor {
    struct PaddingsValue {
        int top;
        int right;
        int bottom;
        int left;
    };

    class Padding : public IElement {
    public:
        PaddingsValue paddings;
        IElement *child;

        IElementRenderer* render();

        void setPaddings(int paddings);

        void setPaddings(int paddingY, int paddingX);

        void setPaddings(int paddingTop, int paddingX, int paddingBottom);

        void setPaddings(int paddingTop, int paddingRight, int paddingBottom, int paddingLeft);
    };

    class PaddingRenderer : public IElementRenderer {
    public:
        PaddingsValue paddings;
        IElement *child;

        RenderSize getSize(Boundaries boundaries);

        void paintBackground(RenderSize size, SkCanvas *canvas);

        std::vector <RenderChild> getChildren(RenderSize size);
    };
}


#endif //ELEMENTOR_PADDING_H
