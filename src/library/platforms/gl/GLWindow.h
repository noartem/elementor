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

#include "GLCursor.h"
#include "GLMonitor.h"

namespace elementor::platforms::gl {
	class GLWindow : public WindowContext {
	public:
		explicit GLWindow(const std::shared_ptr<PlatformContext>& ctx);

		~GLWindow();

		void draw();

		void setTitle(std::string newTitle) override;

		std::string getTitle() override;

		Size getSize() override;

		void setSize(Size size) override;

		std::optional<Size> getMinSize() override;

		void setMinSize(std::optional<Size> size) override;

		void setMinSize(Size size) override;

		std::optional<Size> getMaxSize() override;

		void setMaxSize(std::optional<Size> size) override;

		void setMaxSize(Size size) override;

		Position getPosition() override;

		void setPosition(Position Position) override;

		bool getFocused() override;

		std::shared_ptr<Cursor> getCursor() override;

		std::shared_ptr<Monitor> getMonitor() override;

		float getPixelScale() override {
			return pixelScale;
		}

		void setPixelScale(float newValue) override {
			pixelScale = newValue;
		}

		void close() override;

		void onClose(const std::function<void()>& callback) override {
			this->closeCallbacks.push_back(callback);
		}

		void setApplication(const std::shared_ptr<Application>& newValue) {
			this->application = newValue;
		}

		void onPosition();

		void onFocused();

		void onMouseButton(int button, int action, int mods);

		void onKeyboard(int key, int scancode, int action, int mods);

		void onChar(unsigned int codepoint);

		void onMouseMove(double x, double y);

		void onScroll(double xOffset, double yOffset);

	private:
		GLFWwindow* glWindow = nullptr;
		GrDirectContext* skContext = nullptr;
		sk_sp<SkSurface> skSurface = nullptr;
		SkCanvas* skCanvas = nullptr;

		std::shared_ptr<Application> application;

		std::shared_ptr<GLMonitor> monitor;
		std::shared_ptr<GLCursor> cursor;

		std::string title;
		std::optional<Size> minSize;
		std::optional<Size> maxSize;

		float pixelScale = 0.0f;

		std::vector<std::function<void()>> closeCallbacks;

		void refresh();

		void updateWindowSizeLimits();

		void callCloseCallbacks() {
			for (auto& callback: closeCallbacks) {
				callback();
			}
		}

		float calcPixelScale();
	};
}


#endif //ELEMENTOR_GL_WINDOW_H
