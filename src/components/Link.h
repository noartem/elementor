//
// Created by noartem on 02.02.2023.
//

#ifndef ELEMENTOR_COMPONENTS_LINK_H
#define ELEMENTOR_COMPONENTS_LINK_H

#include "utility.h"
#include "elementor.h"

namespace elementor::components {
    class Link : public Component, public std::enable_shared_from_this<Link> {
    public:
        Link();

        std::shared_ptr<Link> setLabel(std::u32string newLabel);

        std::shared_ptr<Link> setLabel(std::string newLabel);

        std::string getLabel();

        std::shared_ptr<Link> setURL(std::u32string url);

        std::shared_ptr<Link> setURL(std::string url);

        std::string getURL();

        std::shared_ptr<Link> setTextElement(std::shared_ptr<Text> textElement);

        std::shared_ptr<Text> getTextElement();

    private:
        std::string label;
        std::string url;
        std::shared_ptr<Text> textElement;

        void render();
    };

    std::shared_ptr<Link> link();
}

#endif //ELEMENTOR_COMPONENTS_LINK_H
