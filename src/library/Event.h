//
// Created by noartem on 09.05.2022.
//

#ifndef ELEMENTOR_EVENT_H
#define ELEMENTOR_EVENT_H

#include <string>
#include <vector>

namespace elementor {
	class Event {
	public:
		virtual std::string_view getName() = 0;
	};

	enum class EventCallbackResponse {
		None,
		StopPropagation,
	};

	class WithEvents {
	public:
		virtual EventCallbackResponse onEvent(std::shared_ptr<Event> event) = 0;
	};

	enum class MouseButton {
		Left,
		Right,
		Middle,
		Back,
		Forward,
	};

	enum class KeyAction {
		Release,
		Press,
		Repeat,
	};

	enum class KeyMod {
		None,
		Shift,
		Control,
		Alt,
		Super,
		CapsLock,
		NumLock,
	};

	enum class KeyboardKey {
		Unknow,
		Space,
		Apostraphe,
		Comma,
		Minus,
		Period,
		Slash,
		Number0,
		Number1World,
		Number1,
		Number2World,
		Number2,
		Number3,
		Number4,
		Number5,
		Number6,
		Number7,
		Number8,
		Number9,
		Semicolon,
		Equal,
		A,
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		M,
		N,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z,
		LeftBracket,
		Backslash,
		RightBracket,
		GraveAccent,
		Escape,
		Enter,
		Tab,
		Backspace,
		Insert,
		Delete,
		Right,
		Left,
		Down,
		Up,
		PageUp,
		PageDown,
		Home,
		End,
		CapsLock,
		ScrollLock,
		NumLock,
		PrintScreen,
		Pause,
		F1,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,
		F9,
		F10,
		F11,
		F12,
		F13,
		F14,
		F15,
		F16,
		F17,
		F18,
		F19,
		F20,
		F21,
		F22,
		F23,
		F24,
		F25,
		KP0,
		KP1,
		KP2,
		KP3,
		KP4,
		KP5,
		KP6,
		KP7,
		KP8,
		KP9,
		KPDecimal,
		KPDivide,
		KPMultiply,
		KPSubtract,
		KPAdd,
		KPEnter,
		KPEqual,
		LeftShift,
		LeftControl,
		LeftAlt,
		LeftSuper,
		RightShift,
		RightControl,
		RightAlt,
		RightSuper,
		Menu,
	};

	class MouseButtonEvent : public Event {
	public:
		MouseButtonEvent(MouseButton button, KeyAction action, KeyMod mod) {
			this->button = button;
			this->action = action;
			this->mod = mod;
		}

		MouseButton button;
		KeyAction action;
		KeyMod mod;

		std::string_view getName() override {
			return "mouse-button";
		};
	};

	class MouseMoveEvent : public Event {
	public:
		MouseMoveEvent(float x, float y) {
			this->x = x;
			this->y = y;
		}

		float x;
		float y;

		std::string_view getName() override {
			return "mouse-move";
		}
	};

	class ScrollEvent : public Event {
	public:
		ScrollEvent(float xOffset, float yOffset) {
			this->xOffset = xOffset;
			this->yOffset = yOffset;
		}

		float xOffset;
		float yOffset;

		std::string_view getName() override {
			return "scroll";
		}
	};

	class KeyboardEvent : public Event {
	public:
		KeyboardEvent(KeyboardKey key, int scancode, KeyAction action, KeyMod mod) {
			this->key = key;
			this->scancode = scancode;
			this->action = action;
			this->mod = mod;
		}

		KeyboardKey key;
		int scancode;
		KeyAction action;
		KeyMod mod;

		std::string_view getName() override {
			return "keyboard";
		}
	};

	class CharEvent : public Event {
	public:
		explicit CharEvent(char32_t value) {
			this->value = value;
		}

		char32_t value;

		std::string_view getName() override {
			return "char";
		}
	};

	class HoverEvent : public Event {
	public:
		explicit HoverEvent(bool hovered) {
			this->hovered = hovered;
		}

		bool hovered;

		std::string_view getName() override {
			return "hover";
		}
	};
}

#endif //ELEMENTOR_EVENT_H
