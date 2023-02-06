//
// Created by noartem on 18.06.2022.
//

#ifndef ELEMENTOR_EXPANDED_HEIGHT_H
#define ELEMENTOR_EXPANDED_HEIGHT_H

#include "../Element.h"

namespace elementor::elements {
    class ExpandedHeight : public Element, public WithChild, public std::enable_shared_from_this<ExpandedHeight> {
    public:
        std::shared_ptr<ExpandedHeight> setChild(const std::shared_ptr<Element>& child);

        Size getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window,
                     Boundaries boundaries) override;

        std::vector<RenderElement>
        getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) override;
    };

    std::shared_ptr<ExpandedHeight> expandedHeight();
}


#endif //ELEMENTOR_EXPANDED_HEIGHT_H
