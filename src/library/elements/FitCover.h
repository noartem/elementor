//
// Created by noartem on 27.07.2022.
//

#ifndef ELEMENTOR_FIT_COVER_H
#define ELEMENTOR_FIT_COVER_H

#include "../Element.h"

namespace elementor::elements {
    class FitCover : public Element, public WithChild, public std::enable_shared_from_this<FitCover> {
    public:
        std::shared_ptr<FitCover> setChild(const std::shared_ptr<Element>& child);

        ClipBehavior getClipBehaviour() override;

        std::vector<RenderElement>
        getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) override;
    };

    std::shared_ptr<FitCover> fitCover();
}


#endif //ELEMENTOR_FIT_COVER_H
