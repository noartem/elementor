//
// Created by noartem on 26.07.2022.
//

#include "Image.h"

namespace elementor::elements {
    Image *image() {
        return new Image();
    }

    Image *Image::fromSkImage(sk_sp<SkImage> image) {
        this->skImage = image;
        return this;
    }

    sk_sp<SkImage> Image::makeImageFromFile(std::string path) {
        sk_sp<SkData> encodedData = SkData::MakeFromFileName(path.c_str());
        return SkImage::MakeFromEncoded(encodedData);
    }

    Image *Image::fromPath(std::string path) {
        return this->fromSkImage(this->makeImageFromFile(path));
    }

    Image *Image::fromSkData(sk_sp<SkData> data) {
        return this->fromSkImage(SkImage::MakeFromEncoded(data));
    }

    void Image::paintBackground(ApplicationContext *ctx, SkCanvas *canvas, ElementRect rect) {
        SkRect skRect = SkRect::MakeXYWH(0, 0, rect.size.width, rect.size.height);
        canvas->drawImageRect(this->skImage, skRect, SkSamplingOptions(SkCubicResampler::Mitchell()));
    }

    Size Image::getSize(ApplicationContext *ctx, Boundaries boundaries) {
        return fitSizeInBoundaries({(float) this->skImage->width(), (float) this->skImage->height()}, boundaries);
    }
}