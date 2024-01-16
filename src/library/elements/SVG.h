//
// Created by noartem on 30.07.2022.
//

#ifndef ELEMENTOR_SVG_H
#define ELEMENTOR_SVG_H

#include "../include.h"

#include <include/core/SkData.h>
#include <include/core/SkImage.h>
#include <include/core/SkStream.h>
#include <modules/svg/include/SkSVGDOM.h>

namespace elementor::elements {
	struct SVGProps {
		std::optional<sk_sp<SkSVGDOM>> fromDOM = std::nullopt;
		std::optional<sk_sp<SkData>> fromData;
		std::optional<std::string> src;
	};

	class SVG : public Element {
	public:
		explicit SVG(const std::shared_ptr<ApplicationContext>& ctx)
			: Element(ctx) {
		}

		SVG(const std::shared_ptr<ApplicationContext>& ctx, const SVGProps& props)
			: Element(ctx) {
			if (props.fromDOM.has_value()) fromSkSVGDOM(props.fromDOM.value());
			if (props.fromData.has_value()) fromSkData(props.fromData.value());
			if (props.src.has_value()) fromPath(props.src.value());
		}

		static std::shared_ptr<SVG> New(
			const std::shared_ptr<ApplicationContext>& ctx,
			const SVGProps& props
		) {
			return std::make_shared<SVG>(ctx, props);
		}

		static std::shared_ptr<SVG> New(const std::shared_ptr<ApplicationContext>& ctx) {
			return New(ctx, {});
		}

		sk_sp<SkSVGDOM> getSkSVGDOM() const {
			return skSVGDOM;
		}

		void fromSkSVGDOM(const sk_sp<SkSVGDOM>& newSkSVGDOM) {
			skSVGDOM = newSkSVGDOM;
		}

		void fromSkStream(SkStream& stream);

		void fromSkData(sk_sp<SkData> data);

		void fromPath(const std::string& path);

		void fromString(const char value[]);

		void paintBackground(SkCanvas* canvas, const ElementRect& rect) override;

	private:
		sk_sp<SkSVGDOM> skSVGDOM;
		sk_sp<SkImage> skImage;
	};
}


#endif //ELEMENTOR_SVG_H
