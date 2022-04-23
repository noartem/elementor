//
// Created by noartem on 21.04.2022.
//

#ifndef ELEMENTOR_CLIPRRECT_H
#define ELEMENTOR_CLIPRRECT_H

#include "Element.h"

namespace elementor {
    class ClipRRect : public Element, public WithChild {
    public:
        ClipRRect() {};

        ClipRRect(Element *child);

        ClipRRect(float radiusXY, Element *child);

        ClipRRect(float radiusXY, SkClipOp clipOp, Element *child);

        ClipRRect(float radiusX, float radiusY, Element *child);

        ClipRRect(float radiusX, float radiusY, SkClipOp clipOp, Element *child);

        std::shared_ptr <ElementRenderer> render() override;

    private:
        float radiusX = 0;
        float radiusY = 0;
        SkClipOp clipOp = SkClipOp::kIntersect;
    };

    class ClipRRectRenderer : public ElementRenderer {
    public:
        ClipRRectRenderer(ApplicationContext *context, float radiusX, float radiusY, SkClipOp clipOp, Element *child);

        void paintBackground(SkCanvas *canvas, RenderSize size) override;

        std::vector <RenderElement> getChildren(RenderSize size) override;

    private:
        int radiusX;
        int radiusY;
        SkClipOp clipOp;
        Element *child;
    };
}


#endif //ELEMENTOR_CLIP_H
