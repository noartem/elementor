//
// Created by noartem on 04.02.2023.
//

#ifndef ELEMENTOR_COMPONENTS_TOOLTIP_H
#define ELEMENTOR_COMPONENTS_TOOLTIP_H

#include "utility.h"
#include "elementor.h"

namespace elementor::components {
    enum class TooltipPlacement {
        TopStart,
        Top,
        TopEnd,
        RightStart,
        Right,
        RightEnd,
        BottomEnd,
        Bottom,
        BottomStart,
        LeftEnd,
        Left,
        LeftStart,
    };

    class TipWrapper : public Element, public WithOnMouseMove, public WithChild {
    public:
        float left;

        float top;

        std::vector<RenderElement> getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) override;

        EventCallbackResponse onEvent(std::shared_ptr<EventMouseMove> event) override;

    private:
        Position childPosition;
        Size childSize;
    };

    class Tooltip : public Element {
    public:
        ~Tooltip();

        Tooltip *setActive(bool active);

        Tooltip *toggleActive();

        [[nodiscard]] bool getActive() const;

        Tooltip *setPlacement(TooltipPlacement placement);

        [[nodiscard]] TooltipPlacement getPlacement() const;

        Tooltip *setChild(const std::shared_ptr<Element>& child);

        [[nodiscard]] std::shared_ptr<Element> getChild() const;

        Tooltip *setTip(std::shared_ptr<Element> tip);

        std::shared_ptr<Element> getTip();

        Size getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, Boundaries boundaries) override;

        std::vector<RenderElement> getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) override;

    private:
        Window *window;

        bool active = false;
        TooltipPlacement placement = TooltipPlacement::Bottom;
        std::shared_ptr<Element> child = nullptr;
        std::shared_ptr<Element> tip = nullptr;
        TipWrapper *tipWrapper = new TipWrapper();

        std::shared_ptr<Stack> getStackElement();
        void addTipToStack();
        void removeTipFromStack();
    };

    Tooltip *tooltip();
}

#endif //ELEMENTOR_COMPONENTS_TOOLTIP_H
