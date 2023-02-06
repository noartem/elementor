//
// Created by noartem on 29.05.2022.
//

#ifndef ELEMENTOR_ALIGN_WIDTH_H
#define ELEMENTOR_ALIGN_WIDTH_H

#include "../Element.h"

namespace elementor::elements {
    class AlignWidth : public Element, public WithChild, public std::enable_shared_from_this<AlignWidth> {
    public:
        std::shared_ptr<AlignWidth> setCoef(float newCoef, float newChildCoef);

        std::shared_ptr<AlignWidth> setCoef(float newCoef);

        float getCoef() const;

        float getChildCoef() const;

        std::shared_ptr<AlignWidth> setChild(const std::shared_ptr<Element>& child);

        Size getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window,
                     Boundaries boundaries) override;

        std::vector<RenderElement>
        getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) override;

    private:
        float coef = 0;
        float childCoef = 0;
    };

    std::shared_ptr<AlignWidth> alignWidth();
}


#endif //ELEMENTOR_ALIGN_WIDTH_H
