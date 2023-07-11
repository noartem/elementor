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

export function isObject(value) {
    return typeof value === "object" && !Array.isArray(value);
}

export function merge(...objects) {
    const objectsReversed = [...objects].reverse();
    const keys = uniq(objects.flatMap((e) => Object.keys(e)));
    return Object.fromEntries(
        keys.map((key) => {
            let value = objectsReversed.find((e) => key in e)[key];
            const valuesObjects = objects
                .filter((e) => key in e)
                .map((e) => e[key])
                .filter(isObject);

            if (valuesObjects.length >= 2) {
                value = merge(...valuesObjects);
            }

            return [key, value];
        }),
    );
}

export const upper = (str) => str[0].toUpperCase() + str.slice(1);
