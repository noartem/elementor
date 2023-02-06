//
// Created by noartem on 04.02.2023.
//

#include "Tooltip.h"
#include "ComponentsContext.h"

namespace elementor::components {
    Tooltip *tooltip() {
        return new Tooltip();
    }

    Tooltip *Tooltip::setActive(bool newActive) {
        this->active = newActive;

        if (!newActive) {
            this->removeTipFromStack();
        }

        return shared_from_this();
    }

    Tooltip *Tooltip::toggleActive() {
        return this->setActive(!this->active);
    }

    bool Tooltip::getActive() const {
        return this->active;
    }

    Tooltip *Tooltip::setPlacement(TooltipPlacement newPlacement) {
        this->placement = newPlacement;
        return shared_from_this();
    }

    TooltipPlacement Tooltip::getPlacement() const {
        return this->placement;
    }

    Tooltip *Tooltip::setChild(std::shared_ptr<Element> newChild) {
        this->child = newChild;
        return shared_from_this();
    }

    std::shared_ptr<Element> Tooltip::getChild() const {
        return this->child;
    }

    Tooltip *Tooltip::setTip(std::shared_ptr<Element> newTip) {
        this->tip = newTip;
        this->tipWrapper->updateChild(this->tip);
        return shared_from_this();
    }

    std::shared_ptr<Element> Tooltip::getTip() {
        return this->tip;
    }

    Size Tooltip::getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, Boundaries boundaries) {
        return this->child->getSize(ctx, window, boundaries);
    }

    std::shared_ptr<Stack> Tooltip::getStackElement() {
        auto componentsContext = static_cast<ComponentsConstd::shared_ptr<Text>>(window->getUserPointer());
        return componentsContext->getStackElement();
    }

    void Tooltip::addTipToStack() {
        if (this->window == nullptr) {
            return;
        }

        auto stackElement = this->getStackElement();
        int tipPaddingIndex = stackElement->childIndex(this->tipWrapper);
        if (tipPaddingIndex == -1) {
            stackElement->appendChild(this->tipWrapper);
        }
    }

    void Tooltip::removeTipFromStack() {
        if (this->window == nullptr) {
            return;
        }

        auto stackElement = this->getStackElement();
        stackElement->removeChild(this->tipWrapper);
        this->tipWrapper = new TipWrapper();
        this->tipWrapper->updateChild(this->tip);
    }

    std::vector<RenderElement> Tooltip::getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) {
        this->window = window;

        std::vector<RenderElement> children;
        children.push_back({this->child, {0, 0}, rect.size});

        if (this->active) {
            this->addTipToStack();

            auto tipSize = this->tip->getSize(ctx, window, {{0, 0},
                                                            {INFINITY, INFINITY}});

            float tipX = 0;
            if (this->placement == TooltipPlacement::TopStart || this->placement == TooltipPlacement::BottomStart) {
                tipX = rect.position.x;
            } else if (this->placement == TooltipPlacement::Top || this->placement == TooltipPlacement::Bottom) {
                tipX = rect.position.x + rect.size.width / 2 - tipSize.width / 2;
            } else if (this->placement == TooltipPlacement::TopEnd || this->placement == TooltipPlacement::BottomEnd) {
                tipX = rect.position.x + rect.size.width - tipSize.width;
            } else if (this->placement == TooltipPlacement::LeftStart || this->placement == TooltipPlacement::Left ||
                       this->placement == TooltipPlacement::LeftEnd) {
                tipX = rect.position.x - tipSize.width;
            } else if (this->placement == TooltipPlacement::RightStart || this->placement == TooltipPlacement::Right ||
                       this->placement == TooltipPlacement::RightEnd) {
                tipX = rect.position.x + rect.size.width;
            }

            float tipY = 0;
            if (this->placement == TooltipPlacement::LeftStart || this->placement == TooltipPlacement::RightStart) {
                tipY = rect.position.y;
            } else if (this->placement == TooltipPlacement::Left || this->placement == TooltipPlacement::Right) {
                tipY = rect.position.y + rect.size.height / 2 - tipSize.height / 2;
            } else if (this->placement == TooltipPlacement::LeftEnd || this->placement == TooltipPlacement::RightEnd) {
                tipY = rect.position.y + rect.size.height - tipSize.height;
            } else if (this->placement == TooltipPlacement::TopStart || this->placement == TooltipPlacement::Top ||
                       this->placement == TooltipPlacement::TopEnd) {
                tipY = rect.position.y - tipSize.height;
            } else if (this->placement == TooltipPlacement::BottomStart ||
                       this->placement == TooltipPlacement::Bottom || this->placement == TooltipPlacement::BottomEnd) {
                tipY = rect.position.y + rect.size.height;
            }

            this->tipWrapper->left = tipX;
            this->tipWrapper->top = tipY;
        } else {
            this->removeTipFromStack();
        }

        return children;
    }

    std::vector<RenderElement> TipWrapper::getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) {
        std::vector<RenderElement> children;

        if (this->hasChild()) {
            RenderElement childElement{};
            childElement.element = this->getChild();
            childElement.position = {this->left, this->top};
            childElement.size = this->getChild()->getSize(ctx, window, {{0, 0},
                                                                        {INFINITY, INFINITY}});
            children.push_back(childElement);

            this->childPosition = childElement.position;
            this->childSize = childElement.size;
        }

        return children;
    }

    EventCallbackResponse TipWrapper::onEvent(std::shared_ptr<EventMouseMove> event) {
        if (event->x > this->childPosition.x && event->x < this->childPosition.x + this->childSize.width &&
            event->y > this->childPosition.y && event->y < this->childPosition.y + this->childSize.height) {
            return EventCallbackResponse::StopPropagation;
        } else {
            return EventCallbackResponse::None;
        }
    }
}