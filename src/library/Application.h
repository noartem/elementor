//
// Created by noartem on 13.04.2022.
//

#ifndef ELEMENTOR_APPLICATION_H
#define ELEMENTOR_APPLICATION_H

#include "Element.h"
#include "Event.h"

#include <map>

namespace elementor {
    struct ElementNode {
        std::shared_ptr <Element> element;
        ElementRect rect;
        std::vector <ElementNode> children = {};
    };

    class Application {
    public:
        Application(const std::shared_ptr <ApplicationContext> &ctx, const std::shared_ptr <Window> &window) {
            this->ctx = ctx;
            this->window = window;
        }

        void draw(SkCanvas *canvas);

        void dispatchEvent(const std::shared_ptr <Event> &event);

    private:
        std::shared_ptr <ApplicationContext> ctx;
        std::shared_ptr <Window> window;
        ElementNode rootNode;
        std::map <std::string, std::vector<std::shared_ptr < Element>>>
        eventListeners;

        ElementNode makeRootNode();

        ElementNode makeNode(const RenderElement &element, const ElementRect &rect, const Rect &boundary);

        void saveElementEventListeners(const std::shared_ptr <Element> &element);

        void drawNode(const ElementNode &node, SkCanvas *canvas);
    };
};


#endif //ELEMENTOR_APPLICATION_H
