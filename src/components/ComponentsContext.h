//
// Created by noartem on 04.02.2023.
//

#ifndef ELEMENTOR_COMPONENTS_COMPONENTS_CONTEXT_H
#define ELEMENTOR_COMPONENTS_COMPONENTS_CONTEXT_H

#include "elementor.h"

namespace elementor::components {
    class ComponentsContext : public Component, public WithChild, public std::enable_shared_from_this<ComponentsContext> {
    public:
        explicit ComponentsContext(const std::shared_ptr<Element>& rootElement) : Component(), WithChild() {
            this->stackElement = stack();
            this->element = rounded()
                ->setChild(this->stackElement
                    ->appendChild(rootElement));
        };

        std::shared_ptr<Stack> getStackElement() {
            return this->stackElement;
        }

    private:
        std::shared_ptr<Stack> stackElement;
    };
}

#endif //ELEMENTOR_COMPONENTS_COMPONENTS_CONTEXT_H