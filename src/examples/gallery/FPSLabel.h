//
// Created by noartem on 03.08.2022.
//

#ifndef GALLERY_FPS_LABEL_H
#define GALLERY_FPS_LABEL_H

#include "utility.h"

class FPSLabel : public Element {
public:
    FPSLabel();

    Size getSize(ApplicationContext *ctx, Window *window, Boundaries boundaries) override;

    std::vector <RenderElement> getChildren(ApplicationContext *ctx, Window *window, Size size) override;

private:
    Text *child;
};

FPSLabel *fpsLabel();

#endif //GALLERY_FPS_LABEL_H
