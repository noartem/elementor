//
// Created by noartem on 02.02.2023.
//

#include "Link.h"
#include "WithCursor.h"

namespace elementor::components {
    Link *link() {
        return new Link();
    }

    Link::Link() {
    this->textElement = text()
        ->setFontColor("#0078D4");

        this->render();
    }

    void Link::render() {
        this->element = clickable()
            ->setChild(this->textElement
                ->setText(this->label))
            //            ->setChild(withCursor()
//                ->setChild(this->textElement
//                    ->setText(this->label))
//                ->setCursorShape(CursorShape::Hand))
            ->onClick([this] () {
                openURL(this->url);
            });
    }

    Link *Link::setLabel(std::u32string label) {
        this->label = toUTF8(label);
        this->textElement->setText(this->label);
        return this;
    }

    Link *Link::setLabel(std::string label) {
        this->label = label;
        this->textElement->setText(this->label);
        return this;
    }

    std::string Link::getLabel() {
        return this->label;
    }

    Link *Link::setURL(std::u32string url) {
        this->url = toUTF8(url);
        return this;
    }

    Link *Link::setURL(std::string url) {
        this->url = url;
        return this;
    }

    std::string Link::getURL() {
        return this->url;
    }

    Link *Link::setTextElement(Text *textElement) {
        this->textElement = textElement;
        this->render();
        return this;
    }

    Text *Link::getTextElement() {
        return this->textElement;
    }
}