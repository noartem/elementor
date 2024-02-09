//
// Created by noartem on 14.04.2022.
//

#ifndef ELEMENTOR_GL_PLATFORM_H
#define ELEMENTOR_GL_PLATFORM_H

#include "elementor.h"

#include "GLPlatformContext.h"

#include "GLEventLoop.h"
#include "GLClipboard.h"
#include "GLFontManager.h"
#include "GLPerfomance.h"
#include "GLWindow.h"

namespace elementor::platforms::gl {
	class GLPlatform : public GLPlatformContext {
	public:
		GLPlatform();

		void addWindow(const std::shared_ptr<GLWindow>& window);

		void removeWindow(const std::shared_ptr<GLWindow>& window);

		void removeWindow(unsigned int index);

		void run();

		void requestNextFrame(const std::function<void()>& callback) override;

		void requestNextFrame() override;

		[[nodiscard]] std::shared_ptr<Clipboard> getClipboard() const override {
			return clipboard;
		}

		[[nodiscard]] std::shared_ptr<Perfomance> getPerfomance() const override {
			return perfomance;
		}

		[[nodiscard]] sk_sp<SkFontMgr> getSkFontManager() const override {
			return fontManager->getSkFontManager();
		}

		[[nodiscard]] std::string getLocale() const {
			return locale;
		}

		void setLocale(std::string newLocale) {
			locale = newLocale;
		}

	private:
		std::shared_ptr<GLEventLoop> eventLoop;

		std::shared_ptr<GLClipboard> clipboard;
		std::shared_ptr<GLPerfomance> perfomance;
		std::shared_ptr<GLFontManager> fontManager;

		std::vector<std::shared_ptr<GLWindow>> windows;

		std::vector<std::function<void()>> rnfQueue;

		std::string locale = "en";

		void tick();

		void applyRnfQueue();
	};
};

#endif //ELEMENTOR_GL_PLATFORM_H
