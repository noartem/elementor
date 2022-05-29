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
5. Check out examples
    ```bash
    xmake run examples
    ```

## TODO

* Examples gallery - все в одном месте, переключение по клику
* Если скролл x и y, то друг на друга
* Scroll на зажатие и перемещение thumb -> перемещать скролл
* Перенести элементы в отедльный namespace
* Flex Wrap alignment
* Text
    * TextLine = text + text formatting options
    * Textable: text() => TextLine
    * Label just draw TextLine the simple way
    * Fix label memory leak
* Image?
* BoxShadow? - `#include <include/utils/SkShadowUtils.h>`
* Debug
* UI elements: beauty button, text input with text selection
