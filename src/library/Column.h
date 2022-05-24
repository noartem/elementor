//
// Created by noartem on 18.04.2022.
//

#ifndef ELEMENTOR_COLUMN_H
#define ELEMENTOR_COLUMN_H

#include "Element.h"

namespace elementor {
    enum class ColumnAlignment {
        Start,
        Center,
        End,
    };

    class Column : public Element, WithChildren {
    public:
        Column *setSpacing(float spacing);

        float getSpacing();

        Column *setAlignment(ColumnAlignment alignment);

        ColumnAlignment getAlignment();

        Column *appendChild(Element *child);

        Size getSize(ApplicationContext *ctx, Boundaries boundaries) override;  

        std::vector <RenderElement> getChildren(ApplicationContext *ctx, Size size) override;

    private:
        float spacing = 0;
        ColumnAlignment alignment = ColumnAlignment::Start;
    };

    Column *column();
}


#endif //ELEMENTOR_COLUMN_H
