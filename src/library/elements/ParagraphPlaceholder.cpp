//
// Created by noartem on 05.08.2022.
//

#include "ParagraphPlaceholder.h"

#include <utility>

namespace elementor::elements {
    std::shared_ptr<ParagraphPlaceholder> paragraphPlaceholder() {
        return std::make_shared<ParagraphPlaceholder>();
    }

    std::shared_ptr<ParagraphPlaceholder> placeholder() {
        return paragraphPlaceholder();
    }

    std::shared_ptr<ParagraphPlaceholder> ParagraphPlaceholder::setChild(const std::shared_ptr<Element>& child) {
        this->updateChild(child);
        return shared_from_this();
    }

    std::shared_ptr<ParagraphPlaceholder> ParagraphPlaceholder::setAlignment(PlaceholderAlignment newAlignment) {
        this->alignment = newAlignment;
        return shared_from_this();
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

    std::shared_ptr<ParagraphPlaceholder> ParagraphPlaceholder::setBaseline(TextBaseline baseline) {
        this->baseline = baseline;
        return shared_from_this();
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

    std::shared_ptr<ParagraphPlaceholder> ParagraphPlaceholder::setOffset(float offset) {
        this->offset = offset;
        return shared_from_this();
    }

    float ParagraphPlaceholder::getOffset() {
        return this->offset;
    }

    Size ParagraphPlaceholder::getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, Boundaries boundaries) {
        return this->getChild()->getSize(ctx, window, boundaries);
    }

    std::vector <RenderElement> ParagraphPlaceholder::getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) {
        RenderElement childElement{this->getChild(), {0, 0}, rect.size};
        return {childElement};
    }
}