//
// Created by noartem on 21.04.2022.
//

#ifndef ELEMENTOR_CLIPRRECT_H
#define ELEMENTOR_CLIPRRECT_H

#include "Element.h"

namespace elementor {
    class ClipRRect : public Element {
    public:
        Element *child;
        int radius = 0;
        SkClipOp clipOp = SkClipOp::kIntersect;

        std::shared_ptr <ElementRenderer> render() override;
    };

    class ClipRRectRenderer : public ElementRenderer {
    public:
        Element *child;
        int radius = 0;
        SkClipOp clipOp;

        void paintBackground(SkCanvas *canvas, RenderPosition start, RenderSize size) override;

        std::vector <RenderElement> getChildren(RenderSize size) override;
    };
}


#endif //ELEMENTOR_CLIP_H
