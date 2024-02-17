//
// Created by noartem on 09.05.2022.
//

#ifndef ELEMENTOR_EVENT_H
#define ELEMENTOR_EVENT_H

#include <map>
#include <string>
#include <vector>
#include <functional>

#ifndef DEFINE_EVENT_HANDLER
#define DEFINE_EVENT_HANDLER(eventClass, eventName) \
public: static std::shared_ptr<EventHandler> Handle(std::function<EventCallbackResponse(const std::shared_ptr<eventClass>&)> callback) { \
    return std::make_shared<Handler>(callback);     \
}                                                   \
                                                    \
private: class Handler : public EventHandler {      \
public:                                             \
    explicit Handler(std::function<EventCallbackResponse(const std::shared_ptr<eventClass>&)> callback)                                  \
        : callback(callback) {                      \
    }                                               \
                                                    \
    std::string_view getName() override {           \
        return eventName;                           \
    }                                               \
                                                    \
    EventCallbackResponse onEvent(const std::shared_ptr<Event>& event) override {                                                        \
        auto eventMapped = std::dynamic_pointer_cast<eventClass>(event);                                                                 \
        if (!eventMapped) {                         \
            return EventCallbackResponse::None;     \
        }                                           \
                                                    \
        return callback(eventMapped);               \
    }                                               \
                                                    \
private:                                            \
    std::function<EventCallbackResponse(const std::shared_ptr<eventClass>&)> callback;                                                      \
};
#endif

namespace elementor {
	class Event {
	public:
		virtual std::string_view getName() = 0;
	};

	enum class EventCallbackResponse {
		None,
		StopPropagation,
	};

	class EventHandler {
	public:
		virtual std::string_view getName() = 0;
		virtual EventCallbackResponse onEvent(const std::shared_ptr<Event>& event) = 0;
	};

	using EventsHandlersMap = std::map<std::string_view, std::vector<std::shared_ptr<EventHandler>>>;

	class WithEventsHandlers {
	public:
		virtual std::vector<std::shared_ptr<EventHandler>> getEventsHandlers() = 0;
	};

	class WithGlobalEventsHandlers {
	public:
		virtual std::vector<std::shared_ptr<EventHandler>> getGlobalEventsHandlers() = 0;
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

	constexpr int KeyModsShift = 0x0001;
	constexpr int KeyModsCtrl = 0x0002;
	constexpr int KeyModsAlt = 0x0004;
	constexpr int KeyModsSuper = 0x0008;
	constexpr int KeyModsCapsLock = 0x0010;
	constexpr int KeyModsNumLock = 0x0020;

	enum class KeyboardKey {
		Unknown,
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
	DEFINE_EVENT_HANDLER(MouseButtonEvent, "mouse-button");
	public:
		MouseButtonEvent(MouseButton button, KeyAction action, int mods)
			: button(button), action(action), mods(mods) {
		}

		MouseButton button;
		KeyAction action;
		int mods;

		std::string_view getName() override {
			return "mouse-button";
		};
	};

	class MouseMoveEvent : public Event {
	DEFINE_EVENT_HANDLER(MouseMoveEvent, "mouse-move");
	public:
		MouseMoveEvent(float x, float y)
			: x(x), y(y) {
		}

		float x;
		float y;

		std::string_view getName() override {
			return "mouse-move";
		}
	};

	class ScrollEvent : public Event {
	DEFINE_EVENT_HANDLER(ScrollEvent, "scroll");
	public:
		ScrollEvent(float xOffset, float yOffset)
			: xOffset(xOffset), yOffset(yOffset) {
		}

		float xOffset;
		float yOffset;

		std::string_view getName() override {
			return "scroll";
		}
	};

	class KeyboardEvent : public Event {
	DEFINE_EVENT_HANDLER(KeyboardEvent, "keyboard");
	public:
		KeyboardEvent(KeyboardKey key, int scancode, KeyAction action, int mods)
			: key(key), scancode(scancode), action(action), mods(mods) {
		}

		KeyboardKey key;
		int scancode;
		KeyAction action;
		int mods;

		std::string_view getName() override {
			return "keyboard";
		}
	};

	class CharEvent : public Event {
	DEFINE_EVENT_HANDLER(CharEvent, "char");
	public:
		explicit CharEvent(char32_t value)
			: value(value) {
		}

		char32_t value;

		std::string_view getName() override {
			return "char";
		}
	};

	class HoverEvent : public Event {
	DEFINE_EVENT_HANDLER(HoverEvent, "hover");
	public:
		explicit HoverEvent(bool hovered)
			: hovered(hovered) {
		}

		bool hovered;

		std::string_view getName() override {
			return "hover";
		}
	};

	class FocusEvent : public Event {
	DEFINE_EVENT_HANDLER(FocusEvent, "focus");
	public:
		explicit FocusEvent(bool focused)
			: focused(focused) {
		}

		bool focused;

		std::string_view getName() override {
			return "focus";
		}
	};

	class FocusInEvent : public Event {
	DEFINE_EVENT_HANDLER(FocusInEvent, "focus-in");
	public:
		explicit FocusInEvent() {
		}

		std::string_view getName() override {
			return "focus-in";
		}
	};

	class FocusOutEvent : public Event {
	DEFINE_EVENT_HANDLER(FocusOutEvent, "focus-out");
	public:
		explicit FocusOutEvent() {
		}

		std::string_view getName() override {
			return "focus-out";
		}
	};
}

#endif //ELEMENTOR_EVENT_H
