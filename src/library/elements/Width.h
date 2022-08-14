//
// Created by noartem on 29.05.2022.
//

#ifndef ELEMENTOR_WIDTH_H
#define ELEMENTOR_WIDTH_H

#include "../Element.h"

namespace elementor::elements {
    class Width : public Element, public WithChild {
    public:
        Width *setWidth(float width);

        float getWidth();

        Width *setChild(Element *child);

        Size getSize(ApplicationContext *ctx, Window *window, Boundaries boundaries) override;

        std::vector <RenderElement> getChildren(ApplicationContext *ctx, Window *window, Size size) override;

    private:
        float width = 0;
    };

    Width *width();
}


#endif //ELEMENTOR_WIDTH_H
