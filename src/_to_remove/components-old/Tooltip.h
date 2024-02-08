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
        Position position;
        Size size;

        std::vector<RenderElement> getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) override;

        EventCallbackResponse onEvent(std::shared_ptr<MouseMoveEvent> event) override;
    };

    class Tooltip : public Element, public std::enable_shared_from_this<Tooltip> {
    public:
        ~Tooltip();

        std::shared_ptr<Tooltip> setActive(bool active);

        std::shared_ptr<Tooltip> toggleActive();

        [[nodiscard]] bool getActive() const;

        std::shared_ptr<Tooltip> setPlacement(TooltipPlacement placement);

        [[nodiscard]] TooltipPlacement getPlacement() const;

        std::shared_ptr<Tooltip> setGap(float gap);

        [[nodiscard]] float getGap() const;

        std::shared_ptr<Tooltip> setChild(const std::shared_ptr<Element>& newChild);

        [[nodiscard]] std::shared_ptr<Element> getChild() const;

        std::shared_ptr<Tooltip> setTip(const std::shared_ptr<Element>& newTip);

        std::shared_ptr<Element> getTip();

        Size getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, Boundaries boundaries) override;

        std::vector<RenderElement> getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) override;

    private:
        std::shared_ptr<Window> window;

        bool active = false;
        TooltipPlacement placement = TooltipPlacement::Bottom;
        float gap = 0;
        std::shared_ptr<Element> child = nullptr;
        std::shared_ptr<Element> tip = nullptr;
        std::shared_ptr<TipWrapper> tipWrapper = std::make_shared<TipWrapper>();

        std::shared_ptr<Stack> getStackElement();
        void addTipToStack();
        void removeTipFromStack();
    };

    std::shared_ptr<Tooltip> tooltip();
}

#endif //ELEMENTOR_COMPONENTS_TOOLTIP_H