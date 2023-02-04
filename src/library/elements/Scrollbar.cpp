//
// Created by noartem on 26.05.2022.
//

#include "Scrollbar.h"
#include "Clickable.h"
#include "Draggable.h"

namespace elementor::elements {
    Scrollbar *scrollbar() {
        return new Scrollbar();
    }

    Scrollbar *Scrollbar::setTrackX(Element *trackX) {
        this->trackX = clickable()
            ->setChild(trackX)
            ->onClick([this] (elementor::EventMouseButton *event, elementor::Position position) {
                float positionX = (position.x / this->child->getWidth()) * this->child->getScrollWidth();
                this->child->setScrollLeft(positionX - (this->child->getWidth() / 2));
                return EventCallbackResponse::StopPropagation;
            });
        return this;
    }

    Scrollbar *Scrollbar::setTrackY(Element *trackY) {
        this->trackY = clickable()
            ->setChild(trackY)
            ->onClick([this] (elementor::EventMouseButton *event, elementor::Position position) {
                float positionY = (position.y / this->child->getHeight()) * this->child->getScrollHeight();
                this->child->setScrollTop(positionY - (this->child->getHeight() / 2));
                return EventCallbackResponse::StopPropagation;
            });
        return this;
    }

    Scrollbar *Scrollbar::setThumbX(Element *thumbX) {
        this->thumbX = draggable()
            ->setChild(thumbX)
            ->onMove([this] (Position position, Position absolutePosition, Position diff) {
                this->child->setScrollLeft(this->child->getScrollLeft() + diff.x * (this->child->getScrollWidth() / this->child->getWidth()));
            });
        return this;
    }

    Scrollbar *Scrollbar::setThumbY(Element *thumbY) {
        this->thumbY = draggable()
            ->setChild(thumbY)
            ->onMove([this] (Position position, Position absolutePosition, Position diff) {
                this->child->setScrollTop(this->child->getScrollTop() + diff.y * (this->child->getScrollHeight() / this->child->getHeight()));
            });
        return this;
    }

    Scrollbar *Scrollbar::setPosition(ScrollbarPosition position) {
        this->position = position;
        return this;
    }

    ScrollbarPosition Scrollbar::getPosition() {
        return this->position;
    }

    Scrollbar *Scrollbar::setVisible(ScrollbarVisible visible) {
        this->visible = visible;
        return this;
    }

    ScrollbarVisible Scrollbar::getVisible() {
        return this->visible;
    }

    Scrollbar *Scrollbar::setChild(Scrollable *child) {
        this->child = child;
        return this;
    }

    Scrollable *Scrollbar::getChild() {
        return this->child;
    }

    void Scrollbar::scrollToX(int x) {
        float position = (x / this->child->getWidth()) * this->child->getScrollWidth();
        this->child->setScrollLeft(position - (this->child->getWidth() / 2));
    }

    void Scrollbar::scrollToY(int y) {
        float position = (y / this->child->getHeight()) * this->child->getScrollHeight();
        this->child->setScrollTop(position - (this->child->getHeight() / 2));
    }

    Size Scrollbar::getSize(ApplicationContext *ctx, Window *window, Boundaries boundaries) {
        return this->child->getSize(ctx, window, boundaries);
    }

    std::vector <RenderElement> Scrollbar::getChildren(ApplicationContext *ctx, Window *window, ElementRect rect) {
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

                    float thumbWidth = rect.size.width * (rect.size.width / scrollWidth);
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

                    float thumbHeight = rect.size.height * (rect.size.height / scrollHeight);
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
