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

- [ ] Рефактор
    - [ ] Perfomance improvments
        - [ ] const для всех гетеров `int getSome() const;`
        - [ ] везде где передаются не ссылки "const &"
        - [ ] везде, где не изменяются строки заменить на std::string_view
        - [ ] Заменить `#define` на `constexpr`
            ```
            inline constexpr float infinity = ...;
            inline constexpr float zero = 0;
            inline const Boundaries anyBoundaries = {{zero, zero}, {infinity, infinity}};
            ```
        - [ ] убрать new/delete и перенести все на smart pointers (shared_ptr наверное)
        - [ ] Сделать использование элементов безопасным:
            - [ ] Добавить проверки на null
            - [ ] Деструкторы
    - [ ] Text: migrate to custom TextLine
        - [ ] Проверить есть ли в skia-build `SK_SHAPER_HARFBUZZ_AVAILABLE`, `SK_UNICODE_AVAILABLE`
        - [ ] Отедльный класс, который из информации о тексте (все что есть в `Text`), создает `sktext::TextLine`
        - [ ] Для примера: TextLine в Skija
        - [ ] Использовать в `Text` `TextLine`
        - [ ] Проверить размеры текста на разных системах
    - [ ] Вынести ф-ии конвертации цветов
    - [ ] Clickable через Hoverable
    - [ ] Баги со скроллом
        - [ ] Ненужный скролл при ресайзе
        - [ ] Если скролл и x и y, то наслаиваются друг на друга
        - [ ] Добавить scroll на зажатие и перемещение thumb -> перемещать скролл
            Через `Draggable`
    - [ ] Перейти c xmake.io на CMake
- [ ] Новые фичи
    - [ ] Тесты
        - [ ] Ф-ии конвертации цветов
        - [ ] Утилити функции, напрмер: `fitSizeInBoundaries`
        - [ ] Application
        - [ ] Элементы для размеров/позиционирования, например: Padding
        - [ ] Тесты снапшотами для рисующихся
    - [ ] Draggable
    - [ ] Анимации
        - [ ] Линейная анимация
        - [ ] Кривые анимации
        - [ ] Функция перехода
            - [ ] Числа
            - [ ] Точки
            - [ ] Цвета
        - [ ] Макросы для удобства (?)
    - [ ] Transform (типа [CSS Transform](https://developer.mozilla.org/en-US/docs/Web/CSS/CSS_Transforms/Using_CSS_transforms))
    - [ ] Дебагер
        - [ ] Save nodes tree
        - [ ] Dump in console nodes tree on some shortcut
        - [ ] Debug elements inspector
    - [ ] Flex Wrap alignment
    - [ ] BoxShadow?
        `#include <include/utils/SkShadowUtils.h>`
    - [ ] Библиотека стандартных компонентов
    - [ ] Material ui
    - [ ] Video
        [GStreamer with Skia](https://stackoverflow.com/questions/65687577/is-there-a-way-i-can-turn-video-frames-from-gstreamer-to-skimage-instances-to-be)
        [gl_ffmpeg](https://gist.github.com/rcolinray/7552384)
- [ ] Документация
    - [ ] Examples gallery
        - [ ] Добавить примеры для
            - [ ] Text
                - [ ] font fallback (emoju)
                - [ ] ligatures (!=, ==, <=, =:=)
            - [ ] Paragraph
                - [ ] Paragraph placeholder
            - [ ] Padding
            - [ ] Label
            - [ ] Rounded
            - [ ] Border
            - [ ] Element
            - [ ] Clickable
            - [ ] Hoverable
            - [ ] List
                - [ ] Column
                - [ ] Row
            - [ ] Scroll
                - [ ] Scrollable
                - [ ] Scrollbar
        - [ ] Добавить куски кода для примеров
            - [ ] Как заимпортить (?)
            - [ ] Как использовать
            - [ ] Ссылка на элемент в исходниках
        - [ ] Поработать над дизайном
            - [ ] Не дефолтный шрифт
            - [ ] Стандартная цветовая палитра - вынести в константы
            - [ ] Стандартные компоненты
    - [ ] Examples diary
        - [ ] Делать после Examples gallery и применить все изменения
