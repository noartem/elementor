//
// Created by noartem on 04.08.2022.
//

#ifndef ELEMENTOR_PARAGRAPH_H
#define ELEMENTOR_PARAGRAPH_H

#include "../Element.h"
#include "Text.h"

#include <modules/skparagraph/src/ParagraphBuilderImpl.h>

namespace sktextlayout = skia::textlayout;

namespace elementor::elements {
    class Paragraph : public Element, public WithChildren {
    public:
        Paragraph *setTextAlign(TextAlign textAlign);

        TextAlign getTextAlign();

        Paragraph *setTextDirection(TextDirection textDirection);

        TextDirection getTextDirection();

        Paragraph *appendChild(Element *child);

        Size getSize(ApplicationContext *ctx, Window *window, Boundaries boundaries) override;

        void paintBackground(ApplicationContext *ctx, Window *window, SkCanvas *canvas, ElementRect rect) override;

        std::vector <RenderElement> getChildren(ApplicationContext *ctx, Window *window, Size size) override;

    private:
        TextAlign textAlign = TextAlign::Left;
        TextDirection textDirection = TextDirection::LTR;
        std::unique_ptr<sktextlayout::Paragraph> skParagraph;
        std::vector<Text *> childrenText;
        std::vector<Element *> childrenElements;

        float lastPixelScale;

        sk_sp<sktextlayout::FontCollection> makeFontCollection(ApplicationContext *ctx);

        sktextlayout::TextStyle makeDefaultTextStyle();

        sktextlayout::ParagraphStyle makeParagraphStyle();

        sktextlayout::ParagraphBuilderImpl makeBuilder(ApplicationContext *ctx);

        sktextlayout::TextAlign getSkTextAlign();

        sktextlayout::TextDirection getSkTextDirection();

        sktextlayout::PlaceholderStyle makeChildPlaceholderStyle(ApplicationContext *ctx, Window *window, Element *child);

        std::unique_ptr<sktextlayout::Paragraph> makeSkParagraph(ApplicationContext *ctx, Window *window);
    };

    Paragraph *paragraph();
}


#endif //ELEMENTOR_PARAGRAPH_H
