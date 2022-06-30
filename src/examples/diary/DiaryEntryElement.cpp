//
// Created by noartem on 30.06.2022.
//

#include "DiaryEntryElement.h"

DiaryEntryElement *diaryEntryElement(DiaryEntry *entry) {
    return new DiaryEntryElement(entry);
}

DiaryEntryElement::DiaryEntryElement(DiaryEntry *entry) {
    this->child = text()
        ->setFontColor("#2B1615")
        ->setFontFamily("Times New Roman")
        ->setFontSize(18)
        ->setText(entry->toString());
}

Size DiaryEntryElement::getSize(ApplicationContext *ctx, Boundaries boundaries) {
    return this->child->getSize(ctx, boundaries);
}

std::vector <RenderElement> DiaryEntryElement::getChildren(ApplicationContext *ctx, Size size) {
    RenderElement child;
    child.element = this->child;
    child.size = size;
    child.position = {0, 0};
    return {child};
}