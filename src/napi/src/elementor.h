#pragma once

#include "library.h"

#include <napi.h>

class NGLPlatform : public Napi::ObjectWrap<NGLPlatform> {
public:
    NGLPlatform(const Napi::CallbackInfo &info);

    static Napi::Function GetClass(Napi::Env);

    Napi::Value getInstance(const Napi::CallbackInfo &info);

    Napi::Value makeWindow(const Napi::CallbackInfo &info);

    Napi::Value run(const Napi::CallbackInfo &info);

private:
    std::shared_ptr <GLPlatform> instance;
};

class NGLWindow : public Napi::ObjectWrap<NGLWindow> {
public:
    NGLWindow(const Napi::CallbackInfo &info);

    static Napi::Function GetClass(Napi::Env);

    Napi::Value getInstance(const Napi::CallbackInfo &info);

    Napi::Value setTitle(const Napi::CallbackInfo &info);

    Napi::Value setMinSize(const Napi::CallbackInfo &info);

    Napi::Value setMaxSize(const Napi::CallbackInfo &info);

    Napi::Value setRoot(const Napi::CallbackInfo &info);

private:
    std::shared_ptr <GLWindow> instance;
};

class NGLClipboard : public Napi::ObjectWrap<NGLClipboard> {
public:
    NGLClipboard(const Napi::CallbackInfo &info);

    static Napi::Function GetClass(Napi::Env);

    Napi::Value getInstance(const Napi::CallbackInfo &info);

    Napi::Value get(const Napi::CallbackInfo &info);

    Napi::Value set(const Napi::CallbackInfo &info);

private:
    std::shared_ptr <GLClipboard> instance;
};

class NPadding : public Napi::ObjectWrap<NPadding> {
public:
    NPadding(const Napi::CallbackInfo &info);

    static Napi::Function GetClass(Napi::Env);

    Napi::Value getInstance(const Napi::CallbackInfo &info);

    Napi::Value setPaddings(const Napi::CallbackInfo &info);

    Napi::Value setChild(const Napi::CallbackInfo &info);

private:
    std::shared_ptr <Padding> instance;
};


class NBackground : public Napi::ObjectWrap<NBackground> {
public:
    NBackground(const Napi::CallbackInfo &info);

    static Napi::Function GetClass(Napi::Env);

    Napi::Value getInstance(const Napi::CallbackInfo &info);

    Napi::Value setColor(const Napi::CallbackInfo &info);

    Napi::Value setChild(const Napi::CallbackInfo &info);

private:
    std::shared_ptr <Background> instance;
};