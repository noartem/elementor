//
// Created by noartem on 15.08.2022.
//

#ifndef ELEMENTOR_GL_WINDOW_H
#define ELEMENTOR_GL_WINDOW_H

#include <memory>
#include <string>
#include <functional>

#define SK_GL

#include "GLFW/glfw3.h"
#include "include/gpu/GrDirectContext.h"

#include "elementor.h"

#include "GLPlatformContext.h"
#include "GLCursor.h"
#include "GLDisplay.h"

#include "utility.h"

namespace elementor::platforms::gl {
	class GLWindow : public ApplicationContext {
	public:
		explicit GLWindow(const std::shared_ptr<GLPlatformContext>& ctx);

		~GLWindow();

		void tick();

		void setTitle(const std::string_view& newTitle) {
			title = newTitle;
			glfwSetWindowTitle(glWindow, title.data());
		}

		[[nodiscard]] std::string getTitle() const {
			return title;
		}

		void setSize(const Size& size) {
			glfwSetWindowSize(glWindow, std::ceil(size.width * pixelScale), std::ceil(size.height * pixelScale));
			requestNextFrame();
		}

		[[nodiscard]] std::optional<Size> getMinSize() const {
			return minSize;
		}

		void setMinSize(std::optional<Size> size) {
			minSize = size;
			updateWindowSizeLimits();
		}

		void setMinSize(const Size& size) {
			minSize = size;
			updateWindowSizeLimits();
		}

		[[nodiscard]] std::optional<Size> getMaxSize() const {
			return maxSize;
		}

		void setMaxSize(std::optional<Size> size) {
			maxSize = size;
			updateWindowSizeLimits();
		}

		void setMaxSize(const Size& size) {
			maxSize = size;
			updateWindowSizeLimits();
		}

		[[nodiscard]] Position getPosition() const {
			return getWindowPosition(glWindow);
		}

		void setPosition(const Position& position) {
			glfwSetWindowPos(glWindow, std::ceil(position.x), std::ceil(position.y));
		}

		[[nodiscard]] bool isFocused() const {
			return glfwGetWindowAttrib(glWindow, GLFW_FOCUSED);
		}

		void close() {
			glfwDestroyWindow(glWindow);
			callCloseCallbacks();
		}

		void onClose(const std::function<void()>& callback) {
			closeCallbacks.push_back(callback);
		}

		void setRoot(const std::shared_ptr<Element>& rootElement);

		void onPosition();

		void onFocused();

		void onMouseButton(int button, int action, int mods);

		void onKeyboard(int key, int scancode, int action, int mods);

		void onChar(unsigned int codepoint);

		void onMouseMove(double x, double y);

		void onScroll(double xOffset, double yOffset);

		std::string getLocale() override {
			return ctx->getLocale();
		}

		void setLocale(std::string locale) override {
			ctx->setLocale(locale);
		}

		std::shared_ptr<Clipboard> getClipboard() override {
			return ctx->getClipboard();
		}

		std::shared_ptr<Perfomance> getPerfomance() override {
			return ctx->getPerfomance();
		}

		sk_sp<SkFontMgr> getSkFontManager() override {
			return ctx->getSkFontManager();
		}

		void requestNextFrame(const std::function<void()>& callback) override {
			ctx->requestNextFrame(callback);
		}

		void requestNextFrame() override {
			ctx->requestNextFrame();
		}

		std::shared_ptr<Cursor> getCursor() override {
			return cursor;
		}

		std::shared_ptr<Display> getDisplay() override {
			return display;
		}

		float getPixelScale() override {
			return pixelScale;
		}

		void setPixelScale(float newValue) override {
			pixelScale = newValue;
		}

	private:
		std::shared_ptr<GLPlatformContext> ctx;

		GLFWwindow* glWindow = nullptr;

		GLFWmonitor* glMonitor = nullptr;
		void updateMonitor();

		GrDirectContext* skContext = nullptr;
		sk_sp<SkSurface> skSurface = nullptr;
		SkCanvas* skCanvas = nullptr;

		std::shared_ptr<GLDisplay> display;
		std::shared_ptr<GLCursor> cursor;

		std::string title;
		std::optional<Size> minSize;
		std::optional<Size> maxSize;

		std::vector<std::function<void()>> closeCallbacks;

		std::shared_ptr<ApplicationTree> applicationTree;
		std::vector<std::shared_ptr<Event>> pendingEvents;
		std::unique_ptr<ApplicationHoverState> hoverState;
		std::unique_ptr<ApplicationFocusState> focusState;

		[[nodiscard]] Size getSize() const {
			return getWindowSize(glWindow);
		}

		void refresh();

		void draw();

		void updateWindowSizeLimits();

		void callCloseCallbacks() {
			for (auto& callback: closeCallbacks) {
				callback();
			}
		}

		void dispatchEvent(const std::shared_ptr<Event>& event);
		void dispatchPendingEvents();

		float pixelScale = 0.0f;
		float calcPixelScale();
		void updatePixelScale();

		Position positionBeforeFullScreen;
		Size sizeBeforeFullScreen;
		void openFullscreen(GLFWmonitor* monitor);
		void closeFullscreen();
		void toggleFullscreen();
	};
}


#endif //ELEMENTOR_GL_WINDOW_H
