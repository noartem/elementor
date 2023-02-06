//
// Created by noartem on 04.05.2022.
//

#ifndef ELEMENTOR_WRAP_H
#define ELEMENTOR_WRAP_H

#include "../Element.h"

namespace elementor::elements {
    enum class WrapDirection {
        Row,
        Column,
    };

    class Wrap : public Element, public WithChildren, public std::enable_shared_from_this<Wrap> {
    public:
        std::shared_ptr<Wrap> setSpacing(float spacing);

        float getSpacing() const;

        std::shared_ptr<Wrap> setCrossSpacing(float spacing);

        float getCrossSpacing() const;

        std::shared_ptr<Wrap> setSpacing(float spacing, float crossSpacing);

        std::shared_ptr<Wrap> setDirection(WrapDirection direction);

        WrapDirection getDirection();

        std::shared_ptr<Wrap> appendChild(const std::shared_ptr<Element>& child);

        Size getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, Boundaries boundaries) override;

        std::vector <RenderElement> getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) override;

    private:
        float spacing = 0;
        float crossSpacing = 0;
        WrapDirection direction = WrapDirection::Row;
    };

    std::shared_ptr<Wrap> wrap();
}


#endif //ELEMENTOR_WRAP_H
