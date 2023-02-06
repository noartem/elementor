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

        std::vector<RenderElement> getChildren(ApplicationContext *ctx, Window *window, ElementRect rect) override;

        EventCallbackResponse onEvent(EventMouseMove *event) override;

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

        Tooltip *setChild(Element *child);

        [[nodiscard]] Element *getChild() const;

        Tooltip *setTip(Element *tip);

        Element *getTip();

        Size getSize(ApplicationContext *ctx, Window *window, Boundaries boundaries) override;

        std::vector<RenderElement> getChildren(ApplicationContext *ctx, Window *window, ElementRect rect) override;

    private:
        Window *window;

        bool active = false;
        TooltipPlacement placement = TooltipPlacement::Bottom;
        Element *child = nullptr;
        Element *tip = nullptr;
        TipWrapper *tipWrapper = new TipWrapper();

        Stack *getStackElement();
        void addTipToStack();
        void removeTipFromStack();
    };

    Tooltip *tooltip();
}

#endif //ELEMENTOR_COMPONENTS_TOOLTIP_H
