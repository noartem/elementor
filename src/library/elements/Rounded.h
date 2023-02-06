//
// Created by noartem on 21.04.2022.
//

#ifndef ELEMENTOR_ROUNDED_H
#define ELEMENTOR_ROUNDED_H

#include "../Element.h"

namespace elementor::elements {
    class Rounded : public Element, public WithChild, public std::enable_shared_from_this<Rounded> {
    public:
        std::shared_ptr<Rounded> setRadius(float radiusTopLeft, float radiusTopRight, float radiusBottomLeft, float radiusBottomRight);

        std::shared_ptr<Rounded> setRadius(float radiusLeft, float radiusRight);

        std::shared_ptr<Rounded> setRadius(float radius);

        float getRadiusTopLeft() const;

        float getRadiusTopRight() const;

        float getRadiusBottomLeft() const;

        float getRadiusBottomRight() const;

        std::shared_ptr<Rounded> setChild(const std::shared_ptr<Element>& child);

        void paintBackground(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, SkCanvas *canvas, ElementRect rect) override;

        Size getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, Boundaries boundaries) override;

        std::vector <RenderElement> getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) override;

        ClipBehavior getClipBehaviour() override;

    private:
        float radiusTopLeft;
        float radiusTopRight;
        float radiusBottomLeft;
        float radiusBottomRight;
    };

    std::shared_ptr<Rounded> rounded();
}


#endif //ELEMENTOR_ROUNDED_H
