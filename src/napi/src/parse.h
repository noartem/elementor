//
// Created by noartem on 08.07.23.
//

#ifndef ELEMENTOR_PARSE_H
#define ELEMENTOR_PARSE_H

#include "elementor.h"
#include "library.h"

#include <napi.h>
#include <tl/expected.hpp>

enum class parse_error {
    expected_object,
    expected_number,
    expected_string,
    expected_external,
    expected_function,
    wrong_type,
    missing_property,
};

std::string parse_error_to_string(parse_error error) {
    switch (error) {
        case parse_error::expected_object:
            return "expected object";
        case parse_error::expected_number:
            return "expected number";
        case parse_error::expected_string:
            return "expected string";
        case parse_error::expected_external:
            return "expected external";
        case parse_error::expected_function:
            return "expected function";
        case parse_error::wrong_type:
            return "wrong type";
        case parse_error::missing_property:
            return "missing property";
    }
}

tl::expected <float, parse_error> parse_napi_float(const Napi::Value &value) {
    if (!value.IsNumber()) {
        return tl::unexpected(parse_error::expected_number);
    }

    return value.As<Napi::Number>().FloatValue();
}

tl::expected <std::string, parse_error> parse_napi_string(const Napi::Value &value) {
    if (!value.IsString()) {
        return tl::unexpected(parse_error::expected_string);
    }

    return value.As<Napi::String>().Utf8Value();
}

tl::expected <Size, parse_error> parse_napi_size(const Napi::Value &value) {
    if (!value.IsObject()) {
        return tl::unexpected(parse_error::expected_object);
    }

    auto obj = value.As<Napi::Object>();
    if (!obj.Has("width") || !obj.Has("height")) {
        return tl::unexpected(parse_error::missing_property);
    }

    auto width = obj.Get("width");
    auto height = obj.Get("height");

    if (!width.IsNumber() || !height.IsNumber()) {
        return tl::unexpected(parse_error::expected_number);
    }

    return Size{
            .width = width.As<Napi::Number>().FloatValue(),
            .height = height.As<Napi::Number>().FloatValue()
    };
}

template<typename T>
tl::expected <T, parse_error> parse_napi_external(const Napi::Value &value) {
    if (!value.IsExternal()) {
        return tl::unexpected(parse_error::expected_external);
    }

    auto external = value.As < Napi::External < T>>();
    if (external.Data() == nullptr) {
        return tl::unexpected(parse_error::wrong_type);
    }

    return *external.Data();
}

tl::expected <std::shared_ptr<Element>, parse_error> parse_napi_element(Napi::Env env, const Napi::Value &value) {
    if (!value.IsObject()) {
        return tl::unexpected(parse_error::expected_object);
    }

    auto obj = value.As<Napi::Object>();

    if (!obj.Has("getInstance")) {
        return tl::unexpected(parse_error::missing_property);
    }

    auto instanceMethod = obj.Get("getInstance");
    if (!instanceMethod.IsFunction()) {
        return tl::unexpected(parse_error::expected_function);
    }

    auto instance = instanceMethod.As<Napi::Function>().MakeCallback(obj, {});
    if (!instance.IsExternal()) {
        return tl::unexpected(parse_error::expected_external);
    }

    return parse_napi_external<std::shared_ptr<Element>>(instance);
}

#endif //ELEMENTOR_PARSE_H
