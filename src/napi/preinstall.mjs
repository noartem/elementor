import * as util from "util";
import {readFile, writeFile} from "fs/promises";
import {exec as lameExec} from "child_process";

const exec = util.promisify(lameExec);

const BUILD_DIR_PATH_PREFIX = "../../../";

const {stdout: libElementorInfo} = await exec("xmake show -t elementor");
const libElementorPath = libElementorInfo
    .split("\n")
    .find((e) => e.includes("targetfile"))
    .split(": ")[1]
    .trim()
    .split("\x1B")[0];

const bindingFileValue = (await readFile("binding.template.gyp"))
    .toString()
    .replaceAll("$libElementor", `${BUILD_DIR_PATH_PREFIX}${libElementorPath}`);

await writeFile("binding.gyp", bindingFileValue, {flag: "w"});
