//
// Created by noartem on 26.05.2022.
//

#include "Scrollbar.h"
#include "Clickable.h"

namespace elementor::elements {
    Scrollbar *scrollbar() {
        return new Scrollbar();
    }

    Scrollbar *Scrollbar::setScrollTrack(std::function<Element *()> scrollTrack) {
        this->scrollTrack = scrollTrack;
        return this;
    }

    std::function<Element *()>Scrollbar::getScrollTrack() {
        return this->scrollTrack;
    }

    Scrollbar *Scrollbar::setScrollThumb(std::function<Element *()> scrollThumb) {
        this->scrollThumb = scrollThumb;
        return this;
    }

    std::function<Element *()>Scrollbar::getScrollThumb() {
        return this->scrollThumb;
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

    Scrollbar *Scrollbar::setMinThumbSize(float size) {
        this->minThumbSize = size;
        return this;
    }

    float Scrollbar::getMinThumbSize() {
        return this->minThumbSize;
    }

    Scrollbar *Scrollbar::setChild(Scrollable *child) {
        this->child = child;
        return this;
    }

    Scrollbar *Scrollbar::setChild(Element *child) {
        Scrollable *childScrollable = dynamic_cast<Scrollable *>(child);
        if (childScrollable != NULL) {
            this->child = childScrollable;    
        }

        return this;
    }

    void Scrollbar::scrollToX(int x) {
        float position = (x / this->child->getWidth()) * this->child->getScrollWidth();
        this->child->setScrollLeft(position - (this->child->getWidth() / 2));
    }

    void Scrollbar::scrollToY(int y) {
        float position = (y / this->child->getHeight()) * this->child->getScrollHeight();
        this->child->setScrollTop(position - (this->child->getHeight() / 2));
    }

    void Scrollbar::initChild() {
        if (this->scrollTrack && (this->trackX == NULL || this->trackY == NULL)) {
            this->trackX = clickable()
                ->setChild(this->scrollTrack())
                ->onClick([this] (EventMouseButton *event, Position position) {
                    this->scrollToX(position.x);
                    return EventCallbackResponse::StopPropagation;
                });

            this->trackY = clickable()
                ->setChild(this->scrollTrack())
                ->onClick([this] (EventMouseButton *event, Position position) {
                    this->scrollToY(position.y);
                    return EventCallbackResponse::StopPropagation;
                });
        }

        if (this->scrollThumb && (this->thumbX == NULL || this->thumbY == NULL)) {
            this->thumbX = this->scrollThumb();
            this->thumbY = this->scrollThumb();
        }
    }

    Size Scrollbar::getSize(ApplicationContext *ctx, Window *window, Boundaries boundaries) {
        return this->child->getSize(ctx, window, boundaries);
    }

    std::vector <RenderElement> Scrollbar::getChildren(ApplicationContext *ctx, Window *window, Size size) {
        this->ctx = ctx;
        this->initChild();

        std::vector <RenderElement> children;

        if (this->child) {
            RenderElement child;
            child.element = this->child;
            child.position = {0, 0};
            Size childSize = this->child->getSize(ctx, window, {size, size});

            ScrollDirection scrollDirection = this->child->getDirection();

            float scrollWidth = this->child->getScrollWidth();
            float scrollHeight = this->child->getScrollHeight();
            float scrollTop = this->child->getScrollTop();
            float scrollLeft = this->child->getScrollLeft();

            float childHeight = childSize.height;
            if (this->child->isHorizontalScroll() && (this->visible == ScrollbarVisible::Always || scrollWidth > size.width)) {
                float trackWidth = 0;
                float trackHeight = 0;

                if (this->trackX) {
                    RenderElement track;
                    track.element = this->trackX;
                    track.size = track.element->getSize(ctx, window, {{size.width, 0}, size});

                    trackWidth = track.size.width;
                    trackHeight = track.size.height;
                    childHeight -= trackHeight;
                    track.position = {0, childHeight};

                    children.push_back(track);
                }

                if (this->thumbX && scrollWidth > size.width) {
                    RenderElement thumb;
                    thumb.element = this->thumbX;

                    float thumbWidth = std::min(size.width * (size.width / scrollWidth), this->minThumbSize);
                    if (trackHeight == 0) {
                        thumb.size = thumb.element->getSize(ctx, window, {{thumbWidth, 0}, {thumbWidth, size.height}});
                        trackHeight = thumb.size.height;
                        childHeight -= trackHeight;
                    } else {
                        thumb.size = {thumbWidth, trackHeight};
                    }

                    thumb.position = {std::min(scrollLeft * (size.width / scrollWidth), trackWidth - thumb.size.width), childHeight};

                    children.push_back(thumb);
                }
            }

            float childWidth = childSize.width;
            if (this->child->isVerticalScroll() && (this->visible == ScrollbarVisible::Always || scrollHeight > size.height)) {
                float trackWidth = 0;
                float trackHeight = 0;

                if (this->trackY) {
                    RenderElement track;
                    track.element = this->trackY;
                    track.size = track.element->getSize(ctx, window, {{0, size.height}, size});

                    trackWidth = track.size.width;
                    trackHeight = track.size.height;
                    childWidth -= trackWidth;
                    track.position = {childWidth, 0};

                    children.push_back(track);
                }

                if (this->thumbY && scrollHeight > size.height) {
                    RenderElement thumb;
                    thumb.element = this->thumbY;

                    float thumbHeight = std::max(size.height * (size.height / scrollHeight), this->minThumbSize);
                    if (trackWidth == 0) {
                        thumb.size = thumb.element->getSize(ctx, window, {{0, thumbHeight}, {size.width, thumbHeight}});
                        trackWidth = thumb.size.width;
                        childWidth -= trackWidth;
                    } else {
                        thumb.size = {trackWidth, thumbHeight};
                    }

                    thumb.position = {childWidth, std::min(scrollTop * (size.height / scrollHeight), trackHeight - thumb.size.height)};

                    children.push_back(thumb);
                }
            }

            if (this->position == ScrollbarPosition::InContent) {
                child.size = {childWidth, childHeight};
            } else {
                child.size = childSize;
            }

            children.insert(children.begin(), child);
        }

        return children;
    }
}
