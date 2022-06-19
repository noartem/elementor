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

* Image
* Paragraph
    * Как это делать в skia?
    * Если Text -> брать из него font, paint
    * Если не Text, то вставлять как прямоугольник посреди текста (Если такое можно)
* Transform
* Text font fallback (например, fallback для эмодзи)
* Примеры для:
    * Padding
    * Label
    * Rounded
    * Border
    * Element
    * Clickable
    * Hoverable
    * List
        * Column
        * Row
    * Scroll
        * Scrollable
        * Scrollbar
* Scroll issues:
    * Исправить если скролл и x и y, то друг наслаиваются на друга
    * Добавить scroll на зажатие и перемещение thumb -> перемещать скролл
* Flex Wrap alignment
* Tests
* Debug elements inspector
* BoxShadow? - `#include <include/utils/SkShadowUtils.h>`
* Material ui
