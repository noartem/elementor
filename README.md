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

* Paragraph
    * Как это делать в skia?
    * Если Text -> брать из него font, paint
    * Если не Text, то вставлять как прямоугольник посреди текста (Если такое можно)
* Text memory leak?
* Примеры для:
    * Padding
    * Sized
        * Height
        * Width
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
* Если скролл x и y, то друг на друга
* Scroll на зажатие и перемещение thumb -> перемещать скролл
* Если резко менять размер, то съезжает вниз, появляется ненужный скролл
* Flex Wrap alignment
* Image?
* Debug
* BoxShadow? - `#include <include/utils/SkShadowUtils.h>`
* Material ui
