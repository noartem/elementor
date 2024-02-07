//
// Created by noartem on 05.02.2024.
//

#ifndef ELEMENTOR_GL_PLATFORM_CONTEXT_H
#define ELEMENTOR_GL_PLATFORM_CONTEXT_H

#include <string>
#include <memory>
#include <functional>

#include <include/core/SkFontMgr.h>

#include "elementor.h"

namespace elementor {
	class GLPlatformContext {
	public:
		[[nodiscard]] virtual std::string getLocale() const = 0;

		virtual void setLocale(std::string locale) = 0;

		[[nodiscard]] virtual std::shared_ptr<Clipboard> getClipboard() const = 0;

		[[nodiscard]] virtual std::shared_ptr<Perfomance> getPerfomance() const = 0;

		[[nodiscard]] virtual sk_sp<SkFontMgr> getSkFontManager() const = 0;

		virtual void requestNextFrame(const std::function<void()>& callback) = 0;

		virtual void requestNextFrame() = 0;
	};
}

#endif //ELEMENTOR_GL_PLATFORM_CONTEXT_H
