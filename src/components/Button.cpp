//
// Created by noartem on 03.02.2023.
//

#include "Button.h"
#include "WithCursor.h"

namespace elementor::components {
    std::shared_ptr<Button> button() {
        return std::make_shared<Button>();
    }

    Button::Button() {
        this->clickableElement = clickable();
        this->textElement = text();
        this->backgroundElement = background();

        this->element = this->clickableElement
            ->setChild(withCursor()
                ->setChild(rounded()
                    ->setRadius(8)
                    ->setChild(this->backgroundElement
                        ->setColor("#DEEDE6")
                        ->setChild(padding()
                            ->setPaddings(12, 18)
                            ->setChild(height()
                                ->setHeight(12)
                                ->setChild(this->textElement
                                    ->setFontColor("#006C4C")
                                    ->setFontSize(16)
                                    ->setFontWeight(450)
                                    ->setFontFamily("Fira Code")
                                    ->setText(this->label))))))
                ->setCursorShape(CursorShape::Hand));
    }

    std::shared_ptr<Button> Button::setLabel(std::u32string newLabel) {
        return this->setLabel(toUTF8(newLabel));
    }

    std::shared_ptr<Button> Button::setLabel(std::string newLabel) {
        this->label = std::move(newLabel);
        this->textElement->setText(this->label);
        return shared_from_this();
    }

    std::string Button::getLabel() {
        return this->label;
    }

    std::shared_ptr<Button> Button::onClick(const std::function<void()>& callback) {
        this->clickableElement->onClick(callback);
        return shared_from_this();
    }

    std::shared_ptr<Button> Button::setBackgroundColor(std::string hex) {
        this->backgroundElement->setColor(std::move(hex));
        return shared_from_this();
    }

    std::shared_ptr<Button> Button::setTextColor(std::string hex) {
        this->textElement->setFontColor(std::move(hex));
        return shared_from_this();
    }
}