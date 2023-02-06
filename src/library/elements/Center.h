//
// Created by noartem on 29.05.2022.
//

#ifndef ELEMENTOR_CENTER_H
#define ELEMENTOR_CENTER_H

#include "../Element.h"

namespace elementor::elements {
    class Center : public Element, public WithChild, public std::enable_shared_from_this<Center> {
    public:
        std::shared_ptr<Center> setChild(const std::shared_ptr<Element>& child);

        std::vector<RenderElement>
        getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) override;
    };

    std::shared_ptr<Center> center();
}


#endif //ELEMENTOR_CENTER_H
