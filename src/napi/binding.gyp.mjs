import {toArray, uniq} from "./utils/index.mjs";
import * as path from "path";
import {mode, packages, targets} from "./project.mjs";

const BUILD_DIR_PATH_PREFIX = `..${path.sep}..${path.sep}..${path.sep}`;

const getTargetLibFile = (target) => {
    const targetFilePath = path.parse(BUILD_DIR_PATH_PREFIX + target.targetfile);
    return [targetFilePath.dir, mode, targetFilePath.base].join(path.sep);
};

const isBinaryTarget = (target) => target.kind === "binary";

const isNotBinaryTarget = (target) => !isBinaryTarget(target);

export default {
    targets: [
        {
            target_name: "elementor",
            sources: ["src/elementor.cpp"],
            libraries: uniq([
                ...targets.filter(isNotBinaryTarget).map(getTargetLibFile),
                ...packages.flatMap((e) => e.libfiles).filter(Boolean),
                ...packages
                    .flatMap((e) => e.syslinks)
                    .filter(Boolean)
                    .map((e) => `-l${e}`),
                ...packages
                    .flatMap((e) =>
                        (e.links ?? []).filter(
                            (l) => !toArray(e.libfiles).some((f) => f.includes(l)),
                        ),
                    )
                    .map((e) => `-l${e}`),
            ]),
            include_dirs: uniq([
                `<!@(node -p "require('node-addon-api').include")`,
                ...packages.flatMap((e) => e.includedirs).filter(Boolean),
            ]),
            dependencies: ["<!(node -p \"require('node-addon-api').gyp\")"],
            defines: ["NAPI_CPP_EXCEPTIONS"],
            cflags: ["-fexceptions", "-fPIC"],
            cflags_cc: ["-fexceptions", "-std=c++17", "-fPIC"],
            xcode_settings: {
                GCC_ENABLE_CPP_EXCEPTIONS: "YES",
                CLANG_CXX_LIBRARY: "libc++",
                MACOSX_DEPLOYMENT_TARGET: "10.7",
            },
            msvs_settings: {
                VCCLCompilerTool: {ExceptionHandling: 1},
            },
        },
    ],
};
