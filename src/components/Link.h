//
// Created by noartem on 02.02.2023.
//

#ifndef ELEMENTOR_COMPONENTS_LINK_H
#define ELEMENTOR_COMPONENTS_LINK_H

#include "utility.h"
#include "elementor.h"

namespace elementor::components {
    class Link : public Component {
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
}

#endif //ELEMENTOR_COMPONENTS_LINK_H
