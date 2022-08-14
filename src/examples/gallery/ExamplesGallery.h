//
// Created by noartem on 03.06.2022.
//

#ifndef GALLERY_EXAMPLES_GALLERY_H
#define GALLERY_EXAMPLES_GALLERY_H

#include "utility.h"
#include "Example.h"

class ExamplesGallery: public Element {
public:
    ExamplesGallery();

    std::vector<Example *> getExamples();

    void setActiveExample(Example *activeExample);

    std::vector <RenderElement> getChildren(ApplicationContext *ctx, Window *window, Size size) override;

private:
    Element *scene;
    Example *activeExample;
    Empty *activeExampleElement;
    Empty *activeExampleLabelName;
    Empty *activeExampleLabelDescription;

    Column *makeExamplesList();
};

#endif //GALLERY_EXAMPLES_GALLERY_H
