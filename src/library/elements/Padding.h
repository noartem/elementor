//
// Created by noartem on 13.04.2022.
//

#ifndef ELEMENTOR_PADDING_H
#define ELEMENTOR_PADDING_H

#include "../Element.h"

namespace elementor::elements {
    struct PaddingsValue {
        float top;
        float right;
        float bottom;
        float left;
    };

    class Padding : public Element, public WithChild, public std::enable_shared_from_this<Padding> {
    public:
        std::shared_ptr<Padding> setPaddings(float paddingTop, float paddingRight, float paddingBottom, float paddingLeft);

        std::shared_ptr<Padding> setPaddings(float paddingTop, float paddingX, float paddingBottom);

        std::shared_ptr<Padding> setPaddings(float paddingY, float paddingX);

        std::shared_ptr<Padding> setPaddings(float paddings);

        PaddingsValue getPaddings();

        std::shared_ptr<Padding> setChild(const std::shared_ptr<Element>& child);

        Size getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, Boundaries boundaries) override;

        std::vector <RenderElement> getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) override;

    private:
        PaddingsValue paddings;
    };

    std::shared_ptr<Padding> padding();
}


#endif //ELEMENTOR_PADDING_H
