//
// Created by noartem on 25.08.2022.
//

#include "TextInput.h"
#include "WithCursor.h"

#include <iostream>

TextInput *textInput() {
    return new TextInput();
}

TextInput::TextInput() {
    this->inputableChild = inputable();

    Paragraph *paragraphRef = paragraph();
    Text *textRef = text();
    Border *borderRef = border();

    this->element = background()
        ->setColor("#FFFFFF")
        ->setChild(hoverable()
            ->setChild(withCursor()
                ->setChild(this->inputableChild
                    ->setChild(borderRef
                        ->setWidth(4)
                        ->setColor("#DEEDE6")
                        ->setRadius(4)
                        ->setChild(rounded()
                            ->setRadius(4)
                            ->setChild(padding()
                            ->setPaddings(8)
                            ->setChild(height()
                                ->setHeight(15)
                                ->setChild(paragraphRef
                                    ->appendChild(textRef
                                        ->setFontColor("#3F4944")
                                        ->setFontSize(16)
                                        ->setFontWeight(500)
                                        ->setFontFamily("Fira Code")))))))
                    ->setText(this->value)
                    ->onChange([this, textRef, paragraphRef] (std::u32string value) {
                        if (this->callbackChange) value = this->callbackChange(value);
                        textRef->setText(value);
                        paragraphRef->forceUpdate();
                        this->value = value;
                        return value;
                    })
                    ->onFocus([this, borderRef] () {
                        this->focused = true;
                        borderRef->setColor("#7FB6A4");
                    })
                    ->onBlur([this, borderRef] () {
                        this->focused = false;
                        borderRef->setColor("#DEEDE6");
                    }))
                ->setCursorShape(CursorShape::IBeam))
            ->onEnter([this, borderRef] () { if (!this->focused) borderRef->setColor("#B9D3C9"); })
            ->onLeave([this, borderRef] () { if (!this->focused) borderRef->setColor("#DEEDE6"); }));
}

TextInput *TextInput::setValue(std::u32string value) {
    this->value = value;
    if (this->inputableChild) {
        this->inputableChild->setText(value);
    } 
    return this;
}

std::u32string TextInput::getValue() {
    return this->value;
}

TextInput *TextInput::onChange(std::function<std::u32string (std::u32string value)> callback) {
    this->callbackChange = callback;
    return this;
}
