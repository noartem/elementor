//
// Created by noartem on 13.04.2022.
//

#ifndef ELEMENTOR_ELEMENT_H
#define ELEMENTOR_ELEMENT_H

#include "Render.h"

#include <include/core/SkCanvas.h>
#include <include/core/SkFontMgr.h>

#include <vector>
#include <optional>
#include <functional>

namespace elementor {
    class Element;
    class Window;
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
        virtual Size getSize(ApplicationContext *ctx, Window *window, Boundaries boundaries);
        virtual void paintBackground(ApplicationContext *ctx, Window *window, SkCanvas *canvas, ElementRect rect);
        virtual std::vector <RenderElement> getChildren(ApplicationContext *ctx, Window *window, Size size);
        virtual ClipBehavior getClipBehaviour();
    };

    // Default monitor scale is 38 logical pixels per centimeter
    #define DefaultMonitorScale 3.8;

    class Clipboard {
    public:
        virtual void set(std::string text) = 0;
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
        virtual CursorShape get() = 0;
    };

    class Perfomance {
    public:
        virtual double getFPS() = 0;
    };

    class Window {
    public:
        virtual Size getSize() = 0;
        virtual std::optional<Size> getMinSize() = 0;
        virtual std::optional<Size> getMaxSize() = 0;
        virtual void setMinSize(Size size) = 0;
        virtual void setMaxSize(Size size) = 0;

        virtual Position getPosition() = 0;
        virtual void setPosition(Position Position) = 0;

        virtual Size getMonitorSize() = 0;
        virtual Size getMonitorPhysicalSize() = 0;
        virtual float getMonitorPixelScale() = 0;
        virtual void setMonitorPixelScale(float scale) = 0;

        virtual Element *getRoot() = 0;
        virtual void setRoot(Element *root) = 0;

        virtual void setTitle(std::string title) = 0;
        virtual std::string getTitle() = 0;

        virtual void close() = 0;

        Cursor *getCursor();
    };

    class ApplicationContext {
    public:
        Element *root;
        Clipboard *clipboard;
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
