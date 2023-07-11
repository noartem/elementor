//
// Created by noartem on 11.07.23.
//

#ifndef ELEMENTOR_TO_NAPI_H
#define ELEMENTOR_TO_NAPI_H

#include "elementor.h"
#include "library.h"

#include <napi.h>


Napi::Value to_napi_string(Napi::Env env, const std::string &value) {
    return Napi::String::New(env, value);
}

Napi::Value to_napi_float(Napi::Env env, float value) {
    return Napi::Number::New(env, value);
}

Napi::Value to_napi_size(Napi::Env env, Size value) {
    auto obj = Napi::Object::New(env);
    obj.Set("width", value.width);
    obj.Set("height", value.height);
    return obj;
}

Napi::Value to_napi_size(Napi::Env env, std::optional<Size> value) {
    if (value) {
        return to_napi_size(env, value.value());
    } else {
        return env.Null();
    }
}

#endif //ELEMENTOR_TO_NAPI_H
