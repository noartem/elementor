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
        float position = ((x / this->ctx->monitorPixelScale) / this->child->getWidth()) * this->child->getScrollWidth();
        this->child->setScrollLeft(position - (this->child->getWidth() / 2));
    }

    void Scrollbar::scrollToY(int y) {
        float position = ((y / this->ctx->monitorPixelScale) / this->child->getHeight()) * this->child->getScrollHeight();
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

    Size Scrollbar::getSize(ApplicationContext *ctx, Boundaries boundaries) {
        return this->child->getSize(ctx, boundaries);
    }

    std::vector <RenderElement> Scrollbar::getChildren(ApplicationContext *ctx, Size size) {
        this->ctx = ctx;
        this->initChild();

        std::vector <RenderElement> children;

        if (this->child) {
            RenderElement child;
            child.element = this->child;
            child.position = {0, 0};
            Size childSize = this->child->getSize(ctx, {size, size});

            ScrollDirection scrollDirection = this->child->getDirection();

            float scrollWidth = this->child->getScrollWidth() * ctx->monitorPixelScale;
            float scrollHeight = this->child->getScrollHeight() * ctx->monitorPixelScale;
            float scrollTop = this->child->getScrollTop() * ctx->monitorPixelScale;
            float scrollLeft = this->child->getScrollLeft() * ctx->monitorPixelScale;

            float childHeight = childSize.height;
            if (this->child->isHorizontalScroll() && (this->visible == ScrollbarVisible::Always || scrollWidth > size.width)) {
                float trackHeight = 0;

                if (this->trackX) {
                    RenderElement track;
                    track.element = this->trackX;
                    track.size = track.element->getSize(ctx, {{size.width, 0}, size});

                    trackHeight = track.size.height;
                    childHeight -= trackHeight;
                    track.position = {0, childHeight};

                    children.push_back(track);
                }

                if (this->thumbX && scrollWidth > size.width) {
                    RenderElement thumb;
                    thumb.element = this->thumbX;

                    float thumbWidth = size.width * (size.width / scrollWidth);
                    if (trackHeight == 0) {
                        thumb.size = thumb.element->getSize(ctx, {{thumbWidth, 0}, {thumbWidth, size.height}});
                        trackHeight = thumb.size.height;
                        childHeight -= trackHeight;
                    } else {
                        thumb.size = thumb.element->getSize(ctx, {{thumbWidth, 0}, {thumbWidth, trackHeight}});
                    }

                    thumb.position = {scrollLeft * (size.width / scrollWidth), childHeight};

                    children.push_back(thumb);
                }
            }

            float childWidth = childSize.width;
            if (this->child->isVerticalScroll() && (this->visible == ScrollbarVisible::Always || scrollHeight > size.height)) {
                float trackWidth = 0;

                if (this->trackY) {
                    RenderElement track;
                    track.element = this->trackY;
                    track.size = track.element->getSize(ctx, {{0, size.height}, size});

                    trackWidth = track.size.width;
                    childWidth -= trackWidth;
                    track.position = {childWidth, 0};

                    children.push_back(track);
                }

                if (this->thumbY && scrollHeight > size.height) {
                    RenderElement thumb;
                    thumb.element = this->thumbY;

                    float thumbHeight = size.height * (size.height / scrollHeight);
                    if (trackWidth == 0) {
                        thumb.size = thumb.element->getSize(ctx, {{0, thumbHeight}, {size.width, thumbHeight}});
                        trackWidth = thumb.size.width;
                        childWidth -= trackWidth;
                    } else {
                        thumb.size = thumb.element->getSize(ctx, {{0, thumbHeight}, {trackWidth, thumbHeight}});
                    }

                    thumb.position = {childWidth, scrollTop * (size.height / scrollHeight)};

                    children.push_back(thumb);
                }
            }

            if (this->position == ScrollbarPosition::InContent) {
                child.size = {childWidth, childHeight};
            } else {
                child.size = childSize;
            }

            children.push_back(child);
        }

        return children;
    }
}
