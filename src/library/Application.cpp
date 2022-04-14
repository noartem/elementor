//
// Created by noartem on 13.04.2022.
//

#include "Application.h"

namespace elementor {
    void Application::draw(SkCanvas *canvas) {
        SkPaint paint;
        paint.setColor(SK_ColorWHITE);
        canvas->drawPaint(paint);

        paint.setColor(SK_ColorBLUE);
        canvas->drawRect({100, 200, 300, 500}, paint);

        paint.setColor(SK_ColorRED);
        canvas->drawRect({200, 200, 600, 500}, paint);
    }
}
