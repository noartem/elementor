export function toLines(code) {
    if (Array.isArray(code)) {
        return code.map(e => e.trim())
    }

    return code
        .trim()
        .split("\n")
        .map(e => e.trim());
}

export function hasReturn(code) {
    return code.split('\n').some(line => line.trim().startsWith('return'))
}

export function singleLine(code) {
    return !code.trim().includes('\n')
}