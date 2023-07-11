export function generateMethodRealization(methodData) {

}

export function generateClassRealization(classData) {

}

export function generateRealization({comments, includes = [], classes = [], methods, afterRealization}) {
    let result = [];

    if (comments) {
        result.push(`// ${comments}`);
    }

    if (includes.length > 0) {
        result.push(includes.map(e => `#include "${e}"`));
    }

    for (const className in classes) {
        result.push(generateClassRealization({...classes[className], name: className}));
    }

    for (const methodName in methods) {
        result.push(generateMethodRealization({...methods[methodName], name: methodName}));
    }

    if (afterRealization) {
        result.push(afterRealization);
    }

    return result
        .map(e => Array.isArray(e) ? e.join('\n') : e)
        .join('\n\n')
}