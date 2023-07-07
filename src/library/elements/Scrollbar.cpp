//
// Created by noartem on 26.05.2022.
//

#include "Scrollbar.h"
#include "Clickable.h"
#include "Draggable.h"

namespace elementor::elements {
    std::shared_ptr<Scrollbar> scrollbar() {
        return std::make_shared<Scrollbar>();
    }

    std::shared_ptr<Scrollbar> Scrollbar::setTrackX(std::shared_ptr<Element> trackX) {
        this->trackX = clickable()
            ->setChild(trackX)
            ->onClick([this] (const std::shared_ptr<EventMouseButton>& event, Position position) {
                float positionX = (position.x / this->child->getWidth()) * this->child->getScrollWidth();
                this->child->setScrollLeft(positionX - (this->child->getWidth() / 2));
                return EventCallbackResponse::StopPropagation;
            });
        return shared_from_this();
    }

    std::shared_ptr<Scrollbar> Scrollbar::setTrackY(std::shared_ptr<Element> trackY) {
        this->trackY = clickable()
            ->setChild(trackY)
            ->onClick([this] (const std::shared_ptr<EventMouseButton>& event, Position position) {
                float positionY = (position.y / this->child->getHeight()) * this->child->getScrollHeight();
                this->child->setScrollTop(positionY - (this->child->getHeight() / 2));
                return EventCallbackResponse::StopPropagation;
            });
        return shared_from_this();
    }

    std::shared_ptr<Scrollbar> Scrollbar::setThumbX(std::shared_ptr<Element> thumbX) {
        this->thumbX = draggable()
            ->setChild(thumbX)
            ->onMove([this] (Position position, Position absolutePosition, Position diff) {
                this->child->setScrollLeft(this->child->getScrollLeft() + diff.x * (this->child->getScrollWidth() / this->child->getWidth()));
            });
        return shared_from_this();
    }

    std::shared_ptr<Scrollbar> Scrollbar::setThumbY(std::shared_ptr<Element> thumbY) {
        this->thumbY = draggable()
            ->setChild(thumbY)
            ->onMove([this] (Position position, Position absolutePosition, Position diff) {
                this->child->setScrollTop(this->child->getScrollTop() + diff.y * (this->child->getScrollHeight() / this->child->getHeight()));
            });
        return shared_from_this();
    }

    std::shared_ptr<Scrollbar> Scrollbar::setPosition(ScrollbarPosition position) {
        this->position = position;
        return shared_from_this();
    }

    ScrollbarPosition Scrollbar::getPosition() {
        return this->position;
    }

    std::shared_ptr<Scrollbar> Scrollbar::setVisible(ScrollbarVisible visible) {
        this->visible = visible;
        return shared_from_this();
    }

    ScrollbarVisible Scrollbar::getVisible() {
        return this->visible;
    }

    std::shared_ptr<Scrollbar> Scrollbar::setChild(std::shared_ptr<Scrollable> child) {
        this->child = child;
        return shared_from_this();
    }

    std::shared_ptr<Scrollable> Scrollbar::getChild() {
        return this->child;
    }

    Size Scrollbar::getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, Boundaries boundaries) {
        return this->child->getSize(ctx, window, boundaries);
    }

    std::vector <RenderElement> Scrollbar::getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) {
        std::vector <RenderElement> children;

        if (this->child) {
            RenderElement childElement{};
            childElement.element = this->child;
            childElement.position = {0, 0};
            Size childSize = this->child->getSize(ctx, window, {rect.size, rect.size});

            float scrollWidth = this->child->getScrollWidth();
            float scrollHeight = this->child->getScrollHeight();
            float scrollTop = this->child->getScrollTop();
            float scrollLeft = this->child->getScrollLeft();

            float childHeight = childSize.height;
            float childWidth = childSize.width;

            if (this->child->isHorizontalScroll() && (this->visible == ScrollbarVisible::Always || scrollWidth > rect.size.width)) {
                float trackHeight = 0;

                if (this->trackX) {
                    RenderElement track;
                    track.element = this->trackX;
                    track.size = track.element->getSize(ctx, window, {{rect.size.width, 0}, rect.size});

                    trackHeight = track.size.height;
                    childHeight -= trackHeight;
                    track.position = {0, childHeight};

                    children.push_back(track);
                }

                if (this->thumbX && scrollWidth > rect.size.width) {
                    RenderElement thumb;
                    thumb.element = this->thumbX;

                    float thumbWidth = std::max(rect.size.width * (rect.size.width / scrollWidth), 64.f);
                    if (trackHeight == 0) {
                        thumb.size = thumb.element->getSize(ctx, window, {{thumbWidth, 0}, {thumbWidth, rect.size.height}});
                        trackHeight = thumb.size.height;
                        childHeight -= trackHeight;
                    } else {
                        thumb.size = {thumbWidth, trackHeight};
                    }

                    thumb.position = {std::min(scrollLeft * (rect.size.width / scrollWidth), childWidth - thumb.size.width), childHeight};

                    children.push_back(thumb);
                }
            }

            if (this->child->isVerticalScroll() && (this->visible == ScrollbarVisible::Always || scrollHeight > rect.size.height)) {
                float trackWidth = 0;

                if (this->trackY) {
                    RenderElement trackElement{};
                    trackElement.element = this->trackY;
                    trackElement.size = trackElement.element->getSize(ctx, window, {{0, rect.size.height}, rect.size});

                    trackWidth = trackElement.size.width;
                    childWidth -= trackWidth;
                    trackElement.position = {childWidth, 0};

                    children.push_back(trackElement);
                }

                if (this->thumbY && scrollHeight > rect.size.height) {
                    RenderElement thumbElement{};
                    thumbElement.element = this->thumbY;

                    float thumbHeight = std::max(rect.size.height * (rect.size.height / scrollHeight), 64.f);
                    if (trackWidth == 0) {
                        thumbElement.size = thumbElement.element->getSize(ctx, window, {{0, thumbHeight}, {rect.size.width, thumbHeight}});
                        trackWidth = thumbElement.size.width;
                        childWidth -= trackWidth;
                    } else {
                        thumbElement.size = {trackWidth, thumbHeight};
                    }

                    thumbElement.position = {childWidth, std::min(scrollTop * (rect.size.height / scrollHeight), childHeight - thumbElement.size.height)};

                    children.push_back(thumbElement);
                }
            }

            if (this->position == ScrollbarPosition::InContent) {
                childElement.size = {childWidth, childHeight};
            } else {
                childElement.size = childSize;
            }

            children.insert(children.begin(), childElement);
        }

        return children;
    }
}
