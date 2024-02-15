//
// Created by noartem on 26.07.2022.
//

#ifndef ELEMENTOR_IMAGE_H
#define ELEMENTOR_IMAGE_H

#include "../include.h"

#include <include/core/SkData.h>
#include <include/core/SkImage.h>
#include <include/core/SkSamplingOptions.h>

namespace elementor::elements {
	struct ImageProps {
		std::optional <sk_sp<SkImage>> fromImage = std::nullopt;
		std::optional <sk_sp<SkData>> fromData = std::nullopt;
		std::optional <std::string> src = std::nullopt;
		SkSamplingOptions samplingOptions = SkSamplingOptions(SkCubicResampler::Mitchell());
	};

	class Image : public Element {
	public:
		explicit Image(const std::shared_ptr <ApplicationContext>& ctx)
			: Element(ctx) {
		}

		Image(const std::shared_ptr <ApplicationContext>& ctx, const ImageProps& props)
			: Element(ctx) {
			if (props.fromImage.has_value()) fromSkImage(props.fromImage.value());
			if (props.fromData.has_value()) fromSkData(props.fromData.value());
			if (props.src.has_value()) fromPath(props.src.value());
			setSamplingOptions(samplingOptions);
		}

		static std::shared_ptr <Image> New(
			const std::shared_ptr <ApplicationContext>& ctx,
			const ImageProps& props
		) {
			return std::make_shared<Image>(ctx, props);
		}

		static std::shared_ptr <Image> New(
			const std::shared_ptr <ApplicationContext>& ctx,
			std::shared_ptr <Image>& elementRef,
			const ImageProps& props
		) {
			auto element = New(ctx, props);
			elementRef = element;
			return element;
		}

		static std::shared_ptr <Image> New(const std::shared_ptr <ApplicationContext>& ctx) {
			return New(ctx, {});
		}

		sk_sp <SkImage> getSkImage() const {
			return skImage;
		}

		void fromSkImage(const sk_sp <SkImage>& newSkImage) {
			markChanged();
			skImage = newSkImage;
		}

		void fromSkData(const sk_sp <SkData>& data) {
			fromSkImage(SkImage::MakeFromEncoded(data));
		}

		void fromPath(const std::string& path) {
			fromSkImage(makeImageFromFile(path));
		}

		SkSamplingOptions getSamplingOptions() const {
			return samplingOptions;
		}

		void setSamplingOptions(const SkSamplingOptions& newSamplingOptions) {
			markChanged();
			samplingOptions = newSamplingOptions;
		}

		void paintBackground(SkCanvas* canvas, const ElementRect& rect) override;

		Size getSize(const Boundaries& boundaries) override;

	private:
		sk_sp <SkImage> skImage;
		SkSamplingOptions samplingOptions;

		sk_sp <SkImage> makeImageFromFile(const std::string& path);
	};
}


#endif //ELEMENTOR_IMAGE_H
