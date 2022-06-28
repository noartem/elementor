//
// Created by noartem on 28.06.2022.
//

#ifndef ELEMENTOR_INPUTABLE_H
#define ELEMENTOR_INPUTABLE_H

#include "../Element.h"
#include "../Event.h"

#include <functional>

namespace elementor::elements {
    class Inputable : public Element, public WithOnKeyboard, public WithOnMouseButton, public WithOnMouseMove, WithChild {
    public:
        Inputable *onChange(std::function<void (std::string text)> callback);

        Inputable *onChange(std::function<std::string (std::string text)> callback);

        Inputable *onFocus(std::function<void ()> callback);

        Inputable *onBlur(std::function<void ()> callback);

        Inputable *setText(std::string text);

        std::string getText();

        Inputable *setChild(Element *child);

        Size getSize(ApplicationContext *ctx, Boundaries boundaries) override;

        void paintBackground(ApplicationContext *ctx, SkCanvas *canvas, ElementRect rect) override;

        std::vector <RenderElement> getChildren(ApplicationContext *ctx, Size size) override;

        EventCallbackResponse onEvent(EventMouseMove *event) override;

        EventCallbackResponse onEvent(EventMouseButton *event) override;

        EventCallbackResponse onEvent(EventKeyboard *event) override;

    private:
        std::string text;
        ElementRect rect;
        bool hovered;
        bool focused;
        std::function<std::string (std::string text)> callbackChange;
        std::function<void ()> callbackFocus;
        std::function<void ()> callbackBlur;
    };

    Inputable *inputable();
}


#endif //ELEMENTOR_INPUTABLE_H
