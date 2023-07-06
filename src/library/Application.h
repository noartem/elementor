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
        std::vector <std::shared_ptr<ElementNode>> children;
        std::weak_ptr <ElementNode> parent;
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
        std::shared_ptr <ElementNode> rootNode;
        std::map <std::string, std::vector<std::shared_ptr < ElementNode>>>
        eventListeners;
        std::vector <std::shared_ptr<ElementNode>> hoveredElements;

        std::shared_ptr <ElementNode> makeRootNode();

        std::shared_ptr <ElementNode> makeNode(const RenderElement &element, const ElementRect &rect, const Rect &boundary);

        void saveNodeEventListeners(const std::shared_ptr <ElementNode> &node);

        void drawNode(const std::shared_ptr <ElementNode> &node, SkCanvas *canvas);

        void setHoveredElements(const std::vector <std::shared_ptr<ElementNode>> &newValue);

        void onMouseMove(const std::shared_ptr <EventMouseMove> &event);
    };
};


#endif //ELEMENTOR_APPLICATION_H
