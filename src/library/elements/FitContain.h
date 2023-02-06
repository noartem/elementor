//
// Created by noartem on 27.07.2022.
//

#ifndef ELEMENTOR_FIT_CONTAIN_H
#define ELEMENTOR_FIT_CONTAIN_H

#include "../Element.h"

namespace elementor::elements {
    class FitContain : public Element, public WithChild, public std::enable_shared_from_this<FitContain> {
    public:
        std::shared_ptr<FitContain> setChild(const std::shared_ptr<Element>& child);

        std::vector<RenderElement>
        getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) override;
    };

    std::shared_ptr<FitContain> fitContain();
}


#endif //ELEMENTOR_FIT_CONTAIN_H
