//
// Created by noartem on 03.02.2023.
//

#ifndef ELEMENTOR_STACK_H
#define ELEMENTOR_STACK_H

#include "../Element.h"

namespace elementor::elements {
    class Stack : public Element, public WithChildren {
    public:
        Stack *appendChild(Element *child);

        Size getSize(ApplicationContext *ctx, Window *window, Boundaries boundaries) override;

        std::vector <RenderElement> getChildren(ApplicationContext *ctx, Window *window, Size size) override;
    };

    Stack *stack();
}


#endif //ELEMENTOR_STACK_H
