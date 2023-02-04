//
// Created by noartem on 20.08.2022.
//

#ifndef ELEMENTOR_COMPONENTS_SCALE_CONTROL_H
#define ELEMENTOR_COMPONENTS_SCALE_CONTROL_H

#include "utility.h"
#include "elementor.h"

namespace elementor::components {
    class ScaleControl : public Component {
    public:
        ScaleControl();

        std::vector<RenderElement> getChildren(ApplicationContext *ctx, Window *window, Size size) override;

    private:
        int scalePercentage = 100;
        float initialPixelScale = 0;
        Text *scalePercentageText;

        void applyScale();

        void incrementScale();

        void decrementScale();
    };

    ScaleControl *scaleControl();
}

#endif //ELEMENTOR_COMPONENTS_SCALE_CONTROL_H
