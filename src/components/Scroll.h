//
// Created by noartem on 30.05.2022.
//

#ifndef ELEMENTOR_COMPONENTS_SCROLL_H
#define ELEMENTOR_COMPONENTS_SCROLL_H

#include "utility.h"
#include "elementor.h"

namespace elementor::components {
    class Scroll : public Component, public std::enable_shared_from_this<Scroll> {
    public:
        Scroll();

        std::shared_ptr<Scroll> setChild(const std::shared_ptr<Element>& child);

    private:
        std::shared_ptr<Scrollable> scrollableElement;
    };

    std::shared_ptr<Scroll> scroll();
}

#endif //ELEMENTOR_COMPONENTS_SCROLL_H
