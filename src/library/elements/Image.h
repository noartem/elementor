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
        Image *fromPath(std::string path);

        Image *fromSkData(sk_sp<SkData> data);

        Image *fromSkImage(sk_sp<SkImage> image);

        void paintBackground(ApplicationContext *ctx, SkCanvas *canvas, ElementRect rect) override;

        Size getSize(ApplicationContext *ctx, Boundaries boundaries) override;

    private:
        sk_sp<SkImage> skImage;

        sk_sp<SkImage> makeImageFromFile(std::string path);
    };

    Image *image();
}


#endif //ELEMENTOR_IMAGE_H
