//
// Created by noartem on 11.07.23.
//

#ifndef ELEMENTOR_TO_NAPI_H
#define ELEMENTOR_TO_NAPI_H

#include "elementor.h"
#include "library.h"

#include <napi.h>


Napi::Value to_napi(Napi::Env env, Napi::Value value) {
    return value;
}

Napi::Value to_napi(Napi::Env env, const std::string &value) {
    return Napi::String::New(env, value);
}

Napi::Value to_napi(Napi::Env env, float value) {
    return Napi::Number::New(env, value);
}

Napi::Value to_napi(Napi::Env env, int value) {
    return Napi::Number::New(env, value);
}

Napi::Value to_napi(Napi::Env env, Size value) {
    auto obj = Napi::Object::New(env);
    obj.Set("width", value.width);
    obj.Set("height", value.height);
    return obj;
}

Napi::Value to_napi(Napi::Env env, Position value) {
    auto obj = Napi::Object::New(env);
    obj.Set("x", value.x);
    obj.Set("y", value.y);
    return obj;
}

Napi::Value to_napi(Napi::Env env, std::shared_ptr<Element> value) {
    auto elementConstructor = NNativeElement::GetClass(env);
    auto wrapped = Napi::External<std::shared_ptr<Element>>::New(env, &value);
    return elementConstructor.New({wrapped});
}

Napi::Value to_napi(Napi::Env env, RenderElement value) {
    auto obj = Napi::Object::New(env);
    obj.Set("element", to_napi(env, value.element));
    obj.Set("position", to_napi(env, value.position));
    obj.Set("size", to_napi(env, value.size));
    return obj;
}

template<typename T>
Napi::Value to_napi(Napi::Env env, std::optional <T> value) {
    if (value) {
        return to_napi(env, value.value());
    } else {
        return env.Null();
    }
}

template<typename T>
Napi::Value to_napi(Napi::Env env, std::vector <T> items) {
    auto array = Napi::Array::New(env, items.size());
    for (size_t i = 0; i < items.size(); i++) {
        array[i] = to_napi(env, items[i]);
    }
    return array;
}

#endif //ELEMENTOR_TO_NAPI_H
