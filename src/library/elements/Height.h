//
// Created by noartem on 29.05.2022.
//

#ifndef ELEMENTOR_HEIGHT_H
#define ELEMENTOR_HEIGHT_H

#include "../Element.h"

namespace elementor::elements {
    class Height : public Element, public WithChild {
    public:
        Height *setHeight(float height);

        float getHeight();

        Height *setChild(Element *child);

        Size getSize(ApplicationContext *ctx, Window *window, Boundaries boundaries) override;

        std::vector <RenderElement> getChildren(ApplicationContext *ctx, Window *window, ElementRect rect) override;

    private:
        float height = 0;
    };

    Height *height();
}


#endif //ELEMENTOR_HEIGHT_H
