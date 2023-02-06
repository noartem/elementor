//
// Created by noartem on 27.04.2022.
//

#ifndef ELEMENTOR_BORDER_H
#define ELEMENTOR_BORDER_H

#include "../Element.h"

namespace elementor::elements {
    enum class BorderStyle {
        Solid,
        Dotted,
        Dashed,
    };

    class Border : public Element, public WithChild, public std::enable_shared_from_this<Border> {
    public:
        std::shared_ptr<Border> setColor(SkColor color);

        std::shared_ptr<Border> setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

        std::shared_ptr<Border> setColor(uint8_t r, uint8_t g, uint8_t b);

        std::shared_ptr<Border> setColor(std::string hex);

        SkColor getColor();

        std::shared_ptr<Border> setWidth(float width);

        float getWidth();

        std::shared_ptr<Border> setRadius(float radiusX, float radiusY);

        std::shared_ptr<Border> setRadius(float radiusXY);

        float getRadiusX();

        float getRadiusY();

        std::shared_ptr<Border> setStyle(BorderStyle style);

        BorderStyle getStyle();

        std::shared_ptr<Border> setChild(const std::shared_ptr<Element>& child);

        Size getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window,
                     Boundaries boundaries) override;

        void paintBackground(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, SkCanvas *canvas,
                             ElementRect rect) override;

        std::vector<RenderElement>
        getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) override;

    private:
        float width = 0.0;
        float radiusX = 0.0;
        float radiusY = 0.0;
        SkColor color;
        BorderStyle style = BorderStyle::Solid;
    };

    std::shared_ptr<Border> border();
}


#endif //ELEMENTOR_BORDER_H
