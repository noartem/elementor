//
// Created by noartem on 14.04.2022.
//

#ifndef ELEMENTOR_GL_PLATFORM_H
#define ELEMENTOR_GL_PLATFORM_H

#include "../../Element.h"

#include "GLEventLoop.h"
#include "GLClipboard.h"
#include "GLFontManager.h"
#include "GLPerfomance.h"
#include "GLWindow.h"

namespace elementor::platforms::gl {
	class GLPlatform : public PlatformContext {
	public:
		GLPlatform();

		void addWindow(const std::shared_ptr<GLWindow>& window);

		void removeWindow(const std::shared_ptr<GLWindow>& window);

		void removeWindow(unsigned int index);

		void run();

		void requestNextFrame(const std::function<void()>& callback) override;

		void requestNextFrame() override;

		std::shared_ptr<Clipboard> getClipboard() override {
			return clipboard;
		}

		std::shared_ptr<Perfomance> getPerfomance() override {
			return perfomance;
		}

		sk_sp<SkFontMgr> getSkFontManager() override {
			return this->fontManager->getSkFontManager();
		}

		std::string getLocale() override {
			return locale;
		}

		void setLocale(std::string newLocale) override {
			locale = newLocale;
		}

	private:
		std::shared_ptr<GLEventLoop> eventLoop;

		std::shared_ptr<GLClipboard> clipboard;
		std::shared_ptr<GLPerfomance> perfomance;
		std::shared_ptr<GLFontManager> fontManager;

		std::vector<std::shared_ptr<GLWindow>> windows;

		std::vector<std::function<void()>> rnfNextQueue;
		std::vector<std::function<void()>> rnfCurrentQueue;

		std::string locale = "en";

		void applyRnfQueue();
	};
};

#endif //ELEMENTOR_GL_PLATFORM_H
