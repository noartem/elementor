//
// Created by noartem on 13.04.2022.
//

#ifndef ELEMENTOR_ELEMENT_H
#define ELEMENTOR_ELEMENT_H

#include "Render.h"

#include <include/core/SkCanvas.h>
#include <include/core/SkFontMgr.h>

#include <vector>
#include <functional>

namespace elementor {
    class Element;
    class ApplicationContext;

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
        virtual Size getSize(ApplicationContext *ctx, Boundaries boundaries);

        virtual void paintBackground(ApplicationContext *ctx, SkCanvas *canvas, ElementRect rect);

        virtual std::vector <RenderElement> getChildren(ApplicationContext *ctx, Size size);

        virtual ClipBehavior getClipBehaviour();
    };

    // Default monitor scale is 38 logical pixels per centimeter
    #define DefaultMonitorScale 3.8;

    class Clipboard {
    public:
        virtual void set(std::string) = 0;
        virtual std::string get() = 0;
    };

    enum class CursorShape {
        Default,
        Arrow,
        IBeam,
        Crosshair,
        Hand,
        HorizontalResize,
        VerticalResize
    };

    class Cursor {
    public:
        virtual void set(CursorShape shape) = 0;
    };

    class Perfomance {
    public:
        virtual double getFPS() = 0;
    };

    class WindowContext {
    public:
        Size size;
        Size monitorSize;
        Size monitorPhysicalSize;
        float monitorPixelScale;
        Element *root;
    };

    class ApplicationContext {
    public:
        Element *root;
        WindowContext *window;
        Clipboard *clipboard;
        Cursor *cursor;
        Perfomance *perfomance;
        virtual void requestNextFrame(std::function<void ()> callback) = 0;
        virtual sk_sp<SkFontMgr> getSkFontManager() = 0;
    };

    class WithChild {
    public:
        void updateChild(Element *child);

        Element *getChild();

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

        std::vector<Element *> getChildrenList();

        int getChildrenSize();

        Element *getChild(int i);

    private:
        std::vector<Element *> children;
    };

    Size fitSizeInBoundaries(Size size, Boundaries boundaries);
}

#endif //ELEMENTOR_ELEMENT_H
