//
// Created by noartem on 13.04.2022.
//

#ifndef ELEMENTOR_APPLICATION_H
#define ELEMENTOR_APPLICATION_H

#include "Element.h"
#include "Event.h"

#include <map>

namespace elementor {
    class Application {
    public:
        Element *root;

        void draw(ApplicationContext *ctx, SkCanvas *canvas);

        void dispatchEvent(Event *event);
    
    private:
        std::map<std::string, std::vector<Element*>> eventListeners;

        void saveElementEventListeners(Element *element);

        void drawElement(ApplicationContext *ctx, SkCanvas *canvas, RenderElement *element, ElementRect rect, Rect boundary);
    };
};


#endif //ELEMENTOR_APPLICATION_H
