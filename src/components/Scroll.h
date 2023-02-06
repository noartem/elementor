//
// Created by noartem on 30.05.2022.
//

#ifndef ELEMENTOR_COMPONENTS_SCROLL_H
#define ELEMENTOR_COMPONENTS_SCROLL_H

#include "utility.h"
#include "elementor.h"

namespace elementor::components {
    class Scroll : public Component {
    public:
        Scroll();

        Scroll *setChild(const std::shared_ptr<Element>& child);

    private:
        std::shared_ptr<Scrollable> scrollableElement;
    };

    Scroll *scroll();
}

#endif //ELEMENTOR_COMPONENTS_SCROLL_H
