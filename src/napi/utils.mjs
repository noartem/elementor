import util from "util";
import {exec as lameExec} from "child_process";

export const exec = util.promisify(lameExec);

export function uniq(items) {
    const result = []
    for (const item of items) {
        if (!result.includes(item)) {
            result.push(item)
        }
    }
    return result
}