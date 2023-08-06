const {
  NGLPlatform,
  NPadding,
  NBackground,
  NRounded,
  NRow,
  NFlex,
  NFlexible,
  NWidth,
  NHeight,
  NCenter,
  NText,
} = require("../build/Release/elementor.node");

export interface Size {
  width: number;
  height: number;
}

export interface Window {
  getTitle(): string;
  setTitle(title: string): void;
  getMinSize(): Size;
  setMinSize(minSize: Size): void;
  getMaxSize(): Size;
  setMaxSize(maxSize: Size): void;
  setRoot(root: Element): void;
}

export interface Clipboard {
  get(): string;
  set(value: string): void;
}

export class GLPlatform extends NGLPlatform {
  public makeWindow(size: Size): Window {
    return super.makeWindow(size);
  }

  public run() {
    super.run();
    return this;
  }
}

export class Padding extends NPadding {
  public setChild(child: Element) {
    super.setChild(child);
    return this;
  }

  public setPaddings(top: number, right: number, bottom: number, left: number) {
    super.setPaddings(top, right, bottom, left);
    return this;
  }
  set(top: number, right?: number, bottom?: number, left?: number) {
    right ??= top;
    bottom ??= top;
    left ??= right;
    return this.setPaddings(top, right, bottom, left);
  }
}

export class Background extends NBackground {
  public setChild(child: Element) {
    super.setChild(child);
    return this;
  }

  public setColor(color: string) {
    super.setColor(color);
    return this;
  }
}

export class Rounded extends NRounded {
  public setChild(child: Element) {
    super.setChild(child);
    return this;
  }

  public setRadius(
    topLeft: number,
    topRight: number,
    bottomRight: number,
    bottomLeft: number,
  ) {
    super.setRadius(topLeft, topRight, bottomRight, bottomLeft);
    return this;
  }
  set(
    topLeft: number,
    topRight?: number,
    bottomRight?: number,
    bottomLeft?: number,
  ) {
    topRight ??= topLeft;
    bottomRight ??= topRight;
    bottomLeft ??= topLeft;
    return this.setRadius(topLeft, topRight, bottomRight, bottomLeft);
  }
}

export class Row extends NRow {
  public appendChild(child: Element) {
    super.appendChild(child);
    return this;
  }

  public setSpacing(spacing: number) {
    super.setSpacing(spacing);
    return this;
  }
}

export class Flex extends NFlex {
  public appendChild(child: Element) {
    super.appendChild(child);
    return this;
  }

  public setSpacing(spacing: number) {
    super.setSpacing(spacing);
    return this;
  }
  appendFlexible(value: Element) {
    return this.appendChild(new Flexible().setChild(value));
  }
}

export class Flexible extends NFlexible {
  public setChild(child: Element) {
    super.setChild(child);
    return this;
  }

  public setGrow(grow: number) {
    super.setGrow(grow);
    return this;
  }
}

export class Width extends NWidth {
  public setChild(child: Element) {
    super.setChild(child);
    return this;
  }

  public setWidth(width: number) {
    super.setWidth(width);
    return this;
  }
}

export class Height extends NHeight {
  public setChild(child: Element) {
    super.setChild(child);
    return this;
  }

  public setHeight(height: number) {
    super.setHeight(height);
    return this;
  }
}

export class Center extends NCenter {
  public setChild(child: Element) {
    super.setChild(child);
    return this;
  }
}

export class Text extends NText {
  public setText(text: string) {
    super.setText(text);
    return this;
  }

  public setFontColor(fontColor: string) {
    super.setFontColor(fontColor);
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
  | Height
  | Center
  | Text;
