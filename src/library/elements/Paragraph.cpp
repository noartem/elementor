//
// Created by noartem on 30.07.2022.
//

#include "Paragraph.h"
#include "../String.h"

#include <include/core/SkFontMgr.h>
#include <include/core/SkFontStyle.h>

#include <memory>

namespace elementor::elements {
    Paragraph *paragraph() {
        return new Paragraph();
    }

    TextAlign Paragraph::getTextAlign() {
        return this->textAlign;
    }

    Paragraph *Paragraph::setTextAlign(TextAlign textAlign) {
        this->textAlign = textAlign;
        return this;
    }

    TextDirection Paragraph::getTextDirection() {
        return this->textDirection;
    }

    Paragraph *Paragraph::setTextDirection(TextDirection textDirection) {
        this->textDirection = textDirection;
        return this;
    }

    Paragraph *Paragraph::appendChild(Element *child) {
        this->addChild(child);
        this->skParagraph = NULL;
        return this;
    }

    sk_sp<sktext::FontCollection> Paragraph::makeDefaultFontCollection() {
        sk_sp<sktext::FontCollection> fontCollection = sk_make_sp<sktext::FontCollection>();
        sk_sp<SkFontMgr> fontMgr = SkFontMgr::RefDefault();
        fontCollection->setDefaultFontManager(fontMgr);
        return fontCollection;
    }

    sktext::TextStyle Paragraph::makeDefaultTextStyle() {
        sktext::TextStyle textStyle;
        textStyle.setFontSize(16);
        textStyle.setColor(SK_ColorBLACK);
        textStyle.setFontStyle(SkFontStyle{SkFontStyle::Weight::kNormal_Weight, 
                                           SkFontStyle::Width::kNormal_Width,
                                           SkFontStyle::Slant::kUpright_Slant});
        return textStyle;
    }

    sktext::ParagraphStyle Paragraph::makeDefaultParagraphStyle() {
        sktext::ParagraphStyle paragrphStyle{};
        paragrphStyle.setTextStyle(this->makeDefaultTextStyle());
        paragrphStyle.setTextDirection(this->getSkTextDirection());
        return paragrphStyle;
    }

    sktext::ParagraphBuilderImpl Paragraph::makeBuilder() {
        sktext::ParagraphStyle paragrphStyle = this->makeDefaultParagraphStyle();
        sk_sp<sktext::FontCollection> fontCollection = this->makeDefaultFontCollection();
        sktext::ParagraphBuilderImpl builder {paragrphStyle, fontCollection};
        return builder;
    }

    sktext::TextAlign Paragraph::getSkTextAlign() {
        switch(this->textAlign) {
            case TextAlign::Left:
                return sktext::TextAlign::kLeft;
            case TextAlign::Right:
                return sktext::TextAlign::kRight;
            case TextAlign::Center:
                return sktext::TextAlign::kCenter;
            case TextAlign::Justify:
                return sktext::TextAlign::kJustify;
            case TextAlign::Start:
                return sktext::TextAlign::kStart;
            case TextAlign::End:
                return sktext::TextAlign::kEnd; 
            default:
                return sktext::TextAlign::kLeft;
        }
    }

    sktext::TextDirection Paragraph::getSkTextDirection() {
        switch(this->textDirection) {
            case TextDirection::LTR:
                return sktext::TextDirection::kLtr;
            case TextDirection::RTL:
                return sktext::TextDirection::kRtl;
            default:
                return sktext::TextDirection::kLtr;
        }
    }

    std::unique_ptr<sktext::Paragraph> Paragraph::makeSkParagraph(ApplicationContext *ctx) {
        sktext::ParagraphBuilderImpl builder = this->makeBuilder();

        for (Element *child : this->getChildrenList()) {
            Text *childText = dynamic_cast<Text *>(child);
            if (childText) {
                std::u32string textU32 = childText->getText();
                std::string textU8 = toUTF8(textU32);

                builder.pushStyle(childText->makeSkTextStyle(ctx));
                builder.addText(textU8.c_str(), textU8.size());
                builder.pop();
            }
        }

        std::unique_ptr<sktext::Paragraph> paragraph = builder.Build();

        paragraph->updateTextAlign(this->getSkTextAlign());

        return paragraph;
    }

    Size Paragraph::getSize(ApplicationContext *ctx, Boundaries boundaries) {
        if (this->skParagraph == NULL) {
            this->skParagraph = this->makeSkParagraph(ctx);
        }

        this->skParagraph->layout(boundaries.max.width);
        return fitSizeInBoundaries({this->skParagraph->getMaxWidth(), this->skParagraph->getHeight()}, boundaries);
    }

    void Paragraph::paintBackground(ApplicationContext *ctx, SkCanvas *canvas, ElementRect rect) {
        if (this->skParagraph == NULL) {
            this->skParagraph = this->makeSkParagraph(ctx);
        }

        this->skParagraph->layout(rect.size.width);
        this->skParagraph->paint(canvas, 0, 0);
    }
}