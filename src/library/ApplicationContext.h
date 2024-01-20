//
// Created by noartem on 12.01.2024.
//

#ifndef ELEMENTOR_APPLICATION_CONTEXT_H
#define ELEMENTOR_APPLICATION_CONTEXT_H

#include "WindowContext.h"
#include "PlatformContext.h"

namespace elementor {
	class ApplicationContext {
	public:
		virtual std::shared_ptr<WindowContext> getWindowCtx() = 0;

		virtual std::shared_ptr<PlatformContext> getPlatformCtx() = 0;

		virtual int addEventListener(
			const std::string_view& eventName,
			const std::function<void(const std::shared_ptr<Event>& event)>& eventListener
		) = 0;

		virtual void removeEventListener(const std::string_view& name, int eventListenerId) = 0;
	};
};


#endif //ELEMENTOR_APPLICATION_CONTEXT_H
