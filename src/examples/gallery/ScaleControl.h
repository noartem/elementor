//
// Created by noartem on 20.08.2022.
//

#ifndef GALLERY_SCALE_CONTROL_H
#define GALLERY_SCALE_CONTROL_H

#include "utility.h"

class ScaleControl : public Element {
public:
    ScaleControl();

    Size getSize(ApplicationContext *ctx, Window *window, Boundaries boundaries) override;

    std::vector <RenderElement> getChildren(ApplicationContext *ctx, Window *window, Size size) override;

private:
    ApplicationContext *ctx;
    int scalePercentage = 100;
    float initialPixelScale = 0;
    Element *child;
    Text *scalePercentageText;

    void applyScale();
    void incrementScale();
    void decrementScale();
};

ScaleControl *scaleControl();

#endif //GALLERY_SCALE_CONTROL_H
