#include "elementor.h"
#include "parse.h"

#include <napi.h>
#include <tl/expected.hpp>

NGLPlatform::NGLPlatform(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    this->instance = std::make_shared<GLPlatform>();
}

Napi::Function NGLPlatform::GetClass(Napi::Env env) {
    return DefineClass(env, "NGLPlatform", {
            NGLPlatform::InstanceMethod("getInstance", &NGLPlatform::getInstance),
            NGLPlatform::InstanceMethod("makeWindow", &NGLPlatform::makeWindow),
            NGLPlatform::InstanceMethod("run", &NGLPlatform::run),
    });
}

Napi::Value NGLPlatform::getInstance(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    return Napi::External < std::shared_ptr < GLPlatform >> ::New(env, &this->instance).As<Napi::Value>();
}

Napi::Value NGLPlatform::makeWindow(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1) {
        Napi::TypeError::New(env, "Platform makeWindow: Excepted one argument").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    auto size = parse_napi_size(info[0]);
    if (!size.has_value()) {
        Napi::TypeError::New(env, "Platform makeWindow: " +
                                  parse_error_to_string(size.error())).ThrowAsJavaScriptException();
        return env.Undefined();
    }

    auto window = this->instance->makeWindow(size.value());
    window->setMinSize(size.value());

    auto windowConstructor = NGLWindow::GetClass(env);
    auto wrapped = Napi::External < std::shared_ptr < GLWindow >> ::New(env, &window);
    return windowConstructor.New({wrapped});
}

Napi::Value NGLPlatform::run(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    this->instance->run();

    return env.Undefined();
}

NGLWindow::NGLWindow(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1) {
        Napi::TypeError::New(env, "GLWindow: Excepted one argument").ThrowAsJavaScriptException();
        return;
    }

    auto window = parse_napi_external<std::shared_ptr < GLWindow>>
    (info[0]);
    if (!window.has_value()) {
        Napi::TypeError::New(env, "GLWindow: " + parse_error_to_string(window.error())).ThrowAsJavaScriptException();
        return;
    }

    this->instance = window.value();
}

Napi::Function NGLWindow::GetClass(Napi::Env env) {
    return DefineClass(env, "NGLWindow", {
            NGLWindow::InstanceMethod("getInstance", &NGLWindow::getInstance),
            NGLWindow::InstanceMethod("setTitle", &NGLWindow::setTitle),
            NGLWindow::InstanceMethod("setMinSize", &NGLWindow::setMinSize),
            NGLWindow::InstanceMethod("setMaxSize", &NGLWindow::setMaxSize),
            NGLWindow::InstanceMethod("setRoot", &NGLWindow::setRoot),
    });
}

Napi::Value NGLWindow::setTitle(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1) {
        Napi::TypeError::New(env, "GLWindow setTitle: Excepted one argument").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    auto title = parse_napi_string(info[0]);
    if (!title.has_value()) {
        Napi::TypeError::New(env,
                             "GLWindow setTitle: " + parse_error_to_string(title.error())).ThrowAsJavaScriptException();
        return env.Undefined();
    }

    this->instance->setTitle(title.value());

    return env.Undefined();
}

Napi::Value NGLWindow::setMinSize(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1) {
        Napi::TypeError::New(env, "GLWindow setMinSize: Excepted one argument").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    auto size = parse_napi_size(info[0]);
    if (!size.has_value()) {
        Napi::TypeError::New(env, "GLWindow setMinSize: " +
                                  parse_error_to_string(size.error())).ThrowAsJavaScriptException();
        return env.Undefined();
    }

    this->instance->setMinSize(size.value());

    return env.Undefined();
}

Napi::Value NGLWindow::setMaxSize(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1) {
        Napi::TypeError::New(env, "GLWindow setMaxSize: Excepted one argument").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    auto size = parse_napi_size(info[0]);
    if (!size.has_value()) {
        Napi::TypeError::New(env, "GLWindow setMaxSize: " +
                                  parse_error_to_string(size.error())).ThrowAsJavaScriptException();
        return env.Undefined();
    }

    this->instance->setMaxSize(size.value());

    return env.Undefined();
}

Napi::Value NGLWindow::setRoot(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1) {
        Napi::TypeError::New(env, "GLWindow setRoot: Excepted one argument").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    auto element = parse_napi_element(env, info[0]);
    if (!element.has_value()) {
        Napi::TypeError::New(env,
                             "GLWindow setRoot: " +
                             parse_error_to_string(element.error())).ThrowAsJavaScriptException();
        return env.Undefined();
    }

    this->instance->setRoot(element.value());

    return env.Undefined();
}

