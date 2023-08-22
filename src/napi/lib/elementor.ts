const {
  NNativeElement,
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

import {
  Size,
  Boundaries,
  Position,
  ElementRect,
  RenderElement,
  ClipBehavior,
  ApplicationContext,
  Canvas,
  Element,
  Window,
  Clipboard,
} from "./types";

export class NativeElement extends NNativeElement implements Element {
  public getSize(
    ctx: ApplicationContext,
    window: Window,
    boundaries: Boundaries,
  ): Size {
    return super.getSize(ctx, window, boundaries);
  }

  public paintBackground(
    ctx: ApplicationContext,
    window: Window,
    canvas: Canvas,
    rect: ElementRect,
  ) {
    super.paintBackground(ctx, window, canvas, rect);
    return this;
  }

  public getChildren(
    ctx: ApplicationContext,
    window: Window,
    rect: ElementRect,
  ): Array<RenderElement> {
    return super.getChildren(ctx, window, rect);
  }

  public getClipBehaviour(): ClipBehavior {
    return super.getClipBehaviour();
  }
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

export class Padding extends NPadding implements Element {
  public getSize(
    ctx: ApplicationContext,
    window: Window,
    boundaries: Boundaries,
  ): Size {
    return super.getSize(ctx, window, boundaries);
  }

  public paintBackground(
    ctx: ApplicationContext,
    window: Window,
    canvas: Canvas,
    rect: ElementRect,
  ) {
    super.paintBackground(ctx, window, canvas, rect);
    return this;
  }

  public getChildren(
    ctx: ApplicationContext,
    window: Window,
    rect: ElementRect,
  ): Array<RenderElement> {
    return super.getChildren(ctx, window, rect);
  }

  public getClipBehaviour(): ClipBehavior {
    return super.getClipBehaviour();
  }

  public getChild(): Element {
    return super.getChild();
  }

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

export class Background extends NBackground implements Element {
  public getSize(
    ctx: ApplicationContext,
    window: Window,
    boundaries: Boundaries,
  ): Size {
    return super.getSize(ctx, window, boundaries);
  }

  public paintBackground(
    ctx: ApplicationContext,
    window: Window,
    canvas: Canvas,
    rect: ElementRect,
  ) {
    super.paintBackground(ctx, window, canvas, rect);
    return this;
  }

  public getChildren(
    ctx: ApplicationContext,
    window: Window,
    rect: ElementRect,
  ): Array<RenderElement> {
    return super.getChildren(ctx, window, rect);
  }

  public getClipBehaviour(): ClipBehavior {
    return super.getClipBehaviour();
  }

  public getChild(): Element {
    return super.getChild();
  }

  public setChild(child: Element) {
    super.setChild(child);
    return this;
  }

  public setColor(color: string) {
    super.setColor(color);
    return this;
  }
}

export class Rounded extends NRounded implements Element {
  public getSize(
    ctx: ApplicationContext,
    window: Window,
    boundaries: Boundaries,
  ): Size {
    return super.getSize(ctx, window, boundaries);
  }

  public paintBackground(
    ctx: ApplicationContext,
    window: Window,
    canvas: Canvas,
    rect: ElementRect,
  ) {
    super.paintBackground(ctx, window, canvas, rect);
    return this;
  }

  public getChildren(
    ctx: ApplicationContext,
    window: Window,
    rect: ElementRect,
  ): Array<RenderElement> {
    return super.getChildren(ctx, window, rect);
  }

  public getClipBehaviour(): ClipBehavior {
    return super.getClipBehaviour();
  }

  public getChild(): Element {
    return super.getChild();
  }

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

export class Row extends NRow implements Element {
  public getSize(
    ctx: ApplicationContext,
    window: Window,
    boundaries: Boundaries,
  ): Size {
    return super.getSize(ctx, window, boundaries);
  }

  public paintBackground(
    ctx: ApplicationContext,
    window: Window,
    canvas: Canvas,
    rect: ElementRect,
  ) {
    super.paintBackground(ctx, window, canvas, rect);
    return this;
  }

  public getChildren(
    ctx: ApplicationContext,
    window: Window,
    rect: ElementRect,
  ): Array<RenderElement> {
    return super.getChildren(ctx, window, rect);
  }

  public getClipBehaviour(): ClipBehavior {
    return super.getClipBehaviour();
  }

  public appendChild(child: Element) {
    super.appendChild(child);
    return this;
  }

  public getSpacing(): number {
    return super.getSpacing();
  }

  public setSpacing(spacing: number) {
    super.setSpacing(spacing);
    return this;
  }
}

export class Flex extends NFlex implements Element {
  public getSize(
    ctx: ApplicationContext,
    window: Window,
    boundaries: Boundaries,
  ): Size {
    return super.getSize(ctx, window, boundaries);
  }

  public paintBackground(
    ctx: ApplicationContext,
    window: Window,
    canvas: Canvas,
    rect: ElementRect,
  ) {
    super.paintBackground(ctx, window, canvas, rect);
    return this;
  }

  public getChildren(
    ctx: ApplicationContext,
    window: Window,
    rect: ElementRect,
  ): Array<RenderElement> {
    return super.getChildren(ctx, window, rect);
  }

  public getClipBehaviour(): ClipBehavior {
    return super.getClipBehaviour();
  }

  public appendChild(child: Element) {
    super.appendChild(child);
    return this;
  }

  public getSpacing(): number {
    return super.getSpacing();
  }

  public setSpacing(spacing: number) {
    super.setSpacing(spacing);
    return this;
  }
  appendFlexible(value: Element) {
    return this.appendChild(new Flexible().setChild(value));
  }
}

export class Flexible extends NFlexible implements Element {
  public getSize(
    ctx: ApplicationContext,
    window: Window,
    boundaries: Boundaries,
  ): Size {
    return super.getSize(ctx, window, boundaries);
  }

  public paintBackground(
    ctx: ApplicationContext,
    window: Window,
    canvas: Canvas,
    rect: ElementRect,
  ) {
    super.paintBackground(ctx, window, canvas, rect);
    return this;
  }

  public getChildren(
    ctx: ApplicationContext,
    window: Window,
    rect: ElementRect,
  ): Array<RenderElement> {
    return super.getChildren(ctx, window, rect);
  }

  public getClipBehaviour(): ClipBehavior {
    return super.getClipBehaviour();
  }

  public getChild(): Element {
    return super.getChild();
  }

  public setChild(child: Element) {
    super.setChild(child);
    return this;
  }

  public getGrow(): number {
    return super.getGrow();
  }

  public setGrow(grow: number) {
    super.setGrow(grow);
    return this;
  }
}

export class Width extends NWidth implements Element {
  public getSize(
    ctx: ApplicationContext,
    window: Window,
    boundaries: Boundaries,
  ): Size {
    return super.getSize(ctx, window, boundaries);
  }

  public paintBackground(
    ctx: ApplicationContext,
    window: Window,
    canvas: Canvas,
    rect: ElementRect,
  ) {
    super.paintBackground(ctx, window, canvas, rect);
    return this;
  }

  public getChildren(
    ctx: ApplicationContext,
    window: Window,
    rect: ElementRect,
  ): Array<RenderElement> {
    return super.getChildren(ctx, window, rect);
  }

  public getClipBehaviour(): ClipBehavior {
    return super.getClipBehaviour();
  }

  public getChild(): Element {
    return super.getChild();
  }

  public setChild(child: Element) {
    super.setChild(child);
    return this;
  }

  public getWidth(): number {
    return super.getWidth();
  }

  public setWidth(width: number) {
    super.setWidth(width);
    return this;
  }
}

export class Height extends NHeight implements Element {
  public getSize(
    ctx: ApplicationContext,
    window: Window,
    boundaries: Boundaries,
  ): Size {
    return super.getSize(ctx, window, boundaries);
  }

  public paintBackground(
    ctx: ApplicationContext,
    window: Window,
    canvas: Canvas,
    rect: ElementRect,
  ) {
    super.paintBackground(ctx, window, canvas, rect);
    return this;
  }

  public getChildren(
    ctx: ApplicationContext,
    window: Window,
    rect: ElementRect,
  ): Array<RenderElement> {
    return super.getChildren(ctx, window, rect);
  }

  public getClipBehaviour(): ClipBehavior {
    return super.getClipBehaviour();
  }

  public getChild(): Element {
    return super.getChild();
  }

  public setChild(child: Element) {
    super.setChild(child);
    return this;
  }

  public getHeight(): number {
    return super.getHeight();
  }

  public setHeight(height: number) {
    super.setHeight(height);
    return this;
  }
}

export class Center extends NCenter implements Element {
  public getSize(
    ctx: ApplicationContext,
    window: Window,
    boundaries: Boundaries,
  ): Size {
    return super.getSize(ctx, window, boundaries);
  }

  public paintBackground(
    ctx: ApplicationContext,
    window: Window,
    canvas: Canvas,
    rect: ElementRect,
  ) {
    super.paintBackground(ctx, window, canvas, rect);
    return this;
  }

  public getChildren(
    ctx: ApplicationContext,
    window: Window,
    rect: ElementRect,
  ): Array<RenderElement> {
    return super.getChildren(ctx, window, rect);
  }

  public getClipBehaviour(): ClipBehavior {
    return super.getClipBehaviour();
  }

  public getChild(): Element {
    return super.getChild();
  }

  public setChild(child: Element) {
    super.setChild(child);
    return this;
  }
}

export class Text extends NText implements Element {
  public getSize(
    ctx: ApplicationContext,
    window: Window,
    boundaries: Boundaries,
  ): Size {
    return super.getSize(ctx, window, boundaries);
  }

  public paintBackground(
    ctx: ApplicationContext,
    window: Window,
    canvas: Canvas,
    rect: ElementRect,
  ) {
    super.paintBackground(ctx, window, canvas, rect);
    return this;
  }

  public getChildren(
    ctx: ApplicationContext,
    window: Window,
    rect: ElementRect,
  ): Array<RenderElement> {
    return super.getChildren(ctx, window, rect);
  }

  public getClipBehaviour(): ClipBehavior {
    return super.getClipBehaviour();
  }

  public getText(): string {
    return super.getText();
  }

  public setText(text: string) {
    super.setText(text);
    return this;
  }

  public setFontColor(fontColor: string) {
    super.setFontColor(fontColor);
    return this;
  }

  public getFontSize(): number {
    return super.getFontSize();
  }

  public setFontSize(fontSize: number) {
    super.setFontSize(fontSize);
    return this;
  }

  public getFontSkew(): number {
    return super.getFontSkew();
  }

  public setFontSkew(fontSkew: number) {
    super.setFontSkew(fontSkew);
    return this;
  }

  public getFontScale(): number {
    return super.getFontScale();
  }

  public setFontScale(fontScale: number) {
    super.setFontScale(fontScale);
    return this;
  }

  public getFontFamily(): string {
    return super.getFontFamily();
  }

  public setFontFamily(fontFamily: string) {
    super.setFontFamily(fontFamily);
    return this;
  }
}
