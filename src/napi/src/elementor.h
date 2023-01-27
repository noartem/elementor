#pragma once

#include <napi.h>

class Elementor : public Napi::ObjectWrap<Elementor>
{
public:
    Elementor(const Napi::CallbackInfo&);
    Napi::Value Greet(const Napi::CallbackInfo&);

    static Napi::Function GetClass(Napi::Env);

private:
    std::string _greeterName;
};
