//
// Created by noartem on 15.04.2022.
//

#ifndef ELEMENTOR_BACKGROUND_H
#define ELEMENTOR_BACKGROUND_H

#include "../Element.h"

namespace elementor::elements {
    class Background : public Element, public WithChild, public std::enable_shared_from_this<Background> {
    public:
        Background() : Element(), WithChild() {}

        std::shared_ptr<Background> setColor(SkColor skColor);

        std::shared_ptr<Background> setColor(uint8_t r, uint8_t g, uint8_t b);

        std::shared_ptr<Background> setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

        std::shared_ptr<Background> setColor(std::string hex);

        SkColor getColor() const;

        std::shared_ptr<Background> setChild(const std::shared_ptr<Element>& child);

        void paintBackground(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, SkCanvas *canvas,
                             ElementRect rect) override;

        Size getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window,
                     Boundaries boundaries) override;

        std::vector<RenderElement>
        getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) override;

    private:
        SkColor color{};
    };

    std::shared_ptr<Background> background();
}


#endif //ELEMENTOR_BACKGROUND_H
