export interface Size {
  width: number;
  height: number;
}

export interface Boundaries {
  min: Size;
  max: Size;
}

export interface Position {
  x: number;
  y: number;
}

export interface ElementRect {
  size: Size;
  position: Position;
  visibleSize: Size;
  visiblePosition: Position;
  inParentPosition: Position;
}

export interface RenderElement {
  element: Element;
  position: Position;
  size: Size;
}

export enum ClipBehavior {
  None,
  Hard,
  AntiAlias,
}

export interface ApplicationContext {
  getPixelScale(): number;

  setPixelScale(scale: number): void;

  getLocale(): string;

  setLocale(locale: string): void;

  getClipboard(): Clipboard;

  requestNextFrame(callback: () => void): void;

  makeWindow(size: Size): Window;
}

export interface Canvas {}

export interface Element {
  getSize(
    ctx: ApplicationContext,
    window: Window,
    boundaries: Boundaries,
  ): Size;

  paintBackground(
    ctx: ApplicationContext,
    window: Window,
    canvas: Canvas,
    rect: ElementRect,
  ): void;

  getChildren(
    ctx: ApplicationContext,
    window: Window,
    rect: ElementRect,
  ): Array<RenderElement>;

  getClipBehaviour(): ClipBehavior;
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
