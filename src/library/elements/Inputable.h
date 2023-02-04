//
// Created by noartem on 28.06.2022.
//

#ifndef ELEMENTOR_INPUTABLE_H
#define ELEMENTOR_INPUTABLE_H

#include "../Element.h"
#include "../Event.h"

#include <functional>

namespace elementor::elements {
    class Inputable : public Element, public WithOnKeyboard, public WithOnChar, public WithOnMouseButton, public WithOnMouseMove, public WithChild {
    public:
        Inputable *onChange(std::function<std::u32string (std::u32string text)> callback);

        Inputable *onFocus(std::function<void ()> callback);

        Inputable *onBlur(std::function<void ()> callback);

        Inputable *setText(std::u32string text);

        Inputable *setText(std::string text);

        std::u32string getText();

        Inputable *setChild(Element *child);

        Size getSize(ApplicationContext *ctx, Window *window, Boundaries boundaries) override;

        void paintBackground(ApplicationContext *ctx, Window *window, SkCanvas *canvas, ElementRect rect) override;

        std::vector <RenderElement> getChildren(ApplicationContext *ctx, Window *window, ElementRect rect) override;

        EventCallbackResponse onEvent(EventMouseMove *event) override;

        EventCallbackResponse onEvent(EventMouseButton *event) override;

        EventCallbackResponse onEvent(EventKeyboard *event) override;

        EventCallbackResponse onEvent(EventChar *event) override;

    private:
        ApplicationContext *ctx;
        std::u32string text;
        ElementRect rect;
        bool hovered;
        bool focused;
        std::function<std::u32string (std::u32string text)> callbackChange;
        std::function<void ()> callbackFocus;
        std::function<void ()> callbackBlur;
    };

    Inputable *inputable();
}


#endif //ELEMENTOR_INPUTABLE_H
