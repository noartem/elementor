# Elementor NAPI

## [Elementor](https://github.com/noartem/elementor) Node.js bindings powered by [N-API](https://nodejs.org/api/n-api.html)

## How to build

1. Build elementor itself

```bash
xmake build
```

2. Cd into napi folder

```bash
cd src/napi
```

3. Run preinstall script

```bash
node preinstall.mjs
```

4. Install depndencies and build node extension

```bash
npm install
```

5. Run tests

```bash
npm run test
```