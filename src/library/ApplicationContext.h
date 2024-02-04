//
// Created by noartem on 12.01.2024.
//

#ifndef ELEMENTOR_APPLICATION_CONTEXT_H
#define ELEMENTOR_APPLICATION_CONTEXT_H

#include <memory>
#include <functional>
#include <string_view>

#include "Event.h"
#include "WindowContext.h"
#include "PlatformContext.h"

namespace elementor {
	class ApplicationContext {
	public:
		virtual std::shared_ptr<WindowContext> getWindowCtx() = 0;

		virtual std::shared_ptr<PlatformContext> getPlatformCtx() = 0;
	};
};


#endif //ELEMENTOR_APPLICATION_CONTEXT_H