Napi::Value NGLWindow::getInstance(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    return Napi::External < std::shared_ptr < GLWindow >> ::New(env, &this->instance).As<Napi::Value>();
}

NGLClipboard::NGLClipboard(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    if (info.Length() == 1 && info[0].IsExternal()) {
        this->instance = *info[0].As < Napi::External < std::shared_ptr < GLClipboard>>>().Data();
        return;
    }

    this->instance = std::make_shared<GLClipboard>();
}

Napi::Function NGLClipboard::GetClass(Napi::Env env) {
    return DefineClass(env, "NGLClipboard", {
            NGLClipboard::InstanceMethod("getInstance", &NGLClipboard::getInstance),
            NGLClipboard::InstanceMethod("get", &NGLClipboard::get),
            NGLClipboard::InstanceMethod("set", &NGLClipboard::set),
    });
}

Napi::Value NGLClipboard::getInstance(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    return Napi::External < std::shared_ptr < GLClipboard >> ::New(env, &this->instance).As<Napi::Value>();
}

Napi::Value NGLClipboard::get(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    return Napi::String::New(env, this->instance->get());
}

Napi::Value NGLClipboard::set(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1) {
        Napi::TypeError::New(env, "Clipboard set: Excepted one argument").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    if (!info[0].IsString()) {
        Napi::TypeError::New(env, "Clipboard set: First argument wrong type").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    this->instance->set(info[0].As<Napi::String>().Utf8Value());

    return env.Undefined();
}

NPadding::NPadding(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    if (info.Length() == 1 && info[0].IsExternal()) {
        this->instance = *info[0].As < Napi::External < std::shared_ptr < Padding>>>().Data();
        return;
    }

    this->instance = std::make_shared<Padding>();
}

Napi::Function NPadding::GetClass(Napi::Env env) {
    return DefineClass(env, "NPadding", {
            NPadding::InstanceMethod("getInstance", &NPadding::getInstance),
            NPadding::InstanceMethod("setPaddings", &NPadding::setPaddings),
            NPadding::InstanceMethod("setChild", &NPadding::setChild),
    });
}

Napi::Value NPadding::getInstance(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    return Napi::External < std::shared_ptr < Padding >> ::New(env, &this->instance).As<Napi::Value>();
}

Napi::Value NPadding::setPaddings(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    auto len = info.Length();
    if (len == 0) {
        Napi::TypeError::New(env, "Padding setPaddings: Excepted one argument").ThrowAsJavaScriptException();
    } else if (len == 1) {
        auto paddingYX = parse_napi_float(info[0]);
        if (!paddingYX.has_value()) {
            Napi::TypeError::New(env, "Padding setPaddings: " +
                                      parse_error_to_string(paddingYX.error())).ThrowAsJavaScriptException();
            return env.Undefined();
        }

        this->instance->setPaddings(paddingYX.value());
    } else if (len == 2) {
        auto paddingY = parse_napi_float(info[0]);
        if (!paddingY.has_value()) {
            Napi::TypeError::New(env, "Padding setPaddings: " +
                                      parse_error_to_string(paddingY.error())).ThrowAsJavaScriptException();
            return env.Undefined();
        }

        auto paddingX = parse_napi_float(info[1]);
        if (!paddingX.has_value()) {
            Napi::TypeError::New(env, "Padding setPaddings: " +
                                      parse_error_to_string(paddingX.error())).ThrowAsJavaScriptException();
            return env.Undefined();
        }

        this->instance->setPaddings(paddingY.value(), paddingX.value());
    } else if (len == 3) {
        auto paddingTop = parse_napi_float(info[0]);
        if (!paddingTop.has_value()) {
            Napi::TypeError::New(env, "Padding setPaddings: " +
                                      parse_error_to_string(paddingTop.error())).ThrowAsJavaScriptException();
            return env.Undefined();
        }

        auto paddingX = parse_napi_float(info[1]);
        if (!paddingX.has_value()) {
            Napi::TypeError::New(env, "Padding setPaddings: " +
                                      parse_error_to_string(paddingX.error())).ThrowAsJavaScriptException();
            return env.Undefined();
        }

        auto paddingBottom = parse_napi_float(info[0]);
        if (!paddingBottom.has_value()) {
            Napi::TypeError::New(env, "Padding setPaddings: " +
                                      parse_error_to_string(paddingBottom.error())).ThrowAsJavaScriptException();
            return env.Undefined();
        }

        this->instance->setPaddings(paddingTop.value(), paddingX.value(), paddingBottom.value());
    } else if (len == 4) {
        auto paddingTop = parse_napi_float(info[0]);
        if (!paddingTop.has_value()) {
            Napi::TypeError::New(env, "Padding setPaddings: " +
                                      parse_error_to_string(paddingTop.error())).ThrowAsJavaScriptException();
            return env.Undefined();
        }

        auto paddingRight = parse_napi_float(info[1]);
        if (!paddingRight.has_value()) {
            Napi::TypeError::New(env, "Padding setPaddings: " +
                                      parse_error_to_string(paddingRight.error())).ThrowAsJavaScriptException();
            return env.Undefined();
        }

        auto paddingBottom = parse_napi_float(info[0]);
        if (!paddingBottom.has_value()) {
            Napi::TypeError::New(env, "Padding setPaddings: " +
                                      parse_error_to_string(paddingBottom.error())).ThrowAsJavaScriptException();
            return env.Undefined();
        }

        auto paddingLeft = parse_napi_float(info[1]);
        if (!paddingLeft.has_value()) {
            Napi::TypeError::New(env, "Padding setPaddings: " +
                                      parse_error_to_string(paddingLeft.error())).ThrowAsJavaScriptException();
            return env.Undefined();
        }

        this->instance->setPaddings(paddingTop.value(), paddingRight.value(), paddingBottom.value(),
                                    paddingLeft.value());
    }

    return env.Undefined();
}

Napi::Value NPadding::setChild(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1) {
        Napi::TypeError::New(env, "Padding setChild: Excepted one argument").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    auto element = parse_napi_element(env, info[0]);
    if (!element.has_value()) {
        Napi::TypeError::New(env,
                             "Padding setChild: " +
                             parse_error_to_string(element.error())).ThrowAsJavaScriptException();
        return env.Undefined();
    }

    this->instance->setChild(element.value());

    return env.Undefined();
}

NBackground::NBackground(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    if (info.Length() == 1 && info[0].IsExternal()) {
        this->instance = *info[0].As < Napi::External < std::shared_ptr < Background>>>().Data();
        return;
    }

    this->instance = std::make_shared<Background>();
}

Napi::Function NBackground::GetClass(Napi::Env env) {
    return DefineClass(env, "NBackground", {
            NBackground::InstanceMethod("getInstance", &NBackground::getInstance),
            NBackground::InstanceMethod("setColor", &NBackground::setColor),
            NBackground::InstanceMethod("setChild", &NBackground::setChild),
    });
}

Napi::Value NBackground::getInstance(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    return Napi::External < std::shared_ptr < Background >> ::New(env, &this->instance).As<Napi::Value>();
}

Napi::Value NBackground::setColor(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1) {
        Napi::TypeError::New(env, "Background setColor: Excepted one argument").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    auto color = parse_napi_string(info[0]);
    if (!color.has_value()) {
        Napi::TypeError::New(env, "Background setColor: " +
                                  parse_error_to_string(color.error())).ThrowAsJavaScriptException();
        return env.Undefined();
    }

    this->instance->setColor(color.value());

    return env.Undefined();
}

Napi::Value NBackground::setChild(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1) {
        Napi::TypeError::New(env, "Background setChild: Excepted one argument").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    auto element = parse_napi_element(env, info[0]);
    if (!element.has_value()) {
        Napi::TypeError::New(env,
                             "Background setChild: " +
                             parse_error_to_string(element.error())).ThrowAsJavaScriptException();
        return env.Undefined();
    }

    this->instance->setChild(element.value());

    return env.Undefined();
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set(Napi::String::New(env, "NGLPlatform"), NGLPlatform::GetClass(env));
    exports.Set(Napi::String::New(env, "NGLWindow"), NGLWindow::GetClass(env));
    exports.Set(Napi::String::New(env, "NGLClipboard"), NGLClipboard::GetClass(env));
    exports.Set(Napi::String::New(env, "NPadding"), NPadding::GetClass(env));
    exports.Set(Napi::String::New(env, "NBackground"), NBackground::GetClass(env));
    return exports;
}

NODE_API_MODULE(addon, Init
)
