import {writeFile} from "node:fs/promises";
import {BindingsGenerator} from "./utils/bindings-generator.mjs";

import bindingGyp from "./binding.gyp.mjs";
import bindings from "./bindings.mjs";
import {toLines} from "./utils/cpp-parser.mjs";

const bindingGypString = JSON.stringify(bindingGyp, null, "\t");
await writeFile("binding.gyp", bindingGypString, {flag: "w"});

const bindingsGenerator = new BindingsGenerator(bindings);
await writeFile("src/elementor.h", bindingsGenerator.header, {flag: "w"});
await writeFile("src/elementor.cpp", bindingsGenerator.source, {flag: "w"});

Object.values(bindings).forEach(e => Object.values(e.methods).forEach(e => e.body = toLines(e.body ?? '')))
const bindingsString = JSON.stringify(bindings, null, "\t");
await writeFile("bindings.debug.json", bindingsString, {flag: "w"});
