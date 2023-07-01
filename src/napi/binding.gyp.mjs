import * as util from "util";
import {exec as lameExec} from "child_process";
import * as path from 'path'

export const exec = util.promisify(lameExec);

const BUILD_DIR_PATH_PREFIX = `..${path.sep}..${path.sep}..${path.sep}`;

const projectOut = await exec("xmake lua project-json.lua");
const {packages, targets} = JSON.parse(projectOut.stdout.toString())

const getTargetLibFile = target => {
    const targetFilePath = path.parse(`${BUILD_DIR_PATH_PREFIX}${target.targetfile}`)
    return `${targetFilePath.dir}${path.sep}release${path.sep}${targetFilePath.name}`
}

const isBinaryTarget = target => target.kind === 'binary'

const isNotBinaryTarget = target => !isBinaryTarget(target)

export default {
    targets: [{
        target_name: 'elementor',
        sources: ['src/elementor.cpp'],
        libraries: [
            ...targets.filter(isNotBinaryTarget).map(getTargetLibFile),
            ...packages.flatMap(e => e.libfiles).filter(Boolean),
            ...packages.flatMap(e => e.syslinks).filter(Boolean)
        ],
        include_dirs: [
            `<!@(node -p "require('node-addon-api').include")`,
            ...packages.map(e => e.includedirs).filter(Boolean),
        ],
        dependencies: ["<!(node -p \"require('node-addon-api').gyp\")"],
        defines: ['NAPI_CPP_EXCEPTIONS'],
        cflags: ['-fexceptions', '-fPIC'],
        cflags_cc: ['-fexceptions', '-std=c++17', '-fPIC'],
        xcode_settings: {
            GCC_ENABLE_CPP_EXCEPTIONS: 'YES',
            CLANG_CXX_LIBRARY: 'libc++',
            MACOSX_DEPLOYMENT_TARGET: '10.7'
        },
        msvs_settings: {
            VCCLCompilerTool: {ExceptionHandling: 1},
        },
    }]
}
