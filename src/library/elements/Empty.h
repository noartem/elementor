//
// Created by noartem on 29.05.2022.
//

#ifndef ELEMENTOR_EMPTY_H
#define ELEMENTOR_EMPTY_H

#include "../Element.h"

namespace elementor::elements {
    class Empty : public Element, public WithChild, public std::enable_shared_from_this<Empty> {
    public:
        std::shared_ptr<Empty> setChild(const std::shared_ptr<Element>& child);

        Size getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window,
                     Boundaries boundaries) override;

        std::vector<RenderElement>
        getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) override;
    };

    std::shared_ptr<Empty> empty();
}


#endif //ELEMENTOR_EMPTY_H
