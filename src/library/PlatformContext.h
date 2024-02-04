//
// Created by admin on 12.01.2024.
//

#ifndef ELEMENTOR_PLATFORM_CONTEXT_H
#define ELEMENTOR_PLATFORM_CONTEXT_H

#include <string>
#include <memory>
#include <functional>

#include <include/core/SkFontMgr.h>

namespace elementor {
	class Clipboard {
	public:
		virtual ~Clipboard() = default;

		virtual void set(const std::string_view& text) = 0;

		virtual const std::string_view& get() = 0;
	};

	class Perfomance {
	public:
		virtual double getFPS() = 0;
	};

	class PlatformContext {
	public:
		virtual std::string getLocale() = 0;

		virtual void setLocale(std::string locale) = 0;

		virtual std::shared_ptr<Clipboard> getClipboard() = 0;

		virtual std::shared_ptr<Perfomance> getPerfomance() = 0;

		virtual sk_sp<SkFontMgr> getSkFontManager() = 0;

		virtual void requestNextFrame(const std::function<void()>& callback) = 0;

		virtual void requestNextFrame() = 0;
	};
}

#endif //ELEMENTOR_PLATFORM_CONTEXT_H
