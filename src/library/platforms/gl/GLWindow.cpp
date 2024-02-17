//
// Created by noartem on 14.04.2022.
//

#include "GLWindow.h"

#include <memory>
#include <cmath>
#include <fstream>

#include "GLFW/glfw3.h"

#include "include/gpu/GrBackendSurface.h"
#include "include/gpu/gl/GrGLInterface.h"
#include "include/core/SkTypeface.h"
#include "include/core/SkColorSpace.h"
#include "include/core/SkSurface.h"
#include "include/gpu/GrDirectContext.h"

#include "elementor.h"

#include "utility.h"
#include "GLCursor.h"
#include "GLDisplay.h"

#define GL_RGBA8 0x8058

namespace elementor::platforms::gl {
	GLWindow* getGLFWWindowGLWindow(GLFWwindow* window) {
		return static_cast<GLWindow*>(glfwGetWindowUserPointer(window));
	}

	void onWindowRefresh(GLFWwindow* glfwWindow) {
		GLWindow* window = getGLFWWindowGLWindow(glfwWindow);
		window->requestNextFrame();
	}

	void onWindowPosition(GLFWwindow* glfwWindow, [[maybe_unused]] int x, [[maybe_unused]] int y) {
		GLWindow* window = getGLFWWindowGLWindow(glfwWindow);
		window->onPosition();
	}

	void onWindowClose(GLFWwindow* glfwWindow) {
		GLWindow* window = getGLFWWindowGLWindow(glfwWindow);
		window->close();
	}

	void onSetWindowFocus(GLFWwindow* glfwWindow, [[maybe_unused]] int focused) {
		GLWindow* window = getGLFWWindowGLWindow(glfwWindow);
		window->onFocused();
	}

	void onWindowKey(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods) {
		GLWindow* window = getGLFWWindowGLWindow(glfwWindow);
		window->onKeyboard(key, scancode, action, mods);
	}

	void onWindowChar(GLFWwindow* glfwWindow, unsigned int codepoint) {
		GLWindow* window = getGLFWWindowGLWindow(glfwWindow);
		window->onChar(codepoint);
	}

	void onWindowMouseButton(GLFWwindow* glfwWindow, int button, int action, int mods) {
		GLWindow* window = getGLFWWindowGLWindow(glfwWindow);
		window->onMouseButton(button, action, mods);
	}

	void onWindowCursorPosition(GLFWwindow* glfwWindow, double x, double y) {
		GLWindow* window = getGLFWWindowGLWindow(glfwWindow);
		window->onMouseMove(x, y);
	}

	void onWindowScroll(GLFWwindow* glfwWindow, double x, double y) {
		GLWindow* window = getGLFWWindowGLWindow(glfwWindow);
		window->onScroll(x, y);
	}

	GLWindow::GLWindow(const std::shared_ptr<GLPlatformContext>& ctx)
		: ctx(ctx) {
		glWindow = glfwCreateWindow(1, 1, "Elementor", nullptr, nullptr);

		glfwMakeContextCurrent(glWindow);
		glfwSwapInterval(1);
		glfwSetWindowUserPointer(glWindow, this);
		glfwSetWindowRefreshCallback(glWindow, onWindowRefresh);
		glfwSetWindowPosCallback(glWindow, onWindowPosition);
		glfwSetWindowCloseCallback(glWindow, onWindowClose);
		glfwSetWindowFocusCallback(glWindow, onSetWindowFocus);
		glfwSetKeyCallback(glWindow, onWindowKey);
		glfwSetCharCallback(glWindow, onWindowChar);
		glfwSetMouseButtonCallback(glWindow, onWindowMouseButton);
		glfwSetCursorPosCallback(glWindow, onWindowCursorPosition);
		glfwSetScrollCallback(glWindow, onWindowScroll);

		updateMonitor();

		cursor = std::make_shared<GLCursor>(glWindow);

		skContext = GrDirectContext::MakeGL(GrGLMakeNativeInterface()).release();
	}

	GLWindow::~GLWindow() {
		delete skContext;
		delete skCanvas;
	}

	void GLWindow::refresh() {
		auto size = getSize();

		GrGLFramebufferInfo framebufferInfo;
		framebufferInfo.fFBOID = 0;
		framebufferInfo.fFormat = GL_RGBA8;

		glfwMakeContextCurrent(glWindow);
		GrBackendRenderTarget backendRenderTarget(
			(int)size.width,
			(int)size.height,
			0,
			0,
			framebufferInfo
		);
		// TODO: clear skSurface?
		skSurface = SkSurface::MakeFromBackendRenderTarget(
			skContext,
			backendRenderTarget,
			kBottomLeft_GrSurfaceOrigin,
			kRGBA_8888_SkColorType,
			SkColorSpace::MakeSRGB(),
			nullptr
		);
		// TODO: clear canvas?
		skCanvas = skSurface->getCanvas();
	}

