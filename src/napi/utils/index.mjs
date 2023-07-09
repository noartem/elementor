import {promisify} from "util";
import {exec as _exec} from "child_process";

export const exec = promisify(_exec);

export function uniq(items) {
    const result = [];
    for (const item of items) {
        if (!result.includes(item)) {
            result.push(item);
        }
    }
    return result;
}
