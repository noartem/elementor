import {exec, stringify, withCatch, write} from "./utils/index.mjs";
import {generateCpp} from "./utils/bindings-cpp-gen.mjs";
import {generateDeclaration, generateRealization} from "./utils/cpp-gen.mjs";

import bindingGyp from "./binding.gyp.mjs";
import bindings from "./bindings.mjs";

const bindingsCpp = generateCpp(bindings);

await write("binding.gyp", stringify(bindingGyp));

await write("src/elementor.h", generateDeclaration("elementor", bindingsCpp));
await write("src/elementor.cpp", generateRealization("elementor", bindingsCpp));

await withCatch(exec)("clang-format src/elementor.h src/elementor.cpp -i")

await write("bindings.debug.json", stringify(bindings), {flag: "w"});

await write("bindings.debug.json", stringify(bindings));
await write("bindings-cpp.debug.json", stringify(bindingsCpp));
