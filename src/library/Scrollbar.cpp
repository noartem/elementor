//
// Created by noartem on 26.05.2022.
//

#include "Scrollbar.h"

namespace elementor {
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

    Size Scrollbar::getSize(ApplicationContext *ctx, Boundaries boundaries) {
        return this->child->getSize(ctx, boundaries);
    }

    std::vector <RenderElement> Scrollbar::getChildren(ApplicationContext *ctx, Size size) {
        std::vector <RenderElement> children;
        
        if (this->child) {
            int scrollWidth = ceil(this->child->getScrollWidth() * ctx->monitorPixelScale);
            int scrollHeight = ceil(this->child->getScrollHeight() * ctx->monitorPixelScale);
            int scrollTop = ceil(this->child->getScrollTop() * ctx->monitorPixelScale);
            int scrollLeft = ceil(this->child->getScrollLeft() * ctx->monitorPixelScale);

            ScrollDirection scrollDirection = this->child->getDirection();

            int childHeight = size.height;
            if ((scrollDirection == ScrollDirection::Horizontal || scrollDirection == ScrollDirection::Both) && scrollWidth > size.width) {
                int trackHeight = 0;
                if (this->scrollTrack) {
                    RenderElement track;
                    track.element = this->scrollTrack();
                    track.size = track.element->getSize(ctx, {{size.width, 0}, size});
                    trackHeight = track.size.height;
                    childHeight -= trackHeight;
                    track.position = {0, childHeight};
                    children.push_back(track);
                }

                if (this->scrollThumb) {
                    RenderElement thumb;
                    thumb.element = this->scrollThumb();

                    int thumbWidth = (size.width * size.width) / scrollWidth;
                    if (trackHeight == 0) {
                        thumb.size = thumb.element->getSize(ctx, {{thumbWidth, 0}, {thumbWidth, size.height}});
                        trackHeight = thumb.size.height;
                    } else {
                        thumb.size = thumb.element->getSize(ctx, {{thumbWidth, 0}, {thumbWidth, trackHeight}});
                    }

                    thumb.position = {(scrollLeft * size.width) / scrollWidth, childHeight};
                    children.push_back(thumb);
                }
            }

            int childWidth = size.width;
            if ((scrollDirection == ScrollDirection::Vertical || scrollDirection == ScrollDirection::Both) && scrollHeight > size.height) {
                int trackWidth = 0;
                if (this->scrollTrack) {
                    RenderElement track;
                    track.element = this->scrollTrack();
                    track.size = track.element->getSize(ctx, {{0, size.height}, size});
                    trackWidth = track.size.width;
                    childWidth -= trackWidth;
                    track.position = {childWidth, 0};
                    children.push_back(track);
                }

                if (this->scrollThumb) {
                    RenderElement thumb;
                    thumb.element = this->scrollThumb();

                    int thumbHeight = (size.height * size.height) / scrollHeight;
                    if (trackWidth == 0) {
                        thumb.size = thumb.element->getSize(ctx, {{0, thumbHeight}, {size.width, thumbHeight}});
                        trackWidth = thumb.size.width;
                    } else {
                        thumb.size = thumb.element->getSize(ctx, {{0, thumbHeight}, {trackWidth, thumbHeight}});
                    }

                    thumb.position = {childWidth, (scrollTop * size.height) / scrollHeight};
                    children.push_back(thumb);
                }
            }

            RenderElement child;
            child.element = this->child;
            child.position = {0, 0};
            child.size = {childWidth, childHeight};
            children.push_back(child);
        }

        return children;
    }
}
