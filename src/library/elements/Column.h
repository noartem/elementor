//
// Created by noartem on 18.04.2022.
//

#ifndef ELEMENTOR_COLUMN_H
#define ELEMENTOR_COLUMN_H

#include "../Element.h"

namespace elementor::elements {
    class Column : public Element, public WithChildren {
    public:
        Column *setSpacing(float spacing);

        float getSpacing();

        Column *appendChild(Element *child);

        Size getSize(ApplicationContext *ctx, Window *window, Boundaries boundaries) override;  

        std::vector <RenderElement> getChildren(ApplicationContext *ctx, Window *window, ElementRect rect) override;

    private:
        float spacing = 0;
    };

    Column *column();
}


#endif //ELEMENTOR_COLUMN_H
