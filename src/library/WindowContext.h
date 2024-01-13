//
// Created by admin on 12.01.2024.
//

#ifndef ELEMENTOR_WINDOW_CONTEXT_H
#define ELEMENTOR_WINDOW_CONTEXT_H

#include <vector>
#include <optional>
#include <functional>
#include <string>
#include <memory>

#include "Render.h"
#include "Event.h"

namespace elementor {
	constexpr float DefaultPixelScale = 3.8; // 38 logical pixels per centimeter

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

	class Monitor {
	public:
		virtual Size getSize() = 0;

		virtual Size getPhysicalSize() = 0;
	};

	class WindowContext {
	public:
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

		virtual bool getFocused() = 0;

		virtual std::shared_ptr<Cursor> getCursor() = 0;

		virtual std::shared_ptr<Monitor> getMonitor() = 0;

		virtual float getPixelScale() = 0;

		virtual void setPixelScale(float pixelScale) = 0;

		virtual void close() = 0;

		virtual void onClose(const std::function<void()>& callback) = 0;
	};
}

#endif //ELEMENTOR_WINDOW_CONTEXT_H
