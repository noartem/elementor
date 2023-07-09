import {writeFile} from "node:fs/promises";
import bindingGyp from "./binding.gyp.mjs";
import bindings from "./bindings.mjs";

const bindingGypString = JSON.stringify(bindingGyp, null, '\t')
await writeFile("binding.gyp", bindingGypString, {flag: "w"});

await writeFile("src/elementor.h", bindings.header, {flag: "w"});
await writeFile("src/elementor.cpp", bindings.source, {flag: "w"});
