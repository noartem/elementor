import {exec} from "./utils/index.mjs";

const projectOut = await exec("xmake lua project-json.lua");
const project = JSON.parse(projectOut.stdout.toString());

export default project

export const packages = project.packages
export const targets = project.targets
export const mode = project.mode