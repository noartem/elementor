//
// Created by noartem on 26.07.2022.
//

#ifndef ELEMENTOR_IMAGE_H
#define ELEMENTOR_IMAGE_H

#include "../Element.h"

#include <include/core/SkData.h>
#include <include/core/SkImage.h>
#include <include/core/SkSamplingOptions.h>

namespace elementor::elements {
    class Image : public Element, public std::enable_shared_from_this<Image> {
    public:
        std::shared_ptr<Image> fromSkImage(sk_sp<SkImage> image);

        sk_sp<SkImage> getSkImage();

        std::shared_ptr<Image> fromSkData(sk_sp<SkData> data);

        std::shared_ptr<Image> fromPath(const std::string &path);

        std::shared_ptr<Image> setSamplingOptions(SkSamplingOptions newOptions);

        SkSamplingOptions getSamplingOptions();

        void paintBackground(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, SkCanvas *canvas,
                             ElementRect rect) override;

        Size getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window,
                     Boundaries boundaries) override;

    private:
        sk_sp<SkImage> skImage;
        SkSamplingOptions samplingOptions = SkSamplingOptions(SkCubicResampler::Mitchell());

        sk_sp<SkImage> makeImageFromFile(const std::string &path);
    };

    std::shared_ptr<Image> image();
}


#endif //ELEMENTOR_IMAGE_H
