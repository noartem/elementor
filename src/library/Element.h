//
// Created by noartem on 13.04.2022.
//

#ifndef ELEMENTOR_ELEMENT_H
#define ELEMENTOR_ELEMENT_H

#include "ApplicationContext.h"

#include <include/core/SkCanvas.h>

#include <vector>

namespace elementor {
    class Element;

    struct RenderElement {
        Element *element;
        RenderPosition position;
        RenderSize size;
    };

    class Element {
    public:
        ApplicationContext *context;

        virtual RenderSize getSize(RenderBoundaries boundaries);

        virtual void paintBackground(SkCanvas *canvas, RenderSize size);

        virtual std::vector <RenderElement> getChildren(RenderSize size);
    };

    class WithChild {
    public:
        void updateChild(Element *child);

        Element *getChild(ApplicationContext *context);

        bool hasChild();

        void removeChild();

    private:
        Element *child;
    };

    class WithChildren {
    public:
        void setChildren(std::vector<Element *> children);

        void addChild(Element *child);

        void removeChild(int i);

        std::vector<Element *> getChildren();

        int getChildrenSize();

        Element *getChild(int i);

    private:
        std::vector<Element *> children;
    };

    RenderSize fitSizeInBoundaries(RenderSize size, RenderBoundaries boundaries);
}

#endif //ELEMENTOR_ELEMENT_H
