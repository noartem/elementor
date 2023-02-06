//
// Created by noartem on 03.02.2023.
//

#ifndef ELEMENTOR_STACK_H
#define ELEMENTOR_STACK_H

#include "../Element.h"

namespace elementor::elements {
    class Stack : public Element, public WithChildren, public std::enable_shared_from_this<Stack> {
    public:
        std::shared_ptr<Stack> appendChild(const std::shared_ptr<Element>& child);

        Size getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, Boundaries boundaries) override;

        std::vector <RenderElement> getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) override;
    };

    std::shared_ptr<Stack> stack();
}


#endif //ELEMENTOR_STACK_H
