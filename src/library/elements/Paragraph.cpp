//
// Created by noartem on 04.08.2022.
//

#include "Paragraph.h"
#include "ParagraphPlaceholder.h"

#include <include/core/SkFontMgr.h>
#include <include/core/SkFontStyle.h>
#include <modules/skparagraph/include/TypefaceFontProvider.h>

#include <memory>
#include <utility>

namespace elementor::elements {
    std::shared_ptr<Paragraph> paragraph() {
        return std::make_shared<Paragraph>();
    }

    TextAlign Paragraph::getTextAlign() {
        return this->textAlign;
    }

    std::shared_ptr<Paragraph> Paragraph::setTextAlign(TextAlign newTextAlign) {
        this->textAlign = newTextAlign;
        this->skParagraph = nullptr;
        return shared_from_this();
    }

    TextDirection Paragraph::getTextDirection() {
        return this->textDirection;
    }

    std::shared_ptr<Paragraph> Paragraph::setTextDirection(TextDirection newTextDirection) {
        this->textDirection = newTextDirection;
        this->skParagraph = nullptr;
        return shared_from_this();
    }

    std::shared_ptr<Paragraph> Paragraph::appendChild(const std::shared_ptr<Element> &child) {
        this->addChild(child);

        std::shared_ptr<Text> childText = dynamic_cast<std::shared_ptr<Text>>(child);
        if (childText) {
            this->childrenText.push_back(childText);
        } else {
            this->childrenElements.push_back(child);
        }

        this->skParagraph = nullptr;
        return shared_from_this();
    }

    void Paragraph::forceUpdate() {
        this->skParagraph = nullptr;
    }

    sk_sp<sktextlayout::FontCollection> Paragraph::makeFontCollection(const std::shared_ptr<ApplicationContext>& ctx) {
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
        sktextlayout::ParagraphStyle paragraphStyle{};
        paragraphStyle.setTextStyle(this->makeDefaultTextStyle());
        paragraphStyle.setTextDirection(this->getSkTextDirection());
        return paragraphStyle;
    }

    sktextlayout::ParagraphBuilderImpl Paragraph::makeBuilder(const std::shared_ptr<ApplicationContext>& ctx) {
        sktextlayout::ParagraphStyle paragraphStyle = this->makeParagraphStyle();
        sk_sp<sktextlayout::FontCollection> fontCollection = this->makeFontCollection(ctx);
        sktextlayout::ParagraphBuilderImpl builder{paragraphStyle, fontCollection};
        return builder;
    }

    sktextlayout::TextAlign Paragraph::getSkTextAlign() {
        switch (this->textAlign) {
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
        switch (this->textDirection) {
            case TextDirection::LTR:
                return sktextlayout::TextDirection::kLtr;
            case TextDirection::RTL:
                return sktextlayout::TextDirection::kRtl;
            default:
                return sktextlayout::TextDirection::kLtr;
        }
    }

    sktextlayout::PlaceholderStyle
    Paragraph::makeChildPlaceholderStyle(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window,
                                         const std::shared_ptr<Element>& child) {
        Size childSize = child->getSize(ctx, window, {{0, 0},
                                                      {INFINITY, INFINITY}});

        auto *childPlaceholder = dynamic_cast<std::shared_ptr<ParagraphPlaceholder> >(child);
        if (childPlaceholder) {
            return {childSize.width, childSize.height,
                    childPlaceholder->getSkPlaceholderAlignment(),
                    childPlaceholder->getSkBaseline(),
                    childPlaceholder->getOffset()};
        } else {
            return {childSize.width, childSize.height,
                    sktextlayout::PlaceholderAlignment::kMiddle,
                    sktextlayout::TextBaseline::kAlphabetic,
                    ZERO};
        }
    }

    std::unique_ptr<sktextlayout::Paragraph>
    Paragraph::makeSkParagraph(const std::shared_ptr<ApplicationContext>& ctx, const std::shared_ptr<Window>& window) {
        sktextlayout::ParagraphBuilderImpl builder = this->makeBuilder(ctx);

        for (const std::shared_ptr<Element> &child: this->getChildrenList()) {
            std::shared_ptr<Text> childText = dynamic_cast<std::shared_ptr<Text>>(child);
            if (childText) {
                builder.pushStyle(childText->makeSkTextStyle(ctx));
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

    Size
    Paragraph::getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, Boundaries boundaries) {
        if (this->skParagraph == nullptr || ctx->getPixelScale() != this->lastPixelScale)
            this->skParagraph = this->makeSkParagraph(ctx, window);
        this->lastPixelScale = ctx->getPixelScale();

        this->skParagraph->layout(boundaries.max.width);
        return fitSizeInBoundaries({this->skParagraph->getMaxWidth(), this->skParagraph->getHeight()}, boundaries);
    }

    void Paragraph::paintBackground(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window,
                                    SkCanvas *canvas, ElementRect rect) {
        if (this->skParagraph == nullptr || ctx->getPixelScale() != this->lastPixelScale)
            this->skParagraph = this->makeSkParagraph(ctx, window);
        this->lastPixelScale = ctx->getPixelScale();

        this->skParagraph->layout(rect.size.width);
        this->skParagraph->paint(canvas, 0, 0);
    }

    std::vector<RenderElement>
    Paragraph::getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) {
        if (this->skParagraph == nullptr || ctx->getPixelScale() != this->lastPixelScale)
            this->skParagraph = this->makeSkParagraph(ctx, window);
        this->lastPixelScale = ctx->getPixelScale();

        std::vector<RenderElement> children;
        std::vector<sktextlayout::TextBox> childsRects = this->skParagraph->getRectsForPlaceholders();
        int childrenSize = std::min((int) childsRects.size(), (int) this->getChildrenSize());
        for (unsigned int i = 0; i < childrenSize; i++) {
            RenderElement child{};
            child.element = this->childrenElements[i];
            SkRect childRect = childsRects[i].rect;
            child.position = {childRect.x(), childRect.y()};
            child.size = {childRect.width(), childRect.height()};
            children.push_back(child);
        }

        return children;
    }
}