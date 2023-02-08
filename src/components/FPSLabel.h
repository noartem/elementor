//
// Created by noartem on 03.08.2022.
//

#ifndef ELEMENTOR_COMPONENTS_FPS_LABEL_H
#define ELEMENTOR_COMPONENTS_FPS_LABEL_H

#include "utility.h"
#include "elementor.h"

namespace elementor::components {
    class FPSLabel : public Component, public std::enable_shared_from_this<FPSLabel> {
    public:
        FPSLabel();

        std::vector<RenderElement> getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) override;

    private:
        std::shared_ptr<Text> textElement;
    };

    std::shared_ptr<FPSLabel> fpsLabel();
}

#endif //ELEMENTOR_COMPONENTS_FPS_LABEL_H
