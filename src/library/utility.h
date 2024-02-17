//
// Created by noartem on 07.02.2024.
//

#ifndef ELEMENTOR_UTILITY_H
#define ELEMENTOR_UTILITY_H

#include <string>
#include <locale>
#include <codecvt>
#include <optional>

#include <include/core/SkColor.h>

namespace elementor {
	inline std::string toUTF8(const std::u32string_view& source) {
		std::wstring_convert<std::codecvt_utf8_utf16<char32_t>, char32_t> convertor;
		return convertor.to_bytes(source.data());
	}

	inline std::u32string fromUTF8(const std::string_view& source) {
		std::wstring_convert<std::codecvt_utf8_utf16<char32_t>, char32_t> convertor;
		return convertor.from_bytes(source.data());
	}

	SkColor makeSkColorFromRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

	SkColor makeSkColorFromRGB(uint8_t r, uint8_t g, uint8_t b);

	SkColor makeSkColorFromHex(std::string hex);
};


#endif //ELEMENTOR_UTILITY_H
