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

* Перенести Text, Inputable на `EString : public SkString`
* Image
* Paragraph
    * Просто скопировать skpargraph себе
    * Как это делать в skia?
    * Если Text -> брать из него font, paint
    * Если не Text, то вставлять как прямоугольник посреди текста (Если такое можно)
* Transform
* Text font fallback (например, fallback для эмодзи)
* Баг с ненужным скролом
* Неправильные размеры текста на линухе
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
* Video
    * [GStreamer with Skia](https://stackoverflow.com/questions/65687577/is-there-a-way-i-can-turn-video-frames-from-gstreamer-to-skimage-instances-to-be)
    * [gl_ffmpeg](https://gist.github.com/rcolinray/7552384)
    