	void GLWindow::draw() {
		refresh();

		skCanvas->clear(SK_ColorBLACK);
		applicationTree->draw(skCanvas);

		glfwMakeContextCurrent(glWindow);
		skContext->flush();
		glfwSwapBuffers(glWindow);
	}

	void GLWindow::dispatchEvent(const std::shared_ptr<Event>& event) {
		pendingEvents.push_back(event);
		requestNextFrame();
	}

	void GLWindow::dispatchPendingEvents() {
		auto globalEventsHandlers = applicationTree->getGlobalEventsHandlers();

		auto lastPendingEvents = pendingEvents;
		pendingEvents = {};
		for (const auto& event: lastPendingEvents) {
			if (hoverState->onEvent(event) == EventCallbackResponse::StopPropagation) {
				continue;
			}

			if (focusState->onEvent(event) == EventCallbackResponse::StopPropagation) {
				continue;
			}


			auto keyboardEvent = std::dynamic_pointer_cast<KeyboardEvent>(event);
			if (keyboardEvent) {
				if (keyboardEvent->action == KeyAction::Release &&
					keyboardEvent->key == KeyboardKey::F11 &&
					keyboardEvent->mods == 0) {
					toggleFullscreen();
					continue;
				}

				D(
					if (keyboardEvent->action == KeyAction::Release &&
						keyboardEvent->mods & KeyModsCtrl &&
						keyboardEvent->key == KeyboardKey::P) {
						if (keyboardEvent->mods & KeyModsShift) {
							std::ofstream logFile(std::format("elementor_tree_dump_{}.txt",
								std::chrono::system_clock::now().time_since_epoch().count()));
							applicationTree->print(logFile);
							logFile.close();
						} else {
							applicationTree->print(std::cout);
						}

						continue;
					}

					if (keyboardEvent->action == KeyAction::Release &&
						keyboardEvent->mods & KeyModsCtrl &&
						keyboardEvent->key == KeyboardKey::F) {
						D_LOG("FPS: " << ctx->getPerfomance()->getFPS());
						continue;
					}
				);
			}

			for (const auto& eventHandler: globalEventsHandlers[event->getName()]) {
				auto eventHandlerResponse = eventHandler->onEvent(event);
				if (eventHandlerResponse != EventCallbackResponse::None) {
					break;
				}
			}
		}
	}

	void GLWindow::tick() {
		if (applicationTree == nullptr) {
			return;
		}

		cursor->updateCursor();

		applicationTree->resize(getSize());

		hoverState->tick();
		focusState->tick();

		dispatchPendingEvents();

		applicationTree->checkIfChanged();
		applicationTree->updateChanged();

		if (getSize() == ZeroSize) {
			return;
		}

		draw();
	}

	void GLWindow::setRoot(const std::shared_ptr<Element>& rootElement) {
		applicationTree = std::make_shared<ApplicationTree>(rootElement, getSize());
		hoverState = std::make_unique<HoverState>(applicationTree, cursor);
		focusState = std::make_unique<FocusState>(applicationTree);
	}

	void GLWindow::updateWindowSizeLimits() {
		glfwSetWindowSizeLimits(
			glWindow,
			minSize ? (int)(minSize->width * pixelScale) : GLFW_DONT_CARE,
			minSize ? (int)(minSize->height * pixelScale) : GLFW_DONT_CARE,
			maxSize ? (int)(maxSize->width * pixelScale) : GLFW_DONT_CARE,
			maxSize ? (int)(maxSize->height * pixelScale) : GLFW_DONT_CARE
		);
	}

	void GLWindow::openFullscreen(GLFWmonitor* monitor) {
		positionBeforeFullScreen = getPosition();
		sizeBeforeFullScreen = getSize();

		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		glfwSetWindowMonitor(
			glWindow,
			monitor,
			0,
			0,
			mode->width,
			mode->height,
			mode->refreshRate
		);
	}

	void GLWindow::closeFullscreen() {
		glfwSetWindowMonitor(
			glWindow,
			nullptr,
			(int)positionBeforeFullScreen.x,
			(int)positionBeforeFullScreen.y,
			(int)(sizeBeforeFullScreen.width * pixelScale),
			(int)(sizeBeforeFullScreen.height * pixelScale),
			GLFW_DONT_CARE
		);
	}

	void GLWindow::toggleFullscreen() {
		auto glfwMonitor = getWindowMonitor(glWindow);
		if (glfwGetWindowMonitor(glWindow) == nullptr) {
			openFullscreen(glfwMonitor);
		} else {
			closeFullscreen();
		}
	}

