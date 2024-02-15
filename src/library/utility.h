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
	template<typename T>
	std::string toUTF8(std::basic_string <T, std::char_traits<T>, std::allocator<T>>& source) {
		std::wstring_convert <std::codecvt_utf8_utf16<T>, T> convertor;
		std::string result = convertor.to_bytes(source);
		return result;
	}

	template<typename T>
	void fromUTF8(const std::string& source, std::basic_string <T, std::char_traits<T>, std::allocator<T>>& result) {
		std::wstring_convert <std::codecvt_utf8_utf16<T>, T> convertor;
		result = convertor.from_bytes(source);
	}

	template<typename T>
	bool optionalEquals(const std::optional <T>& a, const std::optional <T>& b) {
		if (a.has_value() != b.has_value()) return false;
		if (!a.has_value()) return true;
		return a.value() == b.value();
	}

	SkColor makeSkColorFromRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

	SkColor makeSkColorFromRGB(uint8_t r, uint8_t g, uint8_t b);

	SkColor makeSkColorFromHex(std::string hex);
};


#endif //ELEMENTOR_UTILITY_H
