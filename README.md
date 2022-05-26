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

* INT_MAX -> inf
* Scroll
    * Исправить scroll на тачпаде
    * Добавить scrollbar
        * Scrollbar child всегда Scroll
        * С помощью scrollHeight/scrollTop определять положение thumb
        * Рисовать один track для vertical/horizontal, оба если Both
        * setTrack(Element *trackElement) - может быть NULL, тогда нет track, default: ScrollbarTrack
        * setThumb(Element *thumbElement) - не NULL, default: ScrollbarThumb
        * где рисовать, над контентом или вместе с ним - занимая пространство
          ScrollbarPosition::InContent, ScrollbarPosition::OnTop
        * Показывать только когда есть возможность скролить (default)  или всегда
* Examples gallery - все в одном месте, переключение по клику
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
* UI elements: beaty button, text input with text selection
