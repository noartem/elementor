//
// Created by noartem on 26.07.2022.
//

#include "Image.h"

#include <utility>

namespace elementor::elements {
	sk_sp<SkImage> Image::makeImageFromFile(const std::string& path) {
		sk_sp<SkData> encodedData = SkData::MakeFromFileName(path.c_str());
		return SkImage::MakeFromEncoded(encodedData);
	}

	void Image::paintBackground(SkCanvas* canvas, const ElementRect& rect) {
		if (skImage == nullptr) {
			return;
		}

		SkRect skRect = SkRect::MakeXYWH(0, 0, rect.size.width, rect.size.height);
		canvas->drawImageRect(skImage, skRect, samplingOptions);
	}

	Size Image::getSize(const Boundaries& boundaries) {
		if (skImage == nullptr) {
			return boundaries.min;
		}

		float pixelScale = ctx->getWindowCtx()->getPixelScale();
		float imageWidthScaled = skImage->width() * pixelScale;
		float imageHeightScaled = skImage->height() * pixelScale;

		Size size = { imageWidthScaled, imageHeightScaled };
		size = fitSizeInBoundaries(size, boundaries);

		return size;
	}
}