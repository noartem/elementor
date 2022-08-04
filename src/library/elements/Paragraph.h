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
    class Paragraph : public Element, WithChildren {
    public:
        Paragraph *setTextAlign(TextAlign textAlign);

        TextAlign getTextAlign();

        Paragraph *setTextDirection(TextDirection textDirection);

        TextDirection getTextDirection();

        Paragraph *appendChild(Element *child);

        Size getSize(ApplicationContext *ctx, Boundaries boundaries) override;

        void paintBackground(ApplicationContext *ctx, SkCanvas *canvas, ElementRect rect) override;

    private:
        TextAlign textAlign = TextAlign::Left;
        TextDirection textDirection = TextDirection::LTR;
        std::unique_ptr<sktext::Paragraph> skParagraph;

        sk_sp<sktext::FontCollection> makeDefaultFontCollection();

        sktext::TextStyle makeDefaultTextStyle();

        sktext::ParagraphStyle makeDefaultParagraphStyle();

        sktext::ParagraphBuilderImpl makeBuilder();

        sktext::TextAlign getSkTextAlign();

        sktext::TextDirection getSkTextDirection();

        std::unique_ptr<sktext::Paragraph> makeSkParagraph(ApplicationContext *ctx);

        std::unique_ptr<sktext::Paragraph> getOrMakeSkParagraph(ApplicationContext *ctx);
    };

    Paragraph *paragraph();
}


#endif //ELEMENTOR_PARAGRAPH_H