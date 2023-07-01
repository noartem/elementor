#pragma once

#include <napi.h>
#include "library.h"

class NGLPlatform : public Napi::ObjectWrap<NGLPlatform>
{
public:
    NGLPlatform(const Napi::CallbackInfo&);
    static Napi::Function GetClass(Napi::Env);
    Napi::Value getClipboard(const Napi::CallbackInfo&);
private:
    std::shared_ptr<GLPlatform> platform;
};

class NGLClipboard : public Napi::ObjectWrap<NGLClipboard>
{
public:
    NGLClipboard(const Napi::CallbackInfo&, std::shared_ptr<GLClipboard> clipboard);
    NGLClipboard(const Napi::CallbackInfo&);
    static Napi::Function GetClass(Napi::Env);
    Napi::Value get(const Napi::CallbackInfo&);
    Napi::Value set(const Napi::CallbackInfo&);
private:
    std::shared_ptr<GLClipboard> clipboard;
};
