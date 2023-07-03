const {NGLPlatform, NGLClipboard} = require("../build/Release/elementor");

interface Clipboard {
    get(): string;

    set(value: string): void;
}

interface Platform {
    getClipboard(): Clipboard;
}

export class GLPlatform {
    private instance: Platform;
    private _clipboard?: Clipboard;

    constructor() {
        this.instance = new NGLPlatform();
    }

    get clipboard() {
        this._clipboard ??= new GLClipboard(this.instance.getClipboard());
        return this._clipboard;
    }
}

export class GLClipboard {
    private instance: Clipboard;

    constructor(instance?: Clipboard) {
        this.instance = instance ?? new NGLClipboard();
    }

    get() {
        return this.instance.get();
    }

    set(value: string) {
        return this.instance.set(value);
    }
}
