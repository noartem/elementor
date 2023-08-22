import {exec, prettifyAST, stringify, withCatch, write} from "./utils/index.mjs";
import {generateBindingsCPP} from "./utils/bindings-cpp-gen.mjs";
import {generateCPPDeclaration, generateCPPRealization,} from "./utils/cpp-gen.mjs";
import {generateBindingsTS} from "./utils/bindings-ts-gen.mjs";
import {generateTS} from "./utils/ts-gen.mjs";

import project from "./project.mjs";
import bindingGyp from "./binding.gyp.mjs";
import bindings from "./bindings/index.mjs";

const bindingsCPP = generateBindingsCPP(bindings);
const bindingsTS = generateBindingsTS(bindings);

await write("binding.gyp", stringify(bindingGyp));

await write("src/elementor.h", generateCPPDeclaration("elementor", bindingsCPP));
await write("src/elementor.cpp", generateCPPRealization("elementor", bindingsCPP));
await withCatch(exec)("clang-format src/elementor.h src/elementor.cpp -i");

await write("lib/elementor.ts", generateTS(bindingsTS));
await withCatch(exec)("npx prettier lib/elementor.ts -w");

await write("project.debug.json", stringify(project));

await write("bindings.debug.json", stringify(bindings));

await write("bindings.debug.json", stringify(bindings));
await write("bindings-cpp.debug.json", stringify(prettifyAST(bindingsCPP)));
await write("bindings-ts.debug.json", stringify(prettifyAST(bindingsTS)));
