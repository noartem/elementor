//
// Created by noartem on 04.05.2022.
//

#ifndef ELEMENTOR_WRAP_H
#define ELEMENTOR_WRAP_H

#include "../Element.h"

namespace elementor::elements {
    enum class WrapDirection {
        Row,
        Column,
    };

    class Wrap : public Element, public WithChildren {
    public:
        Wrap *setSpacing(float spacing);

        float getSpacing();

        Wrap *setCrossSpacing(float spacing);

        float getCrossSpacing();

        Wrap *setSpacing(float spacing, float crossSpacing);

        Wrap *setDirection(WrapDirection direction);

        WrapDirection getDirection();

        Wrap *appendChild(Element *child);

        Size getSize(ApplicationContext *ctx, Window *window, Boundaries boundaries) override;

        std::vector <RenderElement> getChildren(ApplicationContext *ctx, Window *window, Size size) override;

    private:
        float spacing = 0;
        float crossSpacing = 0;
        WrapDirection direction = WrapDirection::Row;
    };

    Wrap *wrap();
}


#endif //ELEMENTOR_WRAP_H
