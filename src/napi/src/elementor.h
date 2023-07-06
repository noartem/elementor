#pragma once

#include <napi.h>
#include "library.h"

// TODO: Fix tests - got double free error when running on linux.
//       Need to test creating just element, maybe double-free related to GLFW

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
