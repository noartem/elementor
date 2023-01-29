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
4. *Optional* Set build mode (release/debug/check)
    ```bash
    xmake f -m release -y
    ```
5. Build project for your system
    ```bash
    xmake build
    ```
6. Check out examples
    ```bash
    xmake run example-gallery
    ```
7. Check out [node.js bindings](src/napi/)