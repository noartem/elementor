export const hasReturn = (code) =>
    (code || '').split("\n").some((line) => line.trim().startsWith("return"));

export const isSingleLine = (code) => !(code || '').trim().includes("\n");

export const toLines = (code) =>
    code
        .trim()
        .split("\n")
        .map((e) => e.trim());