	float GLWindow::calcPixelScale() {
		auto monitorScale = getMonitorSize(glMonitor).width / getMonitorPhysicalSize(glMonitor).width;
		return monitorScale / DefaultPixelScale;
	}

	void GLWindow::updatePixelScale() {
		auto oldPixelScale = pixelScale;
		auto newPixelScale = calcPixelScale();
		pixelScale = newPixelScale;

		if (oldPixelScale == 0 || oldPixelScale == newPixelScale) {
			return;
		}

		updateWindowSizeLimits();

		// TODO: Add window resize based on changed pixelScale
	}

	void GLWindow::updateMonitor() {
		auto newGlMonitor = getWindowMonitor(glWindow);
		if (newGlMonitor == nullptr) {
			if (glMonitor != nullptr) {
				return;
			}

			newGlMonitor = glfwGetPrimaryMonitor();
		}

		if (glMonitor == newGlMonitor) {
			return;
		}

		glMonitor = newGlMonitor;

		display = std::make_shared<GLDisplay>(glMonitor);
		updatePixelScale();
	}

	void GLWindow::onPosition() {
		updateMonitor();
	}

	void GLWindow::onFocused() {
		cursor->setPosition(InvalidPosition);
	}

	MouseButton mapIntToMouseButton(int button) {
		switch (button) {
		case 0:
			return MouseButton::Left;
		case 1:
			return MouseButton::Right;
		case 2:
			return MouseButton::Middle;
		case 3:
			return MouseButton::Back;
		case 4:
			return MouseButton::Forward;
		default:
			return MouseButton::Left;
		}
	}

	KeyAction mapIntToKeyAction(int action) {
		switch (action) {
		case 0:
			return KeyAction::Release;
		case 1:
			return KeyAction::Press;
		case 2:
			return KeyAction::Repeat;
		default:
			return KeyAction::Release;
		}
	}

	void GLWindow::onMouseButton(int button, int action, int mods) {
		auto event = std::make_shared<MouseButtonEvent>(
			mapIntToMouseButton(button),
			mapIntToKeyAction(action),
			mods
		);
		dispatchEvent(event);
	}

