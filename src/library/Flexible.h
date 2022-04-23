//
// Created by noartem on 18.04.2022.
//

#ifndef ELEMENTOR_FLEXIBLE_H
#define ELEMENTOR_FLEXIBLE_H

#include "Element.h"

namespace elementor {
    class Flexible : public Element, public WithChild {
    public:
        Flexible() {};
        
        Flexible(Element *child);

        Flexible(int grow, Element *child);

        void setGrow(int grow);

        int getGrow();

        std::shared_ptr <ElementRenderer> render() override;

    private:
        int grow = 1;
    };

    class FlexibleRenderer : public ElementRenderer {
    public:
        FlexibleRenderer(ApplicationContext *context, Element *child);

        std::vector <RenderElement> getChildren(RenderSize size) override;

    private:
        Element *child;
    };
}


#endif //ELEMENTOR_FLEXIBLE_H
