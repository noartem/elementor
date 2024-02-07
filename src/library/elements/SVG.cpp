//
// Created by noartem on 30.07.2022.
//

#include "SVG.h"

#include <include/core/SkSurface.h>
#include <include/core/SkSamplingOptions.h>
#include <modules/svg/include/SkSVGSVG.h>
#include <modules/svg/include/SkSVGTypes.h>
#include <modules/svg/include/SkSVGRenderContext.h>

#include <utility>

namespace elementor::elements {
	void SVG::fromSkStream(SkStream& stream) {
		markChanged();
		fromSkSVGDOM(SkSVGDOM::MakeFromStream(stream));
	}

	void SVG::fromSkData(sk_sp <SkData> data) {
		SkMemoryStream dataStream(std::move(data));
		return fromSkStream(dataStream);
	}

	void SVG::fromPath(const std::string& path) {
		return fromSkData(SkData::MakeFromFileName(path.c_str()));
	}

	void SVG::fromString(const char value[]) {
		return fromSkData(SkData::MakeWithCString(value));
	}

	void SVG::paintBackground(SkCanvas* canvas, const ElementRect& rect) {
		if (skSVGDOM == nullptr) {
			return;
		}

		if (skImage == nullptr
			|| (abs(skImage->width() - rect.size.width) > 5)
			|| (abs(skImage->height() - rect.size.height) > 5)) {
			SkSVGSVG* root = skSVGDOM->getRoot();
			root->setWidth(SkSVGLength(rect.size.width, SkSVGLength::Unit::kNumber));
			root->setHeight(SkSVGLength(rect.size.height, SkSVGLength::Unit::kNumber));

			// TODO: Cache can be based on something like this
			sk_sp <SkSurface> svgSurface = SkSurface::MakeRasterN32Premul(rect.size.width, rect.size.height);
			if (svgSurface == nullptr) {
				skSVGDOM->render(canvas);
				return;
			}

			SkCanvas* svgCanvas = svgSurface->getCanvas();
			skSVGDOM->render(svgCanvas);
			skImage = svgSurface->makeImageSnapshot();
		}

		SkRect skRect = SkRect::MakeXYWH(0, 0, rect.size.width, rect.size.height);
		canvas->drawImageRect(skImage, skRect, SkSamplingOptions(SkCubicResampler::Mitchell()));
	}
}