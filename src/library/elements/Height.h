//
// Created by noartem on 29.05.2022.
//

#ifndef ELEMENTOR_HEIGHT_H
#define ELEMENTOR_HEIGHT_H

#include "../Element.h"

namespace elementor::elements {
    class Height : public Element, public WithChild, public std::enable_shared_from_this<Height> {
    public:
        std::shared_ptr<Height> setHeight(float height);

        float getHeight();

        std::shared_ptr<Height> setChild(const std::shared_ptr<Element>& child);

        Size getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window,
                     Boundaries boundaries) override;

        std::vector<RenderElement>
        getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) override;

    private:
        float height = 0;
    };

    std::shared_ptr<Height> height();
}


#endif //ELEMENTOR_HEIGHT_H
