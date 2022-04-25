# Elementor

## How to get started

1. Install [XMake](https://xmake.io)
2. Clone project
    ```bash
    git clone https://github.com/noartem/elementor.git
    cd elementor
    ```
3. Fetch project dependencies
    ```bash
    xmake
    ```
4. Build project for your system
    ```bash
    xmake build
    ```
5. Run example
    ```bash
    xmake run elementor-test
    ```

## TODO

* Text
    * TextLine = text + text formatting options
    * Textable: text() => TextLine
    * Label just draw TextLine the simple way
    * Fix label memory leak
* Border
* Flex Wrap
* Image?
* BoxShadow?
* Interactive, Events
* Button
* Scroll
