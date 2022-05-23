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
        Position position;
        Size size;
    };

    enum class ClipBehavior {
        None,
        Hard,
        AntiAlias,
    };

    class Element {
    public:
        ApplicationContext *context;

        virtual Size getSize(Boundaries boundaries);

        virtual void paintBackground(SkCanvas *canvas, ElementRect rect);

        virtual std::vector <RenderElement> getRenderChildren(Size size);

        virtual ClipBehavior getClipBehaviour();
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

    Size fitSizeInBoundaries(Size size, Boundaries boundaries);
}

#endif //ELEMENTOR_ELEMENT_H
