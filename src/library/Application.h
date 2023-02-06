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
        void draw(const std::shared_ptr<ApplicationContext>& ctx, const std::shared_ptr<Window>& window, SkCanvas *canvas);
        void dispatchEvent(const std::shared_ptr<Event>& event);

    private:
        std::map<std::string, std::vector<std::shared_ptr<Element>>> eventListeners;
        void saveElementEventListeners(const std::shared_ptr<Element>& element);

        void drawElement(const std::shared_ptr<ApplicationContext>& ctx, const std::shared_ptr<Window>& window, SkCanvas *canvas, const RenderElement& element, ElementRect rect, Rect boundary);
    };
};


#endif //ELEMENTOR_APPLICATION_H
