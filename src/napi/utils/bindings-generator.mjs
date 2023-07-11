import {realizeMethod} from "./cpp-generator.mjs";
import {BindingClassGenerator} from "./binding-class-generator.mjs";

export class BindingsGenerator {
    #classes = {};

    constructor(bindings) {
        this.#classes = Object.fromEntries(
            Object.entries(bindings).map(([name, data]) => [
                name,
                new BindingClassGenerator(name, data),
            ]),
        );
    }

    get #classesDeclarations() {
        return Object.values(this.#classes).map((e) => e.declaration);
    }

    get #classesRealizations() {
        return Object.values(this.#classes).map((e) => e.realization);
    }

    get #classesNames() {
        return Object.keys(this.#classes);
    }

    get header() {
        return `// generated by src/napi/bindings.mjs
#pragma once

#include "library.h"

#include <napi.h>

${this.#classesDeclarations.join("\n\n\n")}
`;
    }

    get #moduleExportsRealization() {
        return realizeMethod({
            name: "Init",
            args: ["Napi::Env env", "Napi::Object exports"],
            returns: "Napi::Object",
            body: `
                ${this.#classesNames
                .map(
                    (e) =>
                        `exports.Set(Napi::String::New(env, "N${e}"), N${e}::GetClass(env));`,
                )
                .join(`\n`)}
                return exports;
            `,
        });
    }

    get source() {
        return `// generated by src/napi/bindings.mjs
#include "elementor.h"
#include "from_napi.h"
#include "to_napi.h"

#include <napi.h>
#include <tl/expected.hpp>

${this.#classesRealizations.join("\n\n")}

${this.#moduleExportsRealization}

NODE_API_MODULE(addon, Init)
`;
    }
}
