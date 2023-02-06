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
        virtual ~Element() = default;

        virtual Size getSize(ApplicationContext *ctx, Window *window, Boundaries boundaries);
        virtual void paintBackground(ApplicationContext *ctx, Window *window, SkCanvas *canvas, ElementRect rect);
        virtual std::vector <RenderElement> getChildren(ApplicationContext *ctx, Window *window, ElementRect rect);
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

    class Monitor {
    public:
        virtual Size getSize() = 0;
        virtual Size getPhysicalSize() = 0;
    };

    class Window {
    public:
        virtual Element *getRoot() = 0;
        virtual void setRoot(Element *root) = 0;

        virtual void setTitle(std::string title) = 0;
        virtual std::string getTitle() = 0;

        virtual Size getSize() = 0;
        virtual void setSize(Size size) = 0;

        virtual std::optional<Size> getMinSize() = 0;
        virtual void setMinSize(std::optional<Size> size) = 0;
        virtual void setMinSize(Size size) = 0;

        virtual std::optional<Size> getMaxSize() = 0;
        virtual void setMaxSize(std::optional<Size> size) = 0;
        virtual void setMaxSize(Size size) = 0;

        virtual Position getPosition() = 0;
        virtual void setPosition(Position Position) = 0;

        virtual Cursor *getCursor() = 0;

        virtual Monitor *getMonitor() = 0;

        virtual void close() = 0;

        virtual void setUserPointer(void *pointer) = 0;
        virtual void *getUserPointer() = 0;
    };

    class ApplicationContext {
    public:
        virtual ~ApplicationContext() = default;

        virtual float getPixelScale() = 0;
        virtual void setPixelScale(float scale) = 0;

        virtual std::string getLocale() = 0;
        virtual void setLocale(std::string locale) = 0;

        virtual Clipboard *getClipboard() = 0;
        virtual Perfomance *getPerfomance() = 0;
        virtual sk_sp<SkFontMgr> getSkFontManager() = 0;

        virtual void requestNextFrame(std::function<void ()> callback) = 0;

        virtual Window *makeWindow(Size size) = 0;
    };

    class WithChild {
    public:
        virtual ~WithChild();

        virtual void updateChild(Element *child);

        Element *getChild() const;

        bool hasChild() const;

        void removeChild();

    private:
        Element *child;
    };

    class WithChildren {
    public:
        virtual ~WithChildren();

        void setChildren(std::vector<Element *> newChildren);

        void clearChildren();

        void addChild(Element *child);

        void removeChild(int i);

        void removeChild(Element *child);

        std::vector<Element *> getChildrenList() const;

        size_t getChildrenSize() const;

        Element *getChild(int i) const;

        int childIndex(Element *child) const;

    private:
        std::vector<Element *> children;
    };
}

#endif //ELEMENTOR_ELEMENT_H
