//
// Created by noartem on 18.04.2022.
//

#ifndef ELEMENTOR_ROW_H
#define ELEMENTOR_ROW_H

#include "Element.h"

namespace elementor {
    enum class RowAlignment {
        Start,
        Center,
        End,
    };

    class Row : public Element, WithChildren {
    public:
        Row *setSpacing(float spacing);

        float getSpacing();

        Row *setAlignment(RowAlignment alignment);

        RowAlignment getAlignment();

        Row *appendChild(Element *child);

        Size getSize(ApplicationContext *ctx, Boundaries boundaries) override;  

        std::vector <RenderElement> getChildren(ApplicationContext *ctx, Size size) override;

    private:
        float spacing = 0;
        RowAlignment alignment = RowAlignment::Start;
    };

    Row *row();
}


#endif //ELEMENTOR_ROW_H
