const {NGLPlatform, NPadding, NBackground} = require("../build/Release/elementor.node")

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

export const GLPlatform = NGLPlatform as new () => {
    makeWindow(size: Size): Window;

    run(): void;
}

export const Padding = NPadding as new () => {
    setPaddings(xy: number): void;
    setPaddings(y: number, x: number): void;
    setPaddings(top: number, x: number, bottom: number): void;
    setPaddings(top: number, right: number, bottom: number, left: number): void;
    setChild(value: Element): void;
}

export const Background = NBackground as new () => {
    setColor(value: string): void;
    setChild(value: Element): void;
}

export type Element =
    | typeof Padding
    | typeof Background