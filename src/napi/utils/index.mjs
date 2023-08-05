import {writeFile} from "node:fs/promises";
import {promisify} from "util";
import {exec as _exec} from "child_process";
import exp from "constants";

export const exec = promisify(_exec);

export const withCatch = (callback) => async (...args) => {
    try {
        return await callback(...args)
    } catch (e) {
        return null
    }
}

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

export function upper(value) {
    value = value.trim()
    if (!value) {
        return ""
    }

    return value[0].toUpperCase() + value.slice(1)
}

export function lower(value) {
    value = value.trim()
    if (!value) {
        return ""
    }

    return value[0].toLowerCase() + value.slice(1)
}

export const stringify = (e) => JSON.stringify(e, null, "\t");

export const write = (file, value) => writeFile(file, value, {flag: "w"})

export function toArray(value) {
    if (Array.isArray(value)) {
        return value
    } else if (value === undefined || value === null) {
        return []
    } else {
        return [value]
    }
}

export const toSnakeCase = e => lower(e).replace(/[A-Z]/g, e => `_${e.toLowerCase()}`);
