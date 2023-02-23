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
        std::shared_ptr<Element> element;
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
        virtual Size getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, Boundaries boundaries);
        virtual void paintBackground(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, SkCanvas *canvas, ElementRect rect);
        virtual std::vector <RenderElement> getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect);
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
        virtual std::shared_ptr<Element> getRoot() = 0;
        virtual void setRoot(std::shared_ptr<Element> root) = 0;

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

        virtual std::shared_ptr<Cursor> getCursor() = 0;

        virtual std::shared_ptr<Monitor> getMonitor() = 0;

        virtual void close() = 0;

        virtual void setUserPointer(std::shared_ptr<void> pointer) = 0;
        virtual std::shared_ptr<void> getUserPointer() = 0;
    };

    class ApplicationContext {
    public:
        virtual float getPixelScale() = 0;
        virtual void setPixelScale(float scale) = 0;

        virtual std::string getLocale() = 0;
        virtual void setLocale(std::string locale) = 0;

        virtual std::shared_ptr<Clipboard> getClipboard() = 0;
        virtual std::shared_ptr<Perfomance> getPerfomance() = 0;
        virtual sk_sp<SkFontMgr> getSkFontManager() = 0;

        virtual void requestNextFrame(std::function<void ()> callback) = 0;

        virtual std::shared_ptr<Window> makeWindow(Size size) = 0;
    };

    class WithChild {
    public:
        virtual void updateChild(const std::shared_ptr<Element>& child);

        [[nodiscard]] std::shared_ptr<Element> getChild() const;

        [[nodiscard]] bool hasChild() const;

        void removeChild();

    private:
        std::shared_ptr<Element> child;
    };

    class WithChildren {
    public:
        void setChildren(std::vector<std::shared_ptr<Element>> newChildren);

        void clearChildren();

        void addChild(const std::shared_ptr<Element>& child);

        void removeChild(int i);

        void removeChild(const std::shared_ptr<Element>& child);

        [[nodiscard]] std::vector<std::shared_ptr<Element>> getChildrenList() const;

        [[nodiscard]] size_t getChildrenSize() const;

        [[nodiscard]] std::shared_ptr<Element> getChild(int i) const;

        [[nodiscard]] int childIndex(const std::shared_ptr<Element>& child) const;

    private:
        std::vector<std::shared_ptr<Element>> children;
    };
}

#endif //ELEMENTOR_ELEMENT_H
