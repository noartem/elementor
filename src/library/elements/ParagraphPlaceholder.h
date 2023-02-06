//
// Created by noartem on 04.08.2022.
//

#ifndef ELEMENTOR_PARAGRAPH_PLACEHOLDER_H
#define ELEMENTOR_PARAGRAPH_PLACEHOLDER_H

#include "../Element.h"
#include "Text.h"

namespace elementor::elements {
    enum class PlaceholderAlignment {
        Baseline,
        AboveBaseline,
        BelowBaseline,
        Top,
        Bottom,
        Middle,
    };

    class ParagraphPlaceholder : public Element, public WithChild, public std::enable_shared_from_this<ParagraphPlaceholder> {
    public:
        std::shared_ptr<ParagraphPlaceholder> setChild(const std::shared_ptr<Element>& child);

        std::shared_ptr<ParagraphPlaceholder> setAlignment(PlaceholderAlignment newAlignment);

        PlaceholderAlignment getAlignment();

        sktextlayout::PlaceholderAlignment getSkPlaceholderAlignment();

        std::shared_ptr<ParagraphPlaceholder> setBaseline(TextBaseline baseline);

        TextBaseline getBaseline();

        sktextlayout::TextBaseline getSkBaseline();

        std::shared_ptr<ParagraphPlaceholder> setOffset(float offset);

        float getOffset();

        Size getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, Boundaries boundaries) override;

        std::vector <RenderElement> getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) override;
    
    private:
        PlaceholderAlignment alignment = PlaceholderAlignment::Middle;
        TextBaseline baseline = TextBaseline::Alphabetic;
        float offset;
    };

    std::shared_ptr<ParagraphPlaceholder> paragraphPlaceholder();
    std::shared_ptr<ParagraphPlaceholder> placeholder();
}


#endif //ELEMENTOR_PARAGRAPH_PLACEHOLDER_H
