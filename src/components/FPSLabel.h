//
// Created by noartem on 03.08.2022.
//

#ifndef ELEMENTOR_COMPONENTS_FPS_LABEL_H
#define ELEMENTOR_COMPONENTS_FPS_LABEL_H

#include "utility.h"
#include "elementor.h"

namespace elementor::components {
    class FPSLabel : public Component {
    public:
        FPSLabel();

        std::vector<RenderElement> getChildren(ApplicationContext *ctx, Window *window, ElementRect rect) override;

    private:
        Text *textElement;
    };

    FPSLabel *fpsLabel();
}

#endif //ELEMENTOR_COMPONENTS_FPS_LABEL_H
