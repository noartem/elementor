//
// Created by noartem on 26.07.2022.
//

#include "Image.h"

#include <utility>

namespace elementor::elements {
    std::shared_ptr<Image> image() {
        return std::make_shared<Image>();
    }

    std::shared_ptr<Image> Image::fromSkImage(sk_sp<SkImage> image) {
        this->skImage = std::move(image);
        return shared_from_this();
    }

    sk_sp<SkImage> Image::getSkImage() {
        return this->skImage;
    }

    sk_sp<SkImage> Image::makeImageFromFile(const std::string& path) {
        sk_sp<SkData> encodedData = SkData::MakeFromFileName(path.c_str());
        return SkImage::MakeFromEncoded(encodedData);
    }

    std::shared_ptr<Image> Image::fromPath(const std::string& path) {
        return this->fromSkImage(this->makeImageFromFile(path));
    }

    std::shared_ptr<Image> Image::fromSkData(sk_sp<SkData> data) {
        return this->fromSkImage(SkImage::MakeFromEncoded(std::move(data)));
    }

    std::shared_ptr<Image> Image::setSamplingOptions(SkSamplingOptions newOptions) {
        this->samplingOptions = newOptions;
        return shared_from_this();
    }

    SkSamplingOptions Image::getSamplingOptions() {
        return this->samplingOptions;
    }

    void Image::paintBackground(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, SkCanvas *canvas, ElementRect rect) {
        SkRect skRect = SkRect::MakeXYWH(0, 0, rect.size.width, rect.size.height);
        canvas->drawImageRect(this->skImage, skRect, this->samplingOptions);
    }

    Size Image::getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, Boundaries boundaries) {
        float imageWidth = this->skImage->width();
        float imageHeight = this->skImage->height();
        return fitSizeInBoundaries({imageWidth * ctx->getPixelScale(), imageHeight * ctx->getPixelScale()}, boundaries);
    }
}