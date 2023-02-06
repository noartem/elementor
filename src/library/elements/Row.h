//
// Created by noartem on 18.04.2022.
//

#ifndef ELEMENTOR_ROW_H
#define ELEMENTOR_ROW_H

#include "../Element.h"

namespace elementor::elements {
    class Row : public Element, public WithChildren, public std::enable_shared_from_this<Row> {
    public:
        std::shared_ptr<Row> setSpacing(float newSpacing);

        float getSpacing() const;

        std::shared_ptr<Row> appendChild(const std::shared_ptr<Element>& child);

        Size getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, Boundaries boundaries) override;

        std::vector <RenderElement> getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) override;

    private:
        float spacing = 0;
    };

    std::shared_ptr<Row> row();
}


#endif //ELEMENTOR_ROW_H
