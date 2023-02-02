//
// Created by noartem on 02.02.2023.
//

#ifndef GALLERY_LINK_H
#define GALLERY_LINK_H

#include "utility.h"

class Link : public Component  {
public:
    Link();

    Link *setLabel(std::u32string label);

    Link *setLabel(std::string label);

    std::string getLabel();

    Link *setURL(std::u32string url);

    Link *setURL(std::string url);

    std::string getURL();

    Link *setTextElement(Text *textElement);

    Text *getTextElement();

private:
    std::string label;
    std::string url;
    Text *textElement;

    void render();
};

Link *link();

#endif //GALLERY_LINK_H
