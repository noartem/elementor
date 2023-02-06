//
// Created by noartem on 18.04.2022.
//

#ifndef ELEMENTOR_COLUMN_H
#define ELEMENTOR_COLUMN_H

#include "../Element.h"

namespace elementor::elements {
    class Column : public Element, public WithChildren, public std::enable_shared_from_this<Column> {
    public:
        std::shared_ptr<Column> setSpacing(float newSpacing);

        float getSpacing() const;

        std::shared_ptr<Column> appendChild(const std::shared_ptr<Element>& child);

        Size getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window,
                     Boundaries boundaries) override;

        std::vector<RenderElement>
        getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) override;

    private:
        float spacing = 0;
    };

    std::shared_ptr<Column> column();
}


#endif //ELEMENTOR_COLUMN_H
