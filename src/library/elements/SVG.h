//
// Created by noartem on 30.07.2022.
//

#ifndef ELEMENTOR_SVG_H
#define ELEMENTOR_SVG_H

#include "../Element.h"

#include <include/core/SkData.h>
#include <include/core/SkStream.h>
#include <modules/svg/include/SkSVGDOM.h>

namespace elementor::elements {
    class SVG : public Element {
    public:
        sk_sp<SkSVGDOM> getSkSVGDOM();

        SVG *fromSkSVGDOM(sk_sp<SkSVGDOM> skSVGDOM);

        SVG *fromSkStream(SkStream& stream);

        SVG *fromSkData(sk_sp<SkData> data);

        SVG *fromPath(std::string path);

        void paintBackground(ApplicationContext *ctx, Window *window, SkCanvas *canvas, ElementRect rect) override;

    private:
        sk_sp<SkSVGDOM> skSVGDOM;
        sk_sp<SkImage> skImage;

        sk_sp<SkImage> renderSVGImage(Size size);
    };

    SVG *svg();
}


#endif //ELEMENTOR_SVG_H
