//
// Created by noartem on 13.04.2022.
//

#ifndef ELEMENTOR_IELEMENT_H
#define ELEMENTOR_IELEMENT_H

#include <include/core/SkCanvas.h>
#include <vector>

class IElement;

struct RenderPosition {
    float x;
    float y;
};

struct RenderSize {
    int width;
    int height;
};

struct Boundaries {
    RenderSize min;
    RenderSize max;
};

struct RenderChild {
    RenderPosition position;
    RenderSize size;
    IElement* element;
};

class IElementRenderer {
public:
    virtual RenderSize getSize(Boundaries boundaries) = 0;

    virtual void paintBackground(RenderSize size, SkCanvas *canvas) = 0;

    virtual std::vector <RenderChild> getChildren(RenderSize size) = 0;
};

class IElement {
public:
    virtual IElementRenderer* render() = 0;
};

#endif //ELEMENTOR_IELEMENT_H
