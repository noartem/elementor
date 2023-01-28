#pragma once

#include <napi.h>

#include "../../library/include.h"
#include "../../library/animation/include.h"
#include "../../library/platforms/gl/include.h"
#include "../../library/elements/include.h"

using namespace elementor;
using namespace elementor::elements;

class NGLPlatform : public Napi::ObjectWrap<NGLPlatform>
{
public:
    NGLPlatform(const Napi::CallbackInfo&);
    static Napi::Function GetClass(Napi::Env);
    Napi::Value getClipboard(const Napi::CallbackInfo&);
private:
    GLPlatform *platform;
};

class NGLClipboard : public Napi::ObjectWrap<NGLClipboard>
{
public:
    NGLClipboard(const Napi::CallbackInfo&, GLClipboard *clipboard);
    NGLClipboard(const Napi::CallbackInfo&);
    static Napi::Function GetClass(Napi::Env);
    Napi::Value get(const Napi::CallbackInfo&);
    Napi::Value set(const Napi::CallbackInfo&);
private:
    GLClipboard *clipboard;
};
