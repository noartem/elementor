//
// Created by noartem on 29.05.2022.
//

#ifndef ELEMENTOR_CENTER_H
#define ELEMENTOR_CENTER_H

#include "Element.h"

namespace elementor {
    class Center : public Element, WithChild {
    public:
        Center *setChild(Element *child);

        std::vector <RenderElement> getChildren(ApplicationContext *ctx, Size size) override;
    };

    Center *center();
}


#endif //ELEMENTOR_CENTER_H