	KeyboardKey mapIntToKeyboardKey(int key) {
		switch (key) {
		case 32:
			return KeyboardKey::Space;
		case 39:
			return KeyboardKey::Apostraphe;
		case 44:
			return KeyboardKey::Comma;
		case 45:
			return KeyboardKey::Minus;
		case 46:
			return KeyboardKey::Period;
		case 47:
			return KeyboardKey::Slash;
		case 48:
			return KeyboardKey::Number0;
		case 161:
			return KeyboardKey::Number1World;
		case 49:
			return KeyboardKey::Number1;
		case 162:
			return KeyboardKey::Number2World;
		case 50:
			return KeyboardKey::Number2;
		case 51:
			return KeyboardKey::Number3;
		case 52:
			return KeyboardKey::Number4;
		case 53:
			return KeyboardKey::Number5;
		case 54:
			return KeyboardKey::Number6;
		case 55:
			return KeyboardKey::Number7;
		case 56:
			return KeyboardKey::Number8;
		case 57:
			return KeyboardKey::Number9;
		case 59:
			return KeyboardKey::Semicolon;
		case 61:
			return KeyboardKey::Equal;
		case 65:
			return KeyboardKey::A;
		case 66:
			return KeyboardKey::B;
		case 67:
			return KeyboardKey::C;
		case 68:
			return KeyboardKey::D;
		case 69:
			return KeyboardKey::E;
		case 70:
			return KeyboardKey::F;
		case 71:
			return KeyboardKey::G;
		case 72:
			return KeyboardKey::H;
		case 73:
			return KeyboardKey::I;
		case 74:
			return KeyboardKey::J;
		case 75:
			return KeyboardKey::K;
		case 76:
			return KeyboardKey::L;
		case 77:
			return KeyboardKey::M;
		case 78:
			return KeyboardKey::N;
		case 79:
			return KeyboardKey::O;
		case 80:
			return KeyboardKey::P;
		case 81:
			return KeyboardKey::Q;
		case 82:
			return KeyboardKey::R;
		case 83:
			return KeyboardKey::S;
		case 84:
			return KeyboardKey::T;
		case 85:
			return KeyboardKey::U;
		case 86:
			return KeyboardKey::V;
		case 87:
			return KeyboardKey::W;
		case 88:
			return KeyboardKey::X;
		case 89:
			return KeyboardKey::Y;
		case 90:
			return KeyboardKey::Z;
		case 91:
			return KeyboardKey::LeftBracket;
		case 92:
			return KeyboardKey::Backslash;
		case 93:
			return KeyboardKey::RightBracket;
		case 96:
			return KeyboardKey::GraveAccent;
		case 256:
			return KeyboardKey::Escape;
		case 257:
			return KeyboardKey::Enter;
		case 258:
			return KeyboardKey::Tab;
		case 259:
			return KeyboardKey::Backspace;
		case 260:
			return KeyboardKey::Insert;
		case 261:
			return KeyboardKey::Delete;
		case 262:
			return KeyboardKey::Right;
		case 263:
			return KeyboardKey::Left;
		case 264:
			return KeyboardKey::Down;
		case 265:
			return KeyboardKey::Up;
		case 266:
			return KeyboardKey::PageUp;
		case 267:
			return KeyboardKey::PageDown;
		case 268:
			return KeyboardKey::Home;
		case 269:
			return KeyboardKey::End;
		case 280:
			return KeyboardKey::CapsLock;
		case 281:
			return KeyboardKey::ScrollLock;
		case 282:
			return KeyboardKey::NumLock;
		case 283:
			return KeyboardKey::PrintScreen;
		case 284:
			return KeyboardKey::Pause;
		case 290:
			return KeyboardKey::F1;
		case 291:
			return KeyboardKey::F2;
		case 292:
			return KeyboardKey::F3;
		case 293:
			return KeyboardKey::F4;
		case 294:
			return KeyboardKey::F5;
		case 295:
			return KeyboardKey::F6;
		case 296:
			return KeyboardKey::F7;
		case 297:
			return KeyboardKey::F8;
		case 298:
			return KeyboardKey::F9;
		case 299:
			return KeyboardKey::F10;
		case 300:
			return KeyboardKey::F11;
		case 301:
			return KeyboardKey::F12;
		case 302:
			return KeyboardKey::F13;
		case 303:
			return KeyboardKey::F14;
		case 304:
			return KeyboardKey::F15;
		case 305:
			return KeyboardKey::F16;
		case 306:
			return KeyboardKey::F17;
		case 307:
			return KeyboardKey::F18;
		case 308:
			return KeyboardKey::F19;
		case 309:
			return KeyboardKey::F20;
		case 310:
			return KeyboardKey::F21;
		case 311:
			return KeyboardKey::F22;
		case 312:
			return KeyboardKey::F23;
		case 313:
			return KeyboardKey::F24;
		case 314:
			return KeyboardKey::F25;
		case 320:
			return KeyboardKey::KP0;
		case 321:
			return KeyboardKey::KP1;
		case 322:
			return KeyboardKey::KP2;
		case 323:
			return KeyboardKey::KP3;
		case 324:
			return KeyboardKey::KP4;
		case 325:
			return KeyboardKey::KP5;
		case 326:
			return KeyboardKey::KP6;
		case 327:
			return KeyboardKey::KP7;
		case 328:
			return KeyboardKey::KP8;
		case 329:
			return KeyboardKey::KP9;
		case 330:
			return KeyboardKey::KPDecimal;
		case 331:
			return KeyboardKey::KPDivide;
		case 332:
			return KeyboardKey::KPMultiply;
		case 333:
			return KeyboardKey::KPSubtract;
		case 334:
			return KeyboardKey::KPAdd;
		case 335:
			return KeyboardKey::KPEnter;
		case 336:
			return KeyboardKey::KPEqual;
		case 340:
			return KeyboardKey::LeftShift;
		case 341:
			return KeyboardKey::LeftControl;
		case 342:
			return KeyboardKey::LeftAlt;
		case 343:
			return KeyboardKey::LeftSuper;
		case 344:
			return KeyboardKey::RightShift;
		case 345:
			return KeyboardKey::RightControl;
		case 346:
			return KeyboardKey::RightAlt;
		case 347:
			return KeyboardKey::RightSuper;
		case 348:
			return KeyboardKey::Menu;
		default:
			return KeyboardKey::Unknown;
		}
	}

	void GLWindow::onKeyboard(int key, int scancode, int action, int mods) {
		auto event = std::make_shared<KeyboardEvent>(
			mapIntToKeyboardKey(key),
			scancode,
			mapIntToKeyAction(action),
			mods
		);
		dispatchEvent(event);
	}

	void GLWindow::onChar(unsigned int codepoint) {
		auto event = std::make_shared<CharEvent>(codepoint);
		dispatchEvent(event);
	}

	void GLWindow::onMouseMove(double x, double y) {
		cursor->setPosition({ (float)x, (float)y });

		auto event = std::make_shared<MouseMoveEvent>(x, y);
		dispatchEvent(event);
	}

	void GLWindow::onScroll(double xOffset, double yOffset) {
		auto event = std::make_shared<ScrollEvent>(xOffset, yOffset);

		dispatchEvent(event);
	}
}

