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

    sktextlayout::PlaceholderAlignment ParagraphPlaceholder::getSkPlaceholderAlignment() {
        switch (this->alignment) {
            case PlaceholderAlignment::Baseline:
                return sktextlayout::PlaceholderAlignment::kBaseline;
            case PlaceholderAlignment::AboveBaseline:
                return sktextlayout::PlaceholderAlignment::kAboveBaseline;
            case PlaceholderAlignment::BelowBaseline:
                return sktextlayout::PlaceholderAlignment::kBelowBaseline;
            case PlaceholderAlignment::Top:
                return sktextlayout::PlaceholderAlignment::kTop;
            case PlaceholderAlignment::Bottom:
                return sktextlayout::PlaceholderAlignment::kBottom;
            case PlaceholderAlignment::Middle:
                return sktextlayout::PlaceholderAlignment::kMiddle;
            default:
                return sktextlayout::PlaceholderAlignment::kBaseline;
        }
    }

    ParagraphPlaceholder *ParagraphPlaceholder::setBaseline(TextBaseline baseline) {
        this->baseline = baseline;
        return this;
    }

    TextBaseline ParagraphPlaceholder::getBaseline() {
        return this->baseline;
    }

    sktextlayout::TextBaseline ParagraphPlaceholder::getSkBaseline() {
        switch (this->baseline) {
            case TextBaseline::Alphabetic:
                return sktextlayout::TextBaseline::kAlphabetic;
            case TextBaseline::Ideographic:
                return sktextlayout::TextBaseline::kIdeographic;
            default:
                return sktextlayout::TextBaseline::kAlphabetic;
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