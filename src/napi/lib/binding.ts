const addon = require("../build/Release/elementor-native");

interface IElementorNative {
  greet(strName: string): string;
}

class Elementor {
  constructor(name: string) {
    this._addonInstance = new addon.Elementor(name);
  }

  greet(strName: string) {
    return this._addonInstance.greet(strName);
  }

  // private members
  private _addonInstance: IElementorNative;
}

export = Elementor;
