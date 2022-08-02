//
// Created by noartem on 30.07.2022.
//

#include "SVG.h"

#include <include/core/SkSurface.h>
#include <include/core/SkSize.h>
#include <include/core/SkSamplingOptions.h>
#include <modules/svg/include/SkSVGSVG.h>
#include <modules/svg/include/SkSVGTypes.h>
#include <modules/svg/include/SkSVGRenderContext.h>

#include <iostream>

namespace elementor::elements {
    SVG *svg() {
        return new SVG();
    }

    sk_sp<SkSVGDOM> SVG::getSkSVGDOM() {
        return this->skSVGDOM;
    }

    SVG *SVG::fromSkSVGDOM(sk_sp<SkSVGDOM> skSVGDOM) {
        this->skSVGDOM = skSVGDOM;
        return this;
    }

    SVG *SVG::fromSkStream(SkStream& stream) {
        return this->fromSkSVGDOM(SkSVGDOM::MakeFromStream(stream));
    }

    SVG *SVG::fromSkData(sk_sp<SkData> data) {
        SkMemoryStream dataStream(data);
        return this->fromSkStream(dataStream);
    }

    SVG *SVG::fromPath(std::string path) {
        return this->fromSkData(SkData::MakeFromFileName(path.c_str()));
    }

    sk_sp<SkImage> SVG::renderSVGImage(Size size) {
        sk_sp<SkSurface> surface = SkSurface::MakeRasterN32Premul(size.width, size.height);
        SkCanvas *canvas = surface->getCanvas();
        
        SkSVGSVG* root = this->skSVGDOM->getRoot();
        root->setWidth(SkSVGLength(size.width, SkSVGLength::Unit::kNumber));
        root->setHeight(SkSVGLength(size.height, SkSVGLength::Unit::kNumber));

        this->skSVGDOM->render(canvas);

        return surface->makeImageSnapshot();
    }

    void SVG::paintBackground(ApplicationContext *ctx, SkCanvas *canvas, ElementRect rect) {
        if (this->skImage == NULL || (abs(this->skImage->width() - rect.size.width) > 5) || (abs(this->skImage->height() - rect.size.height) > 5)) {
            this->skImage = this->renderSVGImage(rect.size);
        }

        SkRect skRect = SkRect::MakeXYWH(0, 0, rect.size.width, rect.size.height);
        canvas->drawImageRect(this->skImage, skRect, SkSamplingOptions(SkCubicResampler::Mitchell()));
    }
}