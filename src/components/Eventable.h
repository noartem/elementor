//
// Created by noartem on 02.02.2023.
//

#ifndef ELEMENTOR_COMPONENTS_EVENTABLE_H
#define ELEMENTOR_COMPONENTS_EVENTABLE_H

#include "utility.h"
#include "elementor.h"

namespace elementor::components {
	struct EventableProps {
		std::vector<std::shared_ptr<EventHandler>> events;
		std::vector<std::shared_ptr<EventHandler>> globalEvents;
		const std::shared_ptr<Element>& child = nullptr;
	};

	class Eventable : public Component, public WithEventsHandlers, public WithGlobalEventsHandlers {
	public:
		explicit Eventable(const std::shared_ptr<ApplicationContext>& ctx, const EventableProps& props)
			: Component(ctx) {
			events = props.events;
			globalEvents = props.globalEvents;

			setChild(props.child);
		}

		static std::shared_ptr<Eventable> New(
			const std::shared_ptr<ApplicationContext>& ctx,
			const EventableProps& props
		) {
			return std::make_shared<Eventable>(ctx, props);
		}

		static std::shared_ptr<Eventable> New(const std::shared_ptr<ApplicationContext>& ctx) {
			return New(ctx, {});
		}

		void setChild(const std::shared_ptr<Element>& child) {
			element = child;
		}

		std::vector<std::shared_ptr<EventHandler>> getEventsHandlers() override {
			return events;
		}

		std::vector<std::shared_ptr<EventHandler>> getGlobalEventsHandlers() override {
			return globalEvents;
		}

	private:
		std::vector<std::shared_ptr<EventHandler>> events;
		std::vector<std::shared_ptr<EventHandler>> globalEvents;
	};
}

#endif //ELEMENTOR_COMPONENTS_EVENTABLE_H
