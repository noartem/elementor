//
// Created by noartem on 25.08.2022.
//

#include "TextInput.h"
#include "WithCursor.h"

namespace elementor::components {
    std::shared_ptr<TextInput> textInput() {
        return std::make_shared<TextInput>();
    }

    TextInput::TextInput() {
        this->inputableChild = inputable();

        std::shared_ptr<Paragraph> paragraphElement = paragraph();
        std::shared_ptr<Text> textElement = text();
        std::shared_ptr<Border> borderElement = border();

        this->element = background()
            ->setColor("#FFFFFF")
            ->setChild(hoverable()
                ->setChild(withCursor()
                    ->setChild(this->inputableChild
                        ->setChild(borderElement
                            ->setWidth(4)
                            ->setColor("#DEEDE6")
                            ->setRadius(4)
                            ->setChild(rounded()
                                ->setRadius(4)
                                ->setChild(padding()
                                    ->setPaddings(8)
                                    ->setChild(height()
                                        ->setHeight(15)
                                        ->setChild(paragraphElement
                                            ->appendChild(textElement
                                                ->setFontColor("#3F4944")
                                                ->setFontSize(16)
                                                ->setFontWeight(500)
                                                ->setFontFamily("Fira Code")))))))
                        ->setText(this->value)
                        ->onChange([this, textElement, paragraphElement] (std::u32string newValue) {
                            if (this->callbackChange) newValue = this->callbackChange(newValue);
                            textElement->setText(newValue);
                            paragraphElement->forceUpdate();
                            this->value = newValue;
                            return newValue;
                        })
                        ->onFocus([this, borderElement] () {
                            this->focused = true;
                            borderElement->setColor("#7FB6A4");
                        })
                        ->onBlur([this, borderElement] () {
                            this->focused = false;
                            borderElement->setColor("#DEEDE6");
                        }))
                    ->setCursorShape(CursorShape::IBeam))
                ->onEnter([this, borderElement] () { if (!this->focused) borderElement->setColor("#B9D3C9"); })
                ->onLeave([this, borderElement] () { if (!this->focused) borderElement->setColor("#DEEDE6"); }));
    }

    std::shared_ptr<TextInput> TextInput::setValue(const std::u32string &newValue) {
        this->value = newValue;
        if (this->inputableChild) {
            this->inputableChild->setText(newValue);
        }
        return shared_from_this();
    }

    std::u32string TextInput::getValue() {
        return this->value;
    }

    std::shared_ptr<TextInput> TextInput::onChange(std::function<std::u32string(std::u32string newValue)> callback) {
        this->callbackChange = std::move(callback);
        return shared_from_this();
    }
}