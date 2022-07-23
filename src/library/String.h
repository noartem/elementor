//
// Created by noartem on 23.07.2022.
//

#ifndef ELEMENTOR_STRING_H
#define ELEMENTOR_STRING_H

#include <string>
#include <locale>
#include <codecvt>

namespace elementor {
    template <typename T> std::string toUTF8(std::basic_string<T, std::char_traits<T>, std::allocator<T>>& source) {
        std::wstring_convert<std::codecvt_utf8_utf16<T>, T> convertor;
        std::string result = convertor.to_bytes(source);
        return result;
    }

    template <typename T> void fromUTF8(std::string& source, std::basic_string<T, std::char_traits<T>, std::allocator<T>>& result) {
        std::wstring_convert<std::codecvt_utf8_utf16<T>, T> convertor;
        result = convertor.from_bytes(source);
    }
}

#endif //ELEMENTOR_STRING_H