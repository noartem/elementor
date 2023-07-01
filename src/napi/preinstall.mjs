import {writeFile} from "fs/promises";
import bindingGyp from "./binding.gyp.mjs";

const bindingGypString = JSON.stringify(bindingGyp, null, '\t')
await writeFile("binding.gyp", bindingGypString, {flag: "w"});
