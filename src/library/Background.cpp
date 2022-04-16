//
// Created by noartem on 13.04.2022.
//

#include "Background.h"

namespace elementor {
    std::unique_ptr<ElementRenderer> Background::render() {
        auto renderer = std::make_unique<BackgroundRenderer>();
        renderer->color = this->color;
        renderer->child = this->child;
        return renderer;
    }

    void BackgroundRenderer::paintBackground(SkCanvas *canvas, RenderPosition start, RenderSize size) {
        SkPaint paint;
        paint.setColor(this->color);

        SkRect rect = SkRect::MakeXYWH(start.x, start.y, size.width, size.height);
        canvas->drawRect(rect, paint);
    }

    std::vector <RenderChild> BackgroundRenderer::getChildren(RenderSize size) {
        std::vector<RenderChild> children;

        if (this->child) {
            RenderChild renderChild;
            renderChild.element = this->child;
            renderChild.position = {0, 0};
            renderChild.size = size;

            children.push_back(renderChild);
        }

        return children;
    }
}
