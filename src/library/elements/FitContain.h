//
// Created by noartem on 27.07.2022.
//

#ifndef ELEMENTOR_FIT_CONTAIN_H
#define ELEMENTOR_FIT_CONTAIN_H

#include "../Element.h"

namespace elementor::elements {
    class FitContain : public Element, public WithChild {
    public:
        FitContain *setChild(Element *child);

        std::vector <RenderElement> getChildren(ApplicationContext *ctx, Size size) override;
    };

    FitContain *fitContain();
}


#endif //ELEMENTOR_FIT_CONTAIN_H
