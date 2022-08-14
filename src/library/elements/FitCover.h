//
// Created by noartem on 27.07.2022.
//

#ifndef ELEMENTOR_FIT_COVER_H
#define ELEMENTOR_FIT_COVER_H

#include "../Element.h"

namespace elementor::elements {
    class FitCover : public Element, public WithChild {
    public:
        FitCover *setChild(Element *child);

        ClipBehavior getClipBehaviour() override;

        std::vector <RenderElement> getChildren(ApplicationContext *ctx, Window *window, Size size) override;
    };

    FitCover *fitCover();
}


#endif //ELEMENTOR_FIT_COVER_H
