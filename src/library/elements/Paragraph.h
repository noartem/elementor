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
    class Paragraph : public Element, public WithChildren, public std::enable_shared_from_this<Paragraph> {
    public:
        std::shared_ptr<Paragraph> setTextAlign(TextAlign newTextAlign);

        TextAlign getTextAlign();

        std::shared_ptr<Paragraph> setTextDirection(TextDirection newTextDirection);

        TextDirection getTextDirection();

        std::shared_ptr<Paragraph> appendChild(const std::shared_ptr<Element>& child);

        void forceUpdate();

        Size getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window,
                     Boundaries boundaries) override;

        void paintBackground(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, SkCanvas *canvas,
                             ElementRect rect) override;

        std::vector<RenderElement>
        getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) override;

    private:
        TextAlign textAlign = TextAlign::Left;
        TextDirection textDirection = TextDirection::LTR;
        std::unique_ptr<sktextlayout::Paragraph> skParagraph;
        std::vector<std::shared_ptr<Text>> childrenText;
        std::vector<std::shared_ptr<Element>> childrenElements;

        float lastPixelScale;

        static sk_sp<sktextlayout::FontCollection> makeFontCollection(const std::shared_ptr<ApplicationContext>& ctx);

        static sktextlayout::TextStyle makeDefaultTextStyle();

        sktextlayout::ParagraphStyle makeParagraphStyle();

        sktextlayout::ParagraphBuilderImpl makeBuilder(const std::shared_ptr<ApplicationContext>& ctx);

        sktextlayout::TextAlign getSkTextAlign();

        sktextlayout::TextDirection getSkTextDirection();

        static sktextlayout::PlaceholderStyle
        makeChildPlaceholderStyle(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window,
                                  const std::shared_ptr<Element>& child);

        std::unique_ptr<sktextlayout::Paragraph>
        makeSkParagraph(const std::shared_ptr<ApplicationContext>& ctx, const std::shared_ptr<Window>& window);
    };

    std::shared_ptr<Paragraph> paragraph();
}


#endif //ELEMENTOR_PARAGRAPH_H
