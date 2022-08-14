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
    class Image : public Element {
    public:
        Image *fromSkImage(sk_sp<SkImage> image);

        sk_sp<SkImage> getSkImage();

        Image *fromSkData(sk_sp<SkData> data);

        Image *fromPath(std::string path);

        Image *setSamplingOptions(SkSamplingOptions samplingOptions);

        SkSamplingOptions getSamplingOptions();

        void paintBackground(ApplicationContext *ctx, Window *window, SkCanvas *canvas, ElementRect rect) override;

        Size getSize(ApplicationContext *ctx, Window *window, Boundaries boundaries) override;

    private:
        sk_sp<SkImage> skImage;
        SkSamplingOptions samplingOptions = SkSamplingOptions(SkCubicResampler::Mitchell());

        sk_sp<SkImage> makeImageFromFile(std::string path);
    };

    Image *image();
}


#endif //ELEMENTOR_IMAGE_H
