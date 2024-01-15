//
// Created by noartem on 27.04.2022.
//

#ifndef ELEMENTOR_BORDER_H
#define ELEMENTOR_BORDER_H

#include "../include.h"

namespace elementor::elements {
	enum class BorderStyle {
		Solid,
		Dotted,
		Dashed,
	};

	struct BorderProps {
		std::optional<float> radiusX = std::nullopt;
		std::optional<float> radiusY = std::nullopt;
		float radius = 0;
		float width = 1;
		const std::string_view& color = "";
		BorderStyle style = BorderStyle::Solid;
		const std::shared_ptr<Element>& child = nullptr;
	};

	class Border : public Element, public WithChild {
	public:
		explicit Border(const std::shared_ptr<ApplicationContext>& ctx)
			: Element(ctx), WithChild() {
		}

		Border(const std::shared_ptr<ApplicationContext>& ctx, const BorderProps& props)
			: Element(ctx),
			  WithChild(props.child) {
			setRadius(
				props.radiusX.value_or(props.radius),
				props.radiusY.value_or(props.radius)
			);
			setWidth(props.width);
			setStyle(props.style);
			setColor(props.color);
		}

		static std::shared_ptr<Border> New(
			const std::shared_ptr<ApplicationContext>& ctx,
			const BorderProps& props
		) {
			return std::make_shared<Border>(ctx, props);
		}

		static std::shared_ptr<Border> New(const std::shared_ptr<ApplicationContext>& ctx) {
			return New(ctx, {});
		}

		[[nodiscard]] SkColor getColor() const {
			return color;
		}

		void setColor(SkColor skColor) {
			color = skColor;
		}

		void setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
			setColor(makeSkColorFromRGBA(r, g, b, a));
		}

		void setColor(uint8_t r, uint8_t g, uint8_t b) {
			setColor(makeSkColorFromRGB(r, g, b));
		}

		void setColor(const std::string_view& hex) {
			setColor(makeSkColorFromHex(std::string(hex)));
		}

		[[nodiscard]] float getWidth() const {
			return width;
		}

		void setWidth(float newWidth) {
			width = newWidth;
		}

		[[nodiscard]] float getRadiusX() const {
			return radiusX;
		}

		[[nodiscard]] float getRadiusY() const {
			return radiusY;
		}

		void setRadius(float newRadiusX, float newRadiusY) {
			radiusX = newRadiusX;
			radiusY = newRadiusY;
		}

		void setRadius(float radiusXY) {
			setRadius(radiusXY, radiusXY);
		}

		[[nodiscard]] BorderStyle getStyle() const {
			return style;
		}

		void setStyle(BorderStyle newStyle) {
			style = newStyle;
		}

		Size getSize(const Boundaries& boundaries) override;

		void paintBackground(SkCanvas* canvas, const ElementRect& rect) override;

		std::vector<ElementWithRect> getChildren(const ElementRect& rect) override;

	private:
		float width = 0.0;
		float radiusX = 0.0;
		float radiusY = 0.0;
		SkColor color;
		BorderStyle style = BorderStyle::Solid;

		SkPaint makeSkPaint();
		SkRRect makeSkRRect(const ElementRect& rect);
	};

	std::shared_ptr<Border> border();
}


#endif //ELEMENTOR_BORDER_H
