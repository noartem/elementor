//
// Created by noartem on 04.08.2022.
//

#ifndef ELEMENTOR_PARAGRAPH_H
#define ELEMENTOR_PARAGRAPH_H

#include "../Element.h"
#include "Text.h"

#include <modules/skparagraph/src/ParagraphBuilderImpl.h>

namespace sktext = skia::textlayout;

namespace elementor::elements {
    class Paragraph : public Element, public WithChildren {
    public:
        Paragraph *setTextAlign(TextAlign textAlign);

        TextAlign getTextAlign();

        Paragraph *setTextDirection(TextDirection textDirection);

        TextDirection getTextDirection();

        Paragraph *appendChild(Element *child);

        Size getSize(ApplicationContext *ctx, Boundaries boundaries) override;

        void paintBackground(ApplicationContext *ctx, SkCanvas *canvas, ElementRect rect) override;

        std::vector <RenderElement> getChildren(ApplicationContext *ctx, Size size) override;

    private:
        TextAlign textAlign = TextAlign::Left;
        TextDirection textDirection = TextDirection::LTR;
        std::unique_ptr<sktext::Paragraph> skParagraph;
        std::vector<Text *> childrenText;
        std::vector<Element *> childrenElements;

        sk_sp<sktext::FontCollection> makeFontCollection(ApplicationContext *ctx);

        sktext::TextStyle makeDefaultTextStyle();

        sktext::ParagraphStyle makeParagraphStyle();

        sktext::ParagraphBuilderImpl makeBuilder(ApplicationContext *ctx);

        sktext::TextAlign getSkTextAlign();

        sktext::TextDirection getSkTextDirection();

        sktext::PlaceholderStyle makeChildPlaceholderStyle(ApplicationContext *ctx, Element *child);

        std::unique_ptr<sktext::Paragraph> makeSkParagraph(ApplicationContext *ctx);
    };

    Paragraph *paragraph();
}


#endif //ELEMENTOR_PARAGRAPH_H
