//
// Created by noartem on 12.01.2024.
//

#ifndef ELEMENTOR_APPLICATION_CONTEXT_H
#define ELEMENTOR_APPLICATION_CONTEXT_H

#include <vector>
#include <optional>
#include <functional>
#include <string>
#include <memory>

#include <include/core/SkFontMgr.h>

#include "Render.h"
#include "Event.h"

namespace elementor {
	constexpr float DefaultPixelScale = 3.8; // 38 logical pixels per centimeter

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

		virtual Position getPosition() = 0;
	};

	class Display {
	public:
		virtual Size getSize() = 0;

		virtual Size getPhysicalSize() = 0;
	};

	class ApplicationContext {
	public:
		virtual std::string getLocale() = 0;

		virtual void setLocale(std::string locale) = 0;

		virtual std::shared_ptr<Clipboard> getClipboard() = 0;

		virtual std::shared_ptr<Perfomance> getPerfomance() = 0;

		virtual sk_sp<SkFontMgr> getSkFontManager() = 0;

		virtual void requestNextFrame(const std::function<void()>& callback) = 0;

		virtual void requestNextFrame() = 0;

		virtual std::shared_ptr<Cursor> getCursor() = 0;

		virtual std::shared_ptr<Display> getDisplay() = 0;

		virtual float getPixelScale() = 0;

		virtual void setPixelScale(float pixelScale) = 0;
	};
}

#endif //ELEMENTOR_APPLICATION_CONTEXT_H
