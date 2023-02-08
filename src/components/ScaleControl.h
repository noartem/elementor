//
// Created by noartem on 20.08.2022.
//

#ifndef ELEMENTOR_COMPONENTS_SCALE_CONTROL_H
#define ELEMENTOR_COMPONENTS_SCALE_CONTROL_H

#include "utility.h"
#include "elementor.h"

namespace elementor::components {
    class ScaleControl : public Component, public std::enable_shared_from_this<ScaleControl> {
    public:
        ScaleControl();

        std::vector<RenderElement> getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) override;

    private:
        int scalePercentage = 100;
        float initialPixelScale = 0;
        std::shared_ptr<Text> scalePercentageText;

        void applyScale();

        void incrementScale();

        void decrementScale();
    };

    std::shared_ptr<ScaleControl> scaleControl();
}

#endif //ELEMENTOR_COMPONENTS_SCALE_CONTROL_H
