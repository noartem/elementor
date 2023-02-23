//
// Created by noartem on 28.06.2022.
//

#ifndef ELEMENTOR_INPUTABLE_H
#define ELEMENTOR_INPUTABLE_H

#include "../Element.h"
#include "../Event.h"

#include <functional>

namespace elementor::elements {
    class Inputable
            : public Element,
              public WithOnKeyboard,
              public WithOnChar,
              public WithOnMouseButton,
              public WithOnMouseMove,
              public WithChild,
              public std::enable_shared_from_this<Inputable> {
    public:
        std::shared_ptr<Inputable> onChange(const std::function<std::u32string(std::u32string text)> &callback);

        std::shared_ptr<Inputable> onFocus(const std::function<void()> &callback);

        std::shared_ptr<Inputable> onBlur(const std::function<void()> &callback);

        std::shared_ptr<Inputable> setText(const std::u32string& newText);

        std::shared_ptr<Inputable> setText(const std::string& newText);

        std::u32string getText();

        std::shared_ptr<Inputable> setChild(const std::shared_ptr<Element>& child);

        void blur();

        void focus();

        Size getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window,
                     Boundaries boundaries) override;

        void paintBackground(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, SkCanvas *canvas,
                             ElementRect rect) override;

        std::vector<RenderElement>
        getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) override;

        EventCallbackResponse onEvent(std::shared_ptr<EventMouseMove> event) override;

        EventCallbackResponse onEvent(std::shared_ptr<EventMouseButton> event) override;

        EventCallbackResponse onEvent(std::shared_ptr<EventKeyboard> event) override;

        EventCallbackResponse onEvent(std::shared_ptr<EventChar> event) override;

    private:
        std::shared_ptr<ApplicationContext> ctx;
        std::u32string text;
        ElementRect rect;
        bool hovered;
        bool focused;
        std::function<std::u32string(std::u32string text)> callbackChange;
        std::function<void()> callbackFocus;
        std::function<void()> callbackBlur;
    };

    std::shared_ptr<Inputable> inputable();
}


#endif //ELEMENTOR_INPUTABLE_H
