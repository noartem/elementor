//
// Created by noartem on 18.06.2022.
//

#ifndef ELEMENTOR_EXPANDED_WIDTH_H
#define ELEMENTOR_EXPANDED_WIDTH_H

#include "../Element.h"

namespace elementor::elements {
    class ExpandedWidth : public Element, public WithChild, public std::enable_shared_from_this<ExpandedWidth> {
    public:
        std::shared_ptr<ExpandedWidth> setChild(const std::shared_ptr<Element>& child);

        Size getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window,
                     Boundaries boundaries) override;

        std::vector<RenderElement>
        getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) override;
    };

    std::shared_ptr<ExpandedWidth> expandedWidth();
}


#endif //ELEMENTOR_EXPANDED_WIDTH_H
