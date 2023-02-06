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
#include <utility>

namespace elementor::elements {
    std::shared_ptr<SVG> svg() {
        return std::make_shared<SVG>();
    }

    sk_sp<SkSVGDOM> SVG::getSkSVGDOM() {
        return this->skSVGDOM;
    }

    std::shared_ptr<SVG> SVG::fromSkSVGDOM(sk_sp<SkSVGDOM> newSkSVGDOM) {
        this->skSVGDOM = std::move(newSkSVGDOM);
        return shared_from_this();
    }

    std::shared_ptr<SVG> SVG::fromSkStream(SkStream &stream) {
        this->skSVGDOM = SkSVGDOM::MakeFromStream(stream);
        return shared_from_this();
    }

    std::shared_ptr<SVG> SVG::fromSkData(sk_sp<SkData> data) {
        SkMemoryStream dataStream(std::move(data));
        return this->fromSkStream(dataStream);
    }

    std::shared_ptr<SVG> SVG::fromPath(const std::string &path) {
        return this->fromSkData(SkData::MakeFromFileName(path.c_str()));
    }

    std::shared_ptr<SVG> SVG::fromString(const char value[]) {
        return this->fromSkData(SkData::MakeWithCString(value));
    }

    void SVG::paintBackground(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, SkCanvas *canvas, ElementRect rect) {
        if (this->skImage == nullptr || (abs(this->skImage->width() - rect.size.width) > 5) ||
            (abs(this->skImage->height() - rect.size.height) > 5)) {
            SkSVGSVG *root = this->skSVGDOM->getRoot();
            root->setWidth(SkSVGLength(rect.size.width, SkSVGLength::Unit::kNumber));
            root->setHeight(SkSVGLength(rect.size.height, SkSVGLength::Unit::kNumber));

            sk_sp<SkSurface> svgSurface = SkSurface::MakeRasterN32Premul(rect.size.width, rect.size.height);
            if (svgSurface == nullptr) {
                this->skSVGDOM->render(canvas);
                return;
            }

            SkCanvas *svgCanvas = svgSurface->getCanvas();
            this->skSVGDOM->render(svgCanvas);
            this->skImage = svgSurface->makeImageSnapshot();
        }

        SkRect skRect = SkRect::MakeXYWH(0, 0, rect.size.width, rect.size.height);
        canvas->drawImageRect(this->skImage, skRect, SkSamplingOptions(SkCubicResampler::Mitchell()));
    }
}