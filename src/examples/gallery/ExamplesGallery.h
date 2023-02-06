//
// Created by noartem on 03.06.2022.
//

#ifndef GALLERY_EXAMPLES_GALLERY_H
#define GALLERY_EXAMPLES_GALLERY_H

#include "utility.h"
#include "Example.h"

class ExamplesGallery : public Component {
public:
    ExamplesGallery();

    void setActiveExample(Example *activeExample);

private:
    std::shared_ptr<Empty> activeExampleElement;
    std::shared_ptr<Empty> activeExampleLabelName;
    std::shared_ptr<Empty> activeExampleLabelDescription;

    std::shared_ptr<Element> makeExamplesList();
};

#endif //GALLERY_EXAMPLES_GALLERY_H
