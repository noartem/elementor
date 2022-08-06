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

    class ParagraphPlaceholder : public Element, public WithChild {
    public:
        ParagraphPlaceholder *setChild(Element *child);

        ParagraphPlaceholder *setAlignment(PlaceholderAlignment alignment);

        PlaceholderAlignment getAlignment();

        sktext::PlaceholderAlignment getSkPlaceholderAlignment();

        ParagraphPlaceholder *setBaseline(TextBaseline baseline);

        TextBaseline getBaseline();

        sktext::TextBaseline getSkBaseline();

        ParagraphPlaceholder *setOffset(float offset);

        float getOffset();

        Size getSize(ApplicationContext *ctx, Boundaries boundaries) override;

        std::vector <RenderElement> getChildren(ApplicationContext *ctx, Size size) override;
    
    private:
        PlaceholderAlignment alignment = PlaceholderAlignment::Middle;
        TextBaseline baseline = TextBaseline::Alphabetic;
        float offset;
    };

    ParagraphPlaceholder *paragraphPlaceholder();
    ParagraphPlaceholder *placeholder();
}


#endif //ELEMENTOR_PARAGRAPH_PLACEHOLDER_H
