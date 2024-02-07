//
// Created by noartem on 02.02.2023.
//

#include "Link.h"
#include "WithCursor.h"

namespace elementor::components {
    std::shared_ptr<Link> link() {
        return std::make_shared<Link>();
    }

    Link::Link() {
        this->textElement = text()
            ->setFontColor("#0078D4");

        this->render();
    }

    void Link::render() {
        this->element = clickable()
            ->setChild(withCursor()
                ->setChild(this->textElement
                    ->setText(this->label))
                ->setCursorShape(CursorShape::Hand))
            ->onClick([this] () {
                openURL(this->url);
            });
    }

    std::shared_ptr<Link> Link::setLabel(std::u32string newLabel) {
        this->label = toUTF8(newLabel);
        this->textElement->setText(this->label);
        return shared_from_this();
    }

    std::shared_ptr<Link> Link::setLabel(std::string newLabel) {
        this->label = newLabel;
        this->textElement->setText(this->label);
        return shared_from_this();
    }

    std::string Link::getLabel() {
        return this->label;
    }

    std::shared_ptr<Link> Link::setURL(std::u32string url) {
        this->url = toUTF8(url);
        return shared_from_this();
    }

    std::shared_ptr<Link> Link::setURL(std::string url) {
        this->url = url;
        return shared_from_this();
    }

    std::string Link::getURL() {
        return this->url;
    }

    std::shared_ptr<Link> Link::setTextElement(std::shared_ptr<Text> textElement) {
        this->textElement = textElement;
        this->render();
        return shared_from_this();
    }

    std::shared_ptr<Text> Link::getTextElement() {
        return this->textElement;
    }
}