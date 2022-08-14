//
// Created by noartem on 04.08.2022.
//

#include "Paragraph.h"
#include "../String.h"
#include "ParagraphPlaceholder.h"

#include <include/core/SkFontMgr.h>
#include <include/core/SkFontStyle.h>
#include <modules/skparagraph/include/TypefaceFontProvider.h>

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
        this->skParagraph = NULL;
        return this;
    }

    TextDirection Paragraph::getTextDirection() {
        return this->textDirection;
    }

    Paragraph *Paragraph::setTextDirection(TextDirection textDirection) {
        this->textDirection = textDirection;
        this->skParagraph = NULL;
        return this;
    }

    Paragraph *Paragraph::appendChild(Element *child) {
        this->addChild(child);

        Text *childText = dynamic_cast<Text *>(child);
        if (childText) {
            this->childrenText.push_back(childText);
        } else {
            this->childrenElements.push_back(child);
        }

        this->skParagraph = NULL;
        return this;
    }

    sk_sp<sktextlayout::FontCollection> Paragraph::makeFontCollection(ApplicationContext *ctx) {
        sk_sp<sktextlayout::FontCollection> fontCollection = sk_make_sp<sktextlayout::FontCollection>();
        fontCollection->setDefaultFontManager(SkFontMgr::RefDefault());
        fontCollection->setDynamicFontManager(ctx->getSkFontManager());
        return fontCollection;
    }

    sktextlayout::TextStyle Paragraph::makeDefaultTextStyle() {
        sktextlayout::TextStyle textStyle;
        textStyle.setFontSize(16);
        textStyle.setColor(SK_ColorBLACK);
        textStyle.setFontStyle(SkFontStyle{SkFontStyle::Weight::kNormal_Weight, 
                                           SkFontStyle::Width::kNormal_Width,
                                           SkFontStyle::Slant::kUpright_Slant});
        return textStyle;
    }

    sktextlayout::ParagraphStyle Paragraph::makeParagraphStyle() {
        sktextlayout::ParagraphStyle paragrphStyle{};
        paragrphStyle.setTextStyle(this->makeDefaultTextStyle());
        paragrphStyle.setTextDirection(this->getSkTextDirection());
        return paragrphStyle;
    }

    sktextlayout::ParagraphBuilderImpl Paragraph::makeBuilder(ApplicationContext *ctx) {
        sktextlayout::ParagraphStyle paragrphStyle = this->makeParagraphStyle();
        sk_sp<sktextlayout::FontCollection> fontCollection = this->makeFontCollection(ctx);
        sktextlayout::ParagraphBuilderImpl builder {paragrphStyle, fontCollection};
        return builder;
    }

    sktextlayout::TextAlign Paragraph::getSkTextAlign() {
        switch(this->textAlign) {
            case TextAlign::Left:
                return sktextlayout::TextAlign::kLeft;
            case TextAlign::Right:
                return sktextlayout::TextAlign::kRight;
            case TextAlign::Center:
                return sktextlayout::TextAlign::kCenter;
            case TextAlign::Justify:
                return sktextlayout::TextAlign::kJustify;
            case TextAlign::Start:
                return sktextlayout::TextAlign::kStart;
            case TextAlign::End:
                return sktextlayout::TextAlign::kEnd; 
            default:
                return sktextlayout::TextAlign::kLeft;
        }
    }

    sktextlayout::TextDirection Paragraph::getSkTextDirection() {
        switch(this->textDirection) {
            case TextDirection::LTR:
                return sktextlayout::TextDirection::kLtr;
            case TextDirection::RTL:
                return sktextlayout::TextDirection::kRtl;
            default:
                return sktextlayout::TextDirection::kLtr;
        }
    }

    sktextlayout::PlaceholderStyle Paragraph::makeChildPlaceholderStyle(ApplicationContext *ctx, Window *window, Element *child) {
        Size childSize = child->getSize(ctx, window, {{0, 0}, {INFINITY, INFINITY}});

        ParagraphPlaceholder *childPlaceholder = dynamic_cast<ParagraphPlaceholder *>(child);
        if (childPlaceholder) {
            return sktextlayout::PlaceholderStyle(childSize.width, childSize.height,
                                            childPlaceholder->getSkPlaceholderAlignment(),
                                            childPlaceholder->getSkBaseline(),
                                            childPlaceholder->getOffset());
        } else {
            return sktextlayout::PlaceholderStyle(childSize.width, childSize.height,
                                            sktextlayout::PlaceholderAlignment::kMiddle,
                                            sktextlayout::TextBaseline::kAlphabetic,
                                            ZERO);
        }
    }

    std::unique_ptr<sktextlayout::Paragraph> Paragraph::makeSkParagraph(ApplicationContext *ctx, Window *window) {
        sktextlayout::ParagraphBuilderImpl builder = this->makeBuilder(ctx);

        for (Element *child : this->getChildrenList()) {
            Text *childText = dynamic_cast<Text *>(child);
            if (childText) {
                builder.pushStyle(childText->makeSkTextStyle(window));
                builder.addText(childText->getText().c_str(), childText->getText().size());
                builder.pop();
            } else {
                builder.addPlaceholder(this->makeChildPlaceholderStyle(ctx, window, child));
            }
        }

        std::unique_ptr<sktextlayout::Paragraph> paragraph = builder.Build();

        paragraph->updateTextAlign(this->getSkTextAlign());

        return paragraph;
    }

    Size Paragraph::getSize(ApplicationContext *ctx, Window *window, Boundaries boundaries) {
        if (this->skParagraph == NULL) this->skParagraph = this->makeSkParagraph(ctx, window);

        this->skParagraph->layout(boundaries.max.width);
        return fitSizeInBoundaries({this->skParagraph->getMaxWidth(), this->skParagraph->getHeight()}, boundaries);
    }

    void Paragraph::paintBackground(ApplicationContext *ctx, Window *window, SkCanvas *canvas, ElementRect rect) {
        if (this->skParagraph == NULL) this->skParagraph = this->makeSkParagraph(ctx, window);

        this->skParagraph->layout(rect.size.width);
        this->skParagraph->paint(canvas, 0, 0);
    }

    std::vector <RenderElement> Paragraph::getChildren(ApplicationContext *ctx, Window *window, Size size) {
        if (this->skParagraph == NULL) this->skParagraph = this->makeSkParagraph(ctx, window);

        std::vector <RenderElement> children;
        std::vector<sktextlayout::TextBox> childsRects = this->skParagraph->getRectsForPlaceholders();
        int childrenSize = std::min((int) childsRects.size(), (int) this->getChildrenSize());
        for (unsigned int i = 0; i < childrenSize; i++) {
            RenderElement child;
            child.element = this->childrenElements[i];
            SkRect childRect = childsRects[i].rect;
            child.position = {childRect.x(), childRect.y()};
            child.size = {childRect.width(), childRect.height()};        
            children.push_back(child);
        }

        return children;
    }
}