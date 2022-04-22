//
// Created by noartem on 22.04.2022.
//

#ifndef ELEMENTOR_LABEL_H
#define ELEMENTOR_LABEL_H

#include "Element.h"

#include <include/core/SkFont.h>

namespace elementor {
    class Label : public Element {
    public:
        std::string text;
        SkColor fontColor = SK_ColorBLACK;
        float fontSize = 16.0;

        std::shared_ptr <ElementRenderer> render() override;
    };

    class LabelRenderer : public ElementRenderer {
    public:
        std::string text;
        SkColor fontColor;
        float fontSize;

        RenderSize getSize(RenderBoundaries boundaries) override;    

        void paintBackground(SkCanvas *canvas, RenderSize size) override;

    private:
        SkFont makeFont();
        SkRect makeTextBounds();
    };
}


#endif //ELEMENTOR_LABEL_H
