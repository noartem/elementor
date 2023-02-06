//
// Created by noartem on 29.05.2022.
//

#ifndef ELEMENTOR_WIDTH_H
#define ELEMENTOR_WIDTH_H

#include "../Element.h"

namespace elementor::elements {
    class Width : public Element, public WithChild, public std::enable_shared_from_this<Width> {
    public:
        std::shared_ptr<Width> setWidth(float width);

        float getWidth();

        std::shared_ptr<Width> setChild(const std::shared_ptr<Element>& child);

        Size getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, Boundaries boundaries) override;

        std::vector <RenderElement> getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) override;

    private:
        float width = 0;
    };

    std::shared_ptr<Width> width();
}


#endif //ELEMENTOR_WIDTH_H
