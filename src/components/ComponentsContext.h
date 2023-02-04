//
// Created by noartem on 04.02.2023.
//

#ifndef ELEMENTOR_COMPONENTS_COMPONENTS_CONTEXT_H
#define ELEMENTOR_COMPONENTS_COMPONENTS_CONTEXT_H

#include "elementor.h"

namespace elementor::components {
    class ComponentsContext : public Component, public WithChild {
    public:
        explicit ComponentsContext(Element *rootElement) : Component(), WithChild() {
            this->stackElement = stack();
            this->element = rounded()
                ->setChild(this->stackElement
                    ->appendChild(rootElement));
        };

        Stack *getStackElement() {
            return this->stackElement;
        }

    private:
        Stack *stackElement;
    };
}

#endif //ELEMENTOR_COMPONENTS_COMPONENTS_CONTEXT_H