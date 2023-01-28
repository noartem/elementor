const { NGLPlatform, NGLClipboard } = require("../build/Release/elementor");

interface NativePlatform {
  getClipboard(): NativeClipboard;
}

interface NativeClipboard {
  get(): string;
  set(value: string): void;
}

export class Platform {
  private instance: NativePlatform;
  private _clipboard?: Clipboard;

  constructor() {
    this.instance = new NGLPlatform();
  }

  get clipboard() {
    this._clipboard ??= new Clipboard(this.instance.getClipboard());
    return this._clipboard;
  }
}

export class Clipboard {
  private instance: NativeClipboard;

  constructor(instance?: NativeClipboard) {
    this.instance = instance ?? new NGLClipboard();
  }

  get() {
    return this.instance.get();
  }

  set(value: string) {
    return this.instance.set(value);
  }
}
