//
// Created by noartem on 13.04.2022.
//

#include "Border.h"

#include <include/core/SkPath.h>
#include <include/core/SkPathEffect.h>
#include <include/core/SkRRect.h>
#include <include/effects/SkDashPathEffect.h>
#include <include/effects/Sk1DPathEffect.h>

namespace elementor::elements {
	Size Border::getSize(const Boundaries& boundaries) {
		if (doesNotHaveChild()) {
			return boundaries.max;
		}

		auto pixelScale = ctx->getPixelScale();
		float widthScaled = width * pixelScale;

		Boundaries childBoundaries = {
			.min = {
				.width = std::max(boundaries.min.width - 2 * widthScaled, 0.0f),
				.height = std::max(boundaries.min.height - 2 * widthScaled, 0.0f),
			},
			.max = {
				.width = std::max(boundaries.max.width - 2 * widthScaled, 0.0f),
				.height = std::max(boundaries.max.height - 2 * widthScaled, 0.0f)
			}
		};

		Size childSize = child->getSize(childBoundaries);

		Size elementSize = {
			.width = childSize.width + 2 * widthScaled,
			.height = childSize.height + 2 * widthScaled
		};

		return elementSize;
	}

	SkPaint Border::makeSkPaint() {
		auto pixelScale = ctx->getPixelScale();
		float widthScaled = width * pixelScale;

		SkPaint paint;
		paint.setColor(color);
		paint.setStrokeWidth(widthScaled);
		paint.setStyle(SkPaint::kStroke_Style);
		paint.setAntiAlias(true);

		if (style == BorderStyle::Dotted) {
			SkPath path;
			path.addOval(SkRect::MakeWH(widthScaled / 2, widthScaled / 2));
			auto pathEffect = SkPath1DPathEffect::Make(path, widthScaled, 0.0f, SkPath1DPathEffect::kRotate_Style);
			paint.setPathEffect(pathEffect);
		}

		if (style == BorderStyle::Dashed) {
			const SkScalar intervals[] = { 10.0f, 5.0f };
			auto pathEffect = SkDashPathEffect::Make(intervals, 2, 0.0f);
			paint.setPathEffect(pathEffect);
		}

		return paint;
	}

	SkRRect Border::makeSkRRect(const ElementRect& rect) {
		auto pixelScale = ctx->getPixelScale();
		float radiusXScaled = radiusX * pixelScale;
		float radiusYScaled = radiusY * pixelScale;
		float widthScaled = width * pixelScale;

		auto skPaint = makeSkPaint();

		SkRect skRect = SkRect::MakeXYWH(widthScaled / 2, widthScaled / 2, rect.size.width - widthScaled, rect.size.height - widthScaled);
		SkRRect skRRect = SkRRect::MakeRectXY(skRect, radiusXScaled, radiusYScaled);

		return skRRect;
	}

	void Border::paintBackground(SkCanvas* canvas, const ElementRect& rect) {
		canvas->drawRRect(makeSkRRect(rect), makeSkPaint());
	}

	std::vector <ElementWithRect> Border::getChildren(const ElementRect& rect) {
		if (doesNotHaveChild()) {
			return {};
		}

		auto pixelScale = ctx->getPixelScale();
		float widthScaled = width * pixelScale;

		Rect childRect = {
			.size = {
				.width = rect.size.width - 2 * widthScaled,
				.height = rect.size.height - 2 * widthScaled
			},
			.position = {
				.x = widthScaled,
				.y = widthScaled
			}
		};

		ElementWithRect childElement(child, childRect);
		return { childElement };
	}
}
