//
// Created by noartem on 18.04.2022.
//

#ifndef ELEMENTOR_FLEXIBLE_H
#define ELEMENTOR_FLEXIBLE_H

#include "../Element.h"

namespace elementor::elements {
    class Flexible : public Element, public WithChild, public std::enable_shared_from_this<Flexible> {
    public:
        std::shared_ptr<Flexible> setGrow(float newGrow);

        float getGrow() const;

        std::shared_ptr<Flexible> setChild(const std::shared_ptr<Element>& child);

        Size getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window,
                     Boundaries boundaries) override;

        std::vector<RenderElement>
        getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) override;

    private:
        float grow = 1;
    };

    std::shared_ptr<Flexible> flexible();
}


#endif //ELEMENTOR_FLEXIBLE_H
