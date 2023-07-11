
export function throwError(text) {
    if (!text.startsWith('"') && !text.endsWith('"')) {
        text = `"${text}"`
    }

    return `Napi::TypeError::New(env, ${text}).ThrowAsJavaScriptException()`
}

export function newString(from) {
    return `Napi::String::New(env, ${from})`
}