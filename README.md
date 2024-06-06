# Elementor

## How to get started

1. Install [XMake](https://xmake.io)

2. Clone the project

    ```bash
    git clone https://github.com/noartem/elementor.git
    cd elementor
    ```

3. Fetch project dependencies

    ```bash
    xmake
    ```

4. *Optional* Set build mode (release/debug/check)

    ```bash
    xmake f -m release -y
    ```

5. Build the project for your system

    ```bash
    xmake build
    ```
   
6. Generate CMake config file

   ```bash
   xmake project -k cmakelists
   ```

7. Check out examples

    ```bash
    xmake run example-todo
    ```

## Project structure

`src/library` - contains library code   
`src/library/*.(cpp|h)` - library core   
`src/library/platforms` - standard primitive elements library, most of them can be replaced by self-made elements   
`src/platforms` - OS interaction layer   
`src/platforms/gl` - OS interaction layer made with GLFW   
`src/components` - ready-to-use UI components made by standard elements composition, also can be replaced by user
elements   
`src/examples` - example applications used to verify that the library works correctly   
`tests` - various library tests   
`tests/screenshots` - standard examples screenshots used for testing   
`tests/screenshots_new` - newly generated examples screenshots   
`tests/screenshots_diff` - difference between standard and new screenshots

## Run Tests

Run screenshot tests. Screenshots are created by `tests/make_screenshots.cpp` and
compared by `tests/compare_screenshots.py`

```bash
python test.py
```

## Examples

Elementor provides a list of various examples. They are also used for performing screenshot tests.

### 1. Basic

- Rich text rendering
- FPS counter
- Buttons and text field
- Hover and focus support
    - Click on a button and then press Tab - your focus will be moved to the next focusable element (button, text, ...)

```bash
xmake run example-basic
```

<div>
    <img src="tests/screenshots/basic.png" height="256px" alt="Basic example screnshot">
</div>

### 2. Button

- Clickable buttons of different types

```bash
xmake run example-button
```

<div>
    <img src="tests/screenshots/button.png" height="256px" alt="Button example screnshot">
</div>

### 3. Counter

- Clickable button
- Updating state

```bash
xmake run example-counter
```

<div>
    <img src="tests/screenshots/counter.png" height="256px"  alt="Counter example screnshot">
</div>

### 4. CRUD (readonly)

- Template for a generic CRUD application
- For now, read-only

```bash
xmake run example-crud
```

<div>
    <img src="tests/screenshots/crud.png" height="256px" alt="CRUD example screnshot">
</div>

### 5. Temperature Converter

- Text input
- State
- Transforming state

```bash
xmake run example-tempconv
```

<div>
    <img src="tests/screenshots/tempconv.png" width="512px" alt="Temperature converter example screnshot">
</div>

### 6. Text

- Rich text rendering

```bash
xmake run example-text
```

<div>
    <img src="tests/screenshots/text.png" height="256px" alt="Text example screnshot">
</div>

### 7. TODO

- Complex demo application with all previous features combined
- Sync with markdown file `examples/assets/todo.md`

```bash
xmake run example-todo
```

<div>
    <img src="tests/screenshots/todo.png" height="384px" alt="TODO example screnshot">
</div>

### All combined

There is also an example application providing all of the previous examples in one window.

```bash
xmake run examples
```
