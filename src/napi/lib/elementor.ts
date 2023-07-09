const {
  NGLPlatform,
  NPadding,
  NBackground,
  NRounded,
} = require("../build/Release/elementor.node");

export interface Size {
  width: number;
  height: number;
}

export interface Clipboard {
  get(): string;

  set(value: string): void;
}

export interface Window {
  setTitle(value: string): void;

  setMinSize(value: Size): void;

  setMaxSize(value: Size): void;

  setRoot(value: Element): void;

  getClipboard(): Clipboard;
}

export class GLPlatform extends NGLPlatform {
  makeWindow(size: Size): Window {
    return super.makeWindow(size);
  }

  run() {
    super.run();
  }
}

export class Padding extends NPadding {
  setPaddings(top: number, right?: number, bottom?: number, left?: number) {
    right ??= top;
    bottom ??= top;
    left ??= right;
    super.setPaddings(top, right, bottom, left);
    return this;
  }

  setChild(value: Element) {
    super.setChild(value);
    return this;
  }
}

export class Background extends NBackground {
  setColor(value: string) {
    super.setColor(value);
    return this;
  }

  setChild(value: Element) {
    super.setChild(value);
    return this;
  }
}

export class Rounded extends NRounded {
  setRadius(
    topLeft: number,
    topRight?: number,
    bottomRight?: number,
    bottomLeft?: number,
  ) {
    topRight ??= topLeft;
    bottomRight ??= topRight;
    bottomLeft ??= topLeft;
    super.setRadius(topLeft, topRight, bottomRight, bottomLeft);
    return this;
  }

  setChild(value: Element) {
    super.setChild(value);
    return this;
  }
}

export type Element = typeof Padding | typeof Background;
