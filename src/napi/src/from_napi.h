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

std::string from_napi_error_to_string(parse_error error) {
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

tl::expected<float, parse_error> from_napi_float(Napi::Env env, const Napi::Value &value) {
    if (!value.IsNumber()) {
        return tl::unexpected(parse_error::expected_number);
    }

    return value.As<Napi::Number>().FloatValue();
}

tl::expected <std::string, parse_error> from_napi_string(Napi::Env env, const Napi::Value &value) {
    if (!value.IsString()) {
        return tl::unexpected(parse_error::expected_string);
    }

    return value.As<Napi::String>().Utf8Value();
}

tl::expected <Size, parse_error> from_napi_size(Napi::Env env, const Napi::Value &value) {
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

tl::expected <Position, parse_error> from_napi_position(Napi::Env env, const Napi::Value &value) {
    if (!value.IsObject()) {
        return tl::unexpected(parse_error::expected_object);
    }

    auto obj = value.As<Napi::Object>();
    if (!obj.Has("x") || !obj.Has("y")) {
        return tl::unexpected(parse_error::missing_property);
    }

    auto x = obj.Get("x");
    auto y = obj.Get("y");

    if (!x.IsNumber() || !y.IsNumber()) {
        return tl::unexpected(parse_error::expected_number);
    }

    return Position{
            .x = x.As<Napi::Number>().FloatValue(),
            .y = y.As<Napi::Number>().FloatValue()
    };
}

tl::expected <Boundaries, parse_error> from_napi_boundaries(Napi::Env env, const Napi::Value &value) {
    if (!value.IsObject()) {
        return tl::unexpected(parse_error::expected_object);
    }

    auto obj = value.As<Napi::Object>();
    if (!obj.Has("min") || !obj.Has("max")) {
        return tl::unexpected(parse_error::missing_property);
    }

    auto _min = from_napi_size(env, obj.Get("min"));
    if (!_min.has_value()) {
        return tl::unexpected(_min.error());
    }
    auto min = _min.value();

    auto _max = from_napi_size(env, obj.Get("max"));
    if (!_max.has_value()) {
        return tl::unexpected(_max.error());
    }
    auto max = _max.value();

    return Boundaries{
            .min = min,
            .max = max
    };
}

tl::expected <Rect, parse_error> from_napi_rect(Napi::Env env, const Napi::Value &value) {
    if (!value.IsObject()) {
        return tl::unexpected(parse_error::expected_object);
    }

    auto obj = value.As<Napi::Object>();
    if (!obj.Has("size") || !obj.Has("position")) {
        return tl::unexpected(parse_error::missing_property);
    }

    auto _size = from_napi_size(env, obj.Get("size"));
    if (!_size.has_value()) {
        return tl::unexpected(_size.error());
    }
    auto size = _size.value();

    auto _position = from_napi_position(env, obj.Get("position"));
    if (!_position.has_value()) {
        return tl::unexpected(_position.error());
    }
    auto position = _position.value();

    return Rect{
            .size = size,
            .position = position
    };
}

tl::expected <ElementRect, parse_error> from_napi_element_rect(Napi::Env env, const Napi::Value &value) {
    if (!value.IsObject()) {
        return tl::unexpected(parse_error::expected_object);
    }

    auto obj = value.As<Napi::Object>();
    if (!obj.Has("size") || !obj.Has("position")) {
        return tl::unexpected(parse_error::missing_property);
    }

    auto _size = from_napi_size(env, obj.Get("size"));
    if (!_size.has_value()) {
        return tl::unexpected(_size.error());
    }
    auto size = _size.value();

    auto _position = from_napi_position(env, obj.Get("position"));
    if (!_position.has_value()) {
        return tl::unexpected(_position.error());
    }
    auto position = _position.value();

    auto _visibleSize = from_napi_size(env, obj.Get("visibleSize"));
    if (!_visibleSize.has_value()) {
        return tl::unexpected(_visibleSize.error());
    }
    auto visibleSize = _visibleSize.value();

    auto _visiblePosition = from_napi_position(env, obj.Get("visiblePosition"));
    if (!_visiblePosition.has_value()) {
        return tl::unexpected(_visiblePosition.error());
    }
    auto visiblePosition = _visiblePosition.value();

    auto _inParentPosition = from_napi_position(env, obj.Get("inParentPosition"));
    if (!_inParentPosition.has_value()) {
        return tl::unexpected(_inParentPosition.error());
    }
    auto inParentPosition = _inParentPosition.value();

    return ElementRect{
            .size = size,
            .position = position,
            .visibleSize = visibleSize,
            .visiblePosition = visiblePosition,
            .inParentPosition = inParentPosition
    };
}

template<typename T>
tl::expected <T, parse_error> from_napi_external(Napi::Env env, const Napi::Value &value) {
    if (!value.IsExternal()) {
        return tl::unexpected(parse_error::expected_external);
    }

    auto external = value.As < Napi::External < T >> ();
    if (external.Data() == nullptr) {
        return tl::unexpected(parse_error::wrong_type);
    }

    return *external.Data();
}

template<typename T>
tl::expected <T, parse_error> from_napi_instanced(Napi::Env env, const Napi::Value &value) {
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

    return from_napi_external<T>(env, instance);
}

tl::expected <std::shared_ptr<Element>, parse_error> from_napi_element(Napi::Env env, const Napi::Value &value) {
    // TODO: Add JS Class to CPP Element
    return from_napi_instanced<std::shared_ptr < Element>>
    (env, value);
}

tl::expected <std::shared_ptr<Window>, parse_error> from_napi_window(Napi::Env env, const Napi::Value &value) {
    return from_napi_instanced<std::shared_ptr < Window>>
    (env, value);
}

tl::expected<SkCanvas *, parse_error> from_napi_canvas(Napi::Env env, const Napi::Value &value) {
    return from_napi_instanced<SkCanvas *>(env, value);
}

tl::expected <std::shared_ptr<ApplicationContext>, parse_error>
from_napi_application_context(Napi::Env env, const Napi::Value &value) {
    return from_napi_instanced<std::shared_ptr < ApplicationContext>>
    (env, value);
}

// TODO: Make an API like to_napi: `parse_error from_napi(Napi::Env env, const Napi::Value &value, T element)`

#endif //ELEMENTOR_PARSE_H
