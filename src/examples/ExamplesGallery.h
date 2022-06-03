//
// Created by noartem on 03.06.2022.
//

#ifndef ELEMENTOR_EXAMPLES_GALLERY_H
#define ELEMENTOR_EXAMPLES_GALLERY_H

#include "utility.h"
#include "Example.h"

class ExamplesGallery: public Element {
public:
    ExamplesGallery();

    std::vector<Example *> getExamples();

    void setActiveExample(Example *activeExample);

    std::vector <RenderElement> getChildren(ApplicationContext *ctx, Size size) override;

private:
    Element *scene;
    Example *activeExample;
    Empty *activeExampleElement;
    Empty *activeExampleLabelName;
    Empty *activeExampleLabelDescription;

    Column *makeExamplesList();
};

#endif //ELEMENTOR_EXAMPLES_GALLERY_H
