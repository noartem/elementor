//
// Created by noartem on 30.06.2022.
//

#ifndef DIARY_ENTRY_ELEMENT_H
#define DIARY_ENTRY_ELEMENT_H

#include "DiaryEntry.h"
#include "utility.h"

class DiaryEntryElement : public Element {
public:
    DiaryEntryElement(DiaryEntry *entry);

    Size getSize(ApplicationContext *ctx, Boundaries boundaries) override;

    std::vector <RenderElement> getChildren(ApplicationContext *ctx, Size size) override;

private:
    Element *child;
};

DiaryEntryElement *diaryEntryElement(DiaryEntry *entry);

#endif //DIARY_ENTRY_ELEMENT_H
