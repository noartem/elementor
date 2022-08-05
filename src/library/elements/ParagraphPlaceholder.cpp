//
// Created by noartem on 05.08.2022.
//

#include "ParagraphPlaceholder.h"

namespace elementor::elements {
    ParagraphPlaceholder *paragraphPlaceholder() {
        return new ParagraphPlaceholder();
    }

    ParagraphPlaceholder *placeholder() {
        return paragraphPlaceholder();
    }

    ParagraphPlaceholder *ParagraphPlaceholder::setChild(Element *child) {
        this->updateChild(child);
        return this;
    }

    ParagraphPlaceholder *ParagraphPlaceholder::setAlignment(PlaceholderAlignment alignment) {
        this->alignment = alignment;
        return this;
    }

    PlaceholderAlignment ParagraphPlaceholder::getAlignment() {
        return this->alignment;
    }

    sktext::PlaceholderAlignment ParagraphPlaceholder::getSkPlaceholderAlignment() {
        switch (this->alignment) {
            case PlaceholderAlignment::Baseline:
                return sktext::PlaceholderAlignment::kBaseline;
            case PlaceholderAlignment::AboveBaseline:
                return sktext::PlaceholderAlignment::kAboveBaseline;
            case PlaceholderAlignment::BelowBaseline:
                return sktext::PlaceholderAlignment::kBelowBaseline;
            case PlaceholderAlignment::Top:
                return sktext::PlaceholderAlignment::kTop;
            case PlaceholderAlignment::Bottom:
                return sktext::PlaceholderAlignment::kBottom;
            case PlaceholderAlignment::Middle:
                return sktext::PlaceholderAlignment::kMiddle;
            default:
                return sktext::PlaceholderAlignment::kBaseline;
        }
    }

    ParagraphPlaceholder *ParagraphPlaceholder::setBaseline(TextBaseline baseline) {
        this->baseline = baseline;
        return this;
    }

    TextBaseline ParagraphPlaceholder::getBaseline() {
        return this->baseline;
    }

    sktext::TextBaseline ParagraphPlaceholder::getSkBaseline() {
        switch (this->baseline) {
            case TextBaseline::Alphabetic:
                return sktext::TextBaseline::kAlphabetic;
            case TextBaseline::Ideographic:
                return sktext::TextBaseline::kIdeographic;
            default:
                return sktext::TextBaseline::kAlphabetic;
        }
    }

    ParagraphPlaceholder *ParagraphPlaceholder::setOffset(float offset) {
        this->offset = offset;
        return this;
    }

    float ParagraphPlaceholder::getOffset() {
        return this->offset;
    }

    Size ParagraphPlaceholder::getSize(ApplicationContext *ctx, Boundaries boundaries) {
        return this->getChild()->getSize(ctx, boundaries);
    }

    std::vector <RenderElement> ParagraphPlaceholder::getChildren(ApplicationContext *ctx, Size size) {
        RenderElement child;
        child.element = this->getChild();
        child.size = size;
        child.position = {0, 0};
        return {child};
    }
}