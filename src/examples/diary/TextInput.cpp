//
// Created by noartem on 28.06.2022.
//

#include "TextInput.h"

#include <iostream>

TextInput *textInput() {
    return new TextInput();
}

TextInput::TextInput() {
    Text *inputableText = text()
        ->setFontColor("#2B1615")
        ->setFontFamily("Times New Roman")
        ->setFontSize(20)
        ->setText("");

    Border *inputableContent = border()
        ->setWidth(4)
        ->setColor("#FFDAD8")
        ->setRadius(4)
        ->setChild(rounded()
            ->setRadius(4)
            ->setChild(padding()
            ->setPaddings(12, 16)
            ->setChild(height()
                ->setHeight(18)
                ->setChild(inputableText))));

    this->child = background()
        ->setColor("#FFFFFF")
        ->setChild(hoverable()
            ->setChild(inputable()
                ->setChild(inputableContent)
                ->onChange([inputableText] (std::string value) {
                    inputableText->setText(value);
                    return value;
                })
                ->onFocus([this, inputableContent] () {
                    this->focused = true;
                    inputableContent->setColor("#FFB4AD");
                })
                ->onBlur([this, inputableContent] () {
                    this->focused = false;
                    inputableContent->setColor("#FFDAD8");
                }))
            ->onEnter([this, inputableContent] () {
                if (!this->focused) {
                    inputableContent->setColor("#E5BEBD"); 
                }
            })
            ->onLeave([this, inputableContent] () {
                if (!this->focused) {
                    inputableContent->setColor("#FFDAD8"); 
                }
            }));
}

Size TextInput::getSize(ApplicationContext *ctx, Boundaries boundaries) {
    return this->child->getSize(ctx, boundaries);
}

std::vector <RenderElement> TextInput::getChildren(ApplicationContext *ctx, Size size) {
    RenderElement child;
    child.element = this->child;
    child.size = size;
    child.position = {0, 0};
    return {child};
}