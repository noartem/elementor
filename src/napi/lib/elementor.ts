const {
  NGLPlatform,
  NPadding,
  NBackground,
  NRounded,
  NRow,
  NFlex,
  NFlexible,
  NWidth,
  NCenter,
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

export class Row extends NRow {
  setSpacing(spacing: number) {
    super.setSpacing(spacing);
    return this;
  }

  appendChild(value: Element) {
    super.appendChild(value);
    return this;
  }
}

export class Flex extends NFlex {
  setSpacing(spacing: number) {
    super.setSpacing(spacing);
    return this;
  }

  appendChild(value: Element) {
    super.appendChild(value);
    return this;
  }

  appendFlexible(value: Element) {
    return this.appendChild(new Flexible().setChild(value));
  }
}

export class Flexible extends NFlexible {
  setChild(value: Element) {
    super.setChild(value);
    return this;
  }
}

export class Width extends NWidth {
  setWidth(width: number) {
    super.setWidth(width);
    return this;
  }

  setChild(value: Element) {
    super.setChild(value);
    return this;
  }
}

export class Center extends NCenter {
  setChild(value: Element) {
    super.setChild(value);
    return this;
  }
}

export type Element =
  | Padding
  | Background
  | Rounded
  | Row
  | Flex
  | Flexible
  | Width
  | Center;
