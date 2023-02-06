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
    class SVG : public Element, public std::enable_shared_from_this<SVG> {
    public:
        sk_sp<SkSVGDOM> getSkSVGDOM();

        std::shared_ptr<SVG> fromSkSVGDOM(sk_sp<SkSVGDOM> newSkSVGDOM);

        std::shared_ptr<SVG> fromSkStream(SkStream& stream);

        std::shared_ptr<SVG> fromSkData(sk_sp<SkData> data);

        std::shared_ptr<SVG> fromPath(const std::string& path);

        std::shared_ptr<SVG> fromString(const char value[]);

        void paintBackground(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, SkCanvas *canvas, ElementRect rect) override;

    private:
        sk_sp<SkSVGDOM> skSVGDOM;
        sk_sp<SkImage> skImage;
    };

    std::shared_ptr<SVG> svg();
}


#endif //ELEMENTOR_SVG_H
