#include "elementor.h"

NGLPlatform::NGLPlatform(const Napi::CallbackInfo& info) : ObjectWrap(info) {
    this->platform = std::make_shared<GLPlatform>();
}

Napi::Function NGLPlatform::GetClass(Napi::Env env) {
    return DefineClass(env, "NGLPlatform", {
        NGLPlatform::InstanceMethod("getClipboard", &NGLPlatform::getClipboard),
    });
}

Napi::Value NGLPlatform::getClipboard(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    auto clipboardConstructor = NGLClipboard::GetClass(env);
    auto clipboard = this->platform->getClipboard();
    auto wrapped = Napi::External<std::shared_ptr<GLClipboard>>::New(env, &clipboard);
    return clipboardConstructor.New({wrapped});
}

NGLClipboard::NGLClipboard(const Napi::CallbackInfo& info) : ObjectWrap(info) {
    if (info.Length() == 1 && info[0].IsExternal()) {
        this->clipboard = *info[0].As<Napi::External<std::shared_ptr<GLClipboard>>>().Data();
        return;
    }

    this->clipboard = std::make_shared<GLClipboard>();
}

Napi::Function NGLClipboard::GetClass(Napi::Env env) {
    return DefineClass(env, "NGLClipboard", {
        NGLClipboard::InstanceMethod("get", &NGLClipboard::get),
        NGLClipboard::InstanceMethod("set", &NGLClipboard::set),
    });
}

Napi::Value NGLClipboard::get(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    return Napi::String::New(env, this->clipboard->get());
}

Napi::Value NGLClipboard::set(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1) {
        Napi::TypeError::New(env, "Clipbard set: Excepted one argument").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    if (!info[0].IsString()) {
        Napi::TypeError::New(env, "Clipbard set: First argument wrong type").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    this->clipboard->set(info[0].As<Napi::String>().Utf8Value());

    return env.Undefined();
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set(Napi::String::New(env, "NGLPlatform"), NGLPlatform::GetClass(env));
    exports.Set(Napi::String::New(env, "NGLClipboard"), NGLClipboard::GetClass(env));
    return exports;
}

NODE_API_MODULE(addon, Init)
