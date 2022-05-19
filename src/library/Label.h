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
        Label *setText(std::string text);

        std::string setText();

        Label *setFontColor(SkColor color);

        Label *setFontColor(uint8_t r, uint8_t g, uint8_t b);

        Label *setFontColor(std::string color);

        SkColor getFontColor();

        Label *setFontSize(float size);

        float getFontSize();

        Size getSize(Boundaries boundaries) override;    

        void paintBackground(SkCanvas *canvas, Size size, Rect rect) override;

    private:
        std::string text;
        SkColor fontColor = SK_ColorBLACK;
        float fontSize = 16.0;
    };

    Label *label();
}


#endif //ELEMENTOR_LABEL_H
